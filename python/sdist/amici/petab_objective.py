"""
PEtab Objective
---------------
Functionality related to running simulations or evaluating the objective
function as defined by a PEtab problem
"""
import copy
import logging
from typing import Any, Dict, List, Optional, Sequence, Union

import amici
import numpy as np
import pandas as pd
import petab
from petab.C import *  # noqa: F403

from . import AmiciExpData, AmiciModel
from .logging import get_logger, log_execution_time
from .parameter_mapping import ParameterMapping

# some extra imports for backward-compatibility
from .petab.conditions import (  # noqa # pylint: disable=unused-import
    create_edata_for_condition,
    create_edatas,
    create_parameterized_edatas,
    fill_in_parameters,
)
from .petab.parameter_mapping import (  # noqa # pylint: disable=unused-import
    create_parameter_mapping,
    create_parameter_mapping_for_condition,
)
from .petab.util import (  # noqa # pylint: disable=unused-import
    get_states_in_condition_table,
)

try:
    import pysb
except ImportError:
    pysb = None

logger = get_logger(__name__)


# string constant definitions
LLH = "llh"
SLLH = "sllh"
FIM = "fim"
S2LLH = "s2llh"
RES = "res"
SRES = "sres"
RDATAS = "rdatas"
EDATAS = "edatas"


@log_execution_time("Simulating PEtab model", logger)
def simulate_petab(
    petab_problem: petab.Problem,
    amici_model: AmiciModel,
    solver: Optional[amici.Solver] = None,
    problem_parameters: Optional[Dict[str, float]] = None,
    simulation_conditions: Union[pd.DataFrame, Dict] = None,
    edatas: List[AmiciExpData] = None,
    parameter_mapping: ParameterMapping = None,
    scaled_parameters: Optional[bool] = False,
    log_level: int = logging.WARNING,
    num_threads: int = 1,
    failfast: bool = True,
    scaled_gradients: bool = False,
) -> Dict[str, Any]:
    """Simulate PEtab model.

    .. note::
        Regardless of `scaled_parameters`, unscaled sensitivities are returned,
        unless `scaled_gradients=True`.

    :param petab_problem:
        PEtab problem to work on.
    :param amici_model:
        AMICI Model assumed to be compatible with ``petab_problem``.
    :param solver:
        An AMICI solver. Will use default options if None.
    :param problem_parameters:
        Run simulation with these parameters. If ``None``, PEtab
        ``nominalValues`` will be used. To be provided as dict, mapping PEtab
        problem parameters to SBML IDs.
    :param simulation_conditions:
        Result of :py:func:`petab.get_simulation_conditions`. Can be provided
        to save time if this has be obtained before.
        Not required if ``edatas`` and ``parameter_mapping`` are provided.
    :param edatas:
        Experimental data. Parameters are inserted in-place for simulation.
    :param parameter_mapping:
        Optional precomputed PEtab parameter mapping for efficiency, as
        generated by :py:func:`create_parameter_mapping`.
    :param scaled_parameters:
        If ``True``, ``problem_parameters`` are assumed to be on the scale
        provided in the PEtab parameter table and will be unscaled.
        If ``False``, they are assumed to be in linear scale.
    :param log_level:
        Log level, see :mod:`amici.logging` module.
    :param num_threads:
        Number of threads to use for simulating multiple conditions
        (only used if compiled with OpenMP).
    :param failfast:
        Returns as soon as an integration failure is encountered, skipping
        any remaining simulations.
    :param scaled_gradients:
        Whether to compute gradients on parameter scale (``True``) or not
        (``False``).

    :return:
        Dictionary of

        * cost function value (``LLH``),
        * list of :class:`amici.amici.ReturnData` (``RDATAS``),
        * list of :class:`amici.amici.ExpData` (``EDATAS``),

        corresponding to the different simulation conditions.
        For ordering of simulation conditions, see
        :meth:`petab.Problem.get_simulation_conditions_from_measurement_df`.
    """
    logger.setLevel(log_level)

    if solver is None:
        solver = amici_model.getSolver()

    # Switch to scaled parameters.
    problem_parameters = _default_scaled_parameters(
        petab_problem=petab_problem,
        problem_parameters=problem_parameters,
        scaled_parameters=scaled_parameters,
    )
    scaled_parameters = True

    # number of amici simulations will be number of unique
    # (preequilibrationConditionId, simulationConditionId) pairs.
    # Can be optimized by checking for identical condition vectors.
    if (
        simulation_conditions is None
        and parameter_mapping is None
        and edatas is None
    ):
        simulation_conditions = (
            petab_problem.get_simulation_conditions_from_measurement_df()
        )

    # Get parameter mapping
    if parameter_mapping is None:
        parameter_mapping = create_parameter_mapping(
            petab_problem=petab_problem,
            simulation_conditions=simulation_conditions,
            scaled_parameters=scaled_parameters,
            amici_model=amici_model,
        )

    # Get edatas
    if edatas is None:
        # Generate ExpData with all condition-specific information
        edatas = create_edatas(
            amici_model=amici_model,
            petab_problem=petab_problem,
            simulation_conditions=simulation_conditions,
        )

    # Fill parameters in ExpDatas (in-place)
    fill_in_parameters(
        edatas=edatas,
        problem_parameters=problem_parameters,
        scaled_parameters=scaled_parameters,
        parameter_mapping=parameter_mapping,
        amici_model=amici_model,
    )

    # Simulate
    rdatas = amici.runAmiciSimulations(
        amici_model,
        solver,
        edata_list=edatas,
        num_threads=num_threads,
        failfast=failfast,
    )

    # Compute total llh
    llh = sum(rdata["llh"] for rdata in rdatas)
    # Compute total sllh
    sllh = None
    if solver.getSensitivityOrder() != amici.SensitivityOrder.none:
        sllh = aggregate_sllh(
            amici_model=amici_model,
            rdatas=rdatas,
            parameter_mapping=parameter_mapping,
            petab_scale=scaled_parameters,
            petab_problem=petab_problem,
            edatas=edatas,
        )
        if not scaled_gradients and sllh is not None:
            sllh = {
                parameter_id: rescale_sensitivity(
                    sensitivity=sensitivity,
                    parameter_value=problem_parameters[parameter_id],
                    old_scale=petab_problem.parameter_df.loc[
                        parameter_id, PARAMETER_SCALE
                    ],
                    new_scale=LIN,
                )
                for parameter_id, sensitivity in sllh.items()
            }

    # Log results
    sim_cond = petab_problem.get_simulation_conditions_from_measurement_df()
    for i, rdata in enumerate(rdatas):
        sim_cond_id = "N/A" if sim_cond.empty else sim_cond.iloc[i, :].values
        logger.debug(
            f"Condition: {sim_cond_id}, status: {rdata['status']}, "
            f"llh: {rdata['llh']}"
        )

    return {
        LLH: llh,
        SLLH: sllh,
        RDATAS: rdatas,
        EDATAS: edatas,
    }


def aggregate_sllh(
    amici_model: AmiciModel,
    rdatas: Sequence[amici.ReturnDataView],
    parameter_mapping: Optional[ParameterMapping],
    edatas: List[AmiciExpData],
    petab_scale: bool = True,
    petab_problem: petab.Problem = None,
) -> Union[None, Dict[str, float]]:
    """
    Aggregate likelihood gradient for all conditions, according to PEtab
    parameter mapping.

    :param amici_model:
        AMICI model from which ``rdatas`` were obtained.
    :param rdatas:
        Simulation results.
    :param parameter_mapping:
        PEtab parameter mapping to condition-specific simulation parameters.
    :param edatas:
        Experimental data used for simulation.
    :param petab_scale:
        Whether to check that sensitivities were computed with parameters on
        the scales provided in the PEtab parameters table.
    :param petab_problem:
        The PEtab problem that defines the parameter scales.

    :return:
        Aggregated likelihood sensitivities.
    """
    accumulated_sllh = {}
    model_parameter_ids = amici_model.getParameterIds()

    if petab_scale and petab_problem is None:
        raise ValueError(
            "Please provide the PEtab problem, when using "
            "`petab_scale=True`."
        )

    # Check for issues in all condition simulation results.
    for rdata in rdatas:
        # Condition failed during simulation.
        if rdata.status != amici.AMICI_SUCCESS:
            return None
        # Condition simulation result does not provide SLLH.
        if rdata.sllh is None:
            raise ValueError(
                "The sensitivities of the likelihood for a condition were "
                "not computed."
            )

    for condition_parameter_mapping, edata, rdata in zip(
        parameter_mapping, edatas, rdatas
    ):
        for sllh_parameter_index, condition_parameter_sllh in enumerate(
            rdata.sllh
        ):
            # Get PEtab parameter ID
            # Use ExpData if it provides a parameter list, else default to
            # Model.
            if edata.plist:
                model_parameter_index = edata.plist[sllh_parameter_index]
            else:
                model_parameter_index = amici_model.plist(sllh_parameter_index)
            model_parameter_id = model_parameter_ids[model_parameter_index]
            petab_parameter_id = condition_parameter_mapping.map_sim_var[
                model_parameter_id
            ]

            # Initialize
            if petab_parameter_id not in accumulated_sllh:
                accumulated_sllh[petab_parameter_id] = 0

            # Check that the scale is consistent
            if petab_scale:
                # `ParameterMappingForCondition` objects provide the scale in
                # terms of `petab.C` constants already, not AMICI equivalents.
                model_parameter_scale = (
                    condition_parameter_mapping.scale_map_sim_var[
                        model_parameter_id
                    ]
                )
                petab_parameter_scale = petab_problem.parameter_df.loc[
                    petab_parameter_id, PARAMETER_SCALE
                ]
                if model_parameter_scale != petab_parameter_scale:
                    raise ValueError(
                        f"The scale of the parameter `{petab_parameter_id}` "
                        "differs between the AMICI model "
                        f"({model_parameter_scale}) and the PEtab problem "
                        f"({petab_parameter_scale})."
                    )

            # Accumulate
            accumulated_sllh[petab_parameter_id] += condition_parameter_sllh

    return accumulated_sllh


def rescale_sensitivity(
    sensitivity: float,
    parameter_value: float,
    old_scale: str,
    new_scale: str,
) -> float:
    """Rescale a sensitivity between parameter scales.

    :param sensitivity:
        The sensitivity corresponding to the parameter value.
    :param parameter_value:
        The parameter vector element, on ``old_scale``.
    :param old_scale:
        The scale of the parameter value.
    :param new_scale:
        The parameter scale on which to rescale the sensitivity.

    :return:
        The rescaled sensitivity.
    """
    LOG_E_10 = np.log(10)

    if old_scale == new_scale:
        return sensitivity

    unscaled_parameter_value = petab.parameters.unscale(
        parameter=parameter_value,
        scale_str=old_scale,
    )

    scale = {
        (LIN, LOG): lambda s: s * unscaled_parameter_value,
        (LOG, LIN): lambda s: s / unscaled_parameter_value,
        (LIN, LOG10): lambda s: s * (unscaled_parameter_value * LOG_E_10),
        (LOG10, LIN): lambda s: s / (unscaled_parameter_value * LOG_E_10),
    }

    scale[(LOG, LOG10)] = lambda s: scale[(LIN, LOG10)](scale[(LOG, LIN)](s))
    scale[(LOG10, LOG)] = lambda s: scale[(LIN, LOG)](scale[(LOG10, LIN)](s))

    if (old_scale, new_scale) not in scale:
        raise NotImplementedError(
            f"Old scale: {old_scale}. New scale: {new_scale}."
        )

    return scale[(old_scale, new_scale)](sensitivity)


def rdatas_to_measurement_df(
    rdatas: Sequence[amici.ReturnData],
    model: AmiciModel,
    measurement_df: pd.DataFrame,
) -> pd.DataFrame:
    """
    Create a measurement dataframe in the PEtab format from the passed
    ``rdatas`` and own information.

    :param rdatas:
        A sequence of rdatas with the ordering of
        :func:`petab.get_simulation_conditions`.

    :param model:
        AMICI model used to generate ``rdatas``.

    :param measurement_df:
        PEtab measurement table used to generate ``rdatas``.

    :return:
        A dataframe built from the rdatas in the format of ``measurement_df``.
    """
    simulation_conditions = petab.get_simulation_conditions(measurement_df)

    observable_ids = model.getObservableIds()
    rows = []
    # iterate over conditions
    for (_, condition), rdata in zip(simulation_conditions.iterrows(), rdatas):
        # current simulation matrix
        y = rdata.y
        # time array used in rdata
        t = list(rdata.ts)

        # extract rows for condition
        cur_measurement_df = petab.get_rows_for_condition(
            measurement_df, condition
        )

        # iterate over entries for the given condition
        # note: this way we only generate a dataframe entry for every
        # row that existed in the original dataframe. if we want to
        # e.g. have also timepoints non-existent in the original file,
        # we need to instead iterate over the rdata['y'] entries
        for _, row in cur_measurement_df.iterrows():
            # copy row
            row_sim = copy.deepcopy(row)

            # extract simulated measurement value
            timepoint_idx = t.index(row[TIME])
            observable_idx = observable_ids.index(row[OBSERVABLE_ID])
            measurement_sim = y[timepoint_idx, observable_idx]

            # change measurement entry
            row_sim[MEASUREMENT] = measurement_sim

            rows.append(row_sim)

    return pd.DataFrame(rows)


def rdatas_to_simulation_df(
    rdatas: Sequence[amici.ReturnData],
    model: AmiciModel,
    measurement_df: pd.DataFrame,
) -> pd.DataFrame:
    """Create a PEtab simulation dataframe from
    :class:`amici.amici.ReturnData` s.

    See :func:`rdatas_to_measurement_df` for details, only that model outputs
    will appear in column ``simulation`` instead of ``measurement``."""

    df = rdatas_to_measurement_df(
        rdatas=rdatas, model=model, measurement_df=measurement_df
    )

    return df.rename(columns={MEASUREMENT: SIMULATION})


def _default_scaled_parameters(
    petab_problem: petab.Problem,
    problem_parameters: Optional[Dict[str, float]] = None,
    scaled_parameters: bool = False,
) -> Optional[Dict[str, float]]:
    """
    Helper method to handle an unscaled or unspecified parameter vector.

    The parameter vector defaults to the nominal values in the PEtab
    parameter table.

    Unscaled parameter values are scaled.

    :param petab_problem:
        The PEtab problem.
    :param problem_parameters:
        Keys are PEtab parameter IDs, values are parameter values on the scale
        defined in the PEtab parameter table. Defaults to the nominal values in
        the PEtab parameter table.
    :param scaled_parameters:
        Whether `problem_parameters` are on the scale defined in the PEtab
        parameter table.

    :return:
        The scaled parameter vector.
    """
    if problem_parameters is None:
        problem_parameters = dict(
            zip(
                petab_problem.x_ids,
                petab_problem.x_nominal_scaled,
            )
        )
    elif not scaled_parameters:
        problem_parameters = petab_problem.scale_parameters(problem_parameters)
    return problem_parameters
