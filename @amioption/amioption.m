%
% @file amioption
% @brief definition of amioption class
%
classdef amioption < matlab.mixin.CustomDisplay
    %AMIOPTION provides an option container to pass simulation parameters to the
    %simulation routine.
    
    properties
        % absolute integration tolerace
        atol = 1e-16;
        % relative integration tolerace
        rtol = 1e-8;
        % maximum number of integration steps
        maxsteps = 1e4;
        % index of parameters for which the sensitivities are computed
        sens_ind = double.empty();
        % index of states for which positivity should be enforced
        qpositivex = double.empty();
        % scaling of error tolerances for sensitivity equations
        pbar = double.empty();
        % starting time of the simulation
        tstart = 0;
        % linear multistep method.
        lmm = 2;
        % iteration method for linear multistep.
        iter = 2;
        % linear solver
        linsol = 9;
        % stability detection flag
        stldet = true;
        % interpolation type
        interpType = 1;
        % linear multistep method (backwards)
        lmmB = 2;
        % iteration method for linear multistep (backwards).
        iterB = 2;
        % forward sensitivity mode
        ism = 1;
        % sensitivity method
        sensi_meth = 1;
        % sensitivity order
        sensi = 0;
        % number of reported events
        nmaxevent = 10;
        % reordering of states
        ordering = 0;
        % steady state sensitivity flag
        ss = 0;
        % custom initial state
        x0 = double.empty();
        % custom initial sensitivity
        sx0 = double.empty();
        % newton solver: linear solver (BiCGStab, GMRES, KLU direct)
        ns_linsol = 0;
        % newton solver: preconditioning method (none, diagonal, incomplete LU)
        ns_precon = 1;
        % newton solver: maximum newton steps
        ns_maxsteps = 20;
        % newton solver: maximum linear steps
        ns_maxlinsteps = 150;
        % preequilibration of system via newton solver
        preequil = 0;
    end
    
    properties (Hidden)
        % mapping of event ouputs to events
        z2event = double.empty();
        % flag for DAE variables
        id = double.empty();
    end
    
    methods
        function obj = amioption(varargin)
            %amioptions Construct a new amioptions object
            %   OPTS = amioption() creates a set of options with each option set to its
            %   default value.
            %
            %   OPTS = amioption(PARAM, VAL, ...) creates a set of options with the named
            %   parameters altered with the specified values.
            %
            %   OPTS = amioption(OLDOPTS, PARAM, VAL, ...) creates a copy of OLDOPTS with
            %   the named parameters altered with the specified value
            %
            %   Note: to see the parameters, check the
            %   documentation page for @amioption
            %
            % Parameters:
            %  varargin: input to construct amioption object, see function
            %            function description
            %
            % Return values:
            %  obj: amioption object constructed from inputs
            %
            
            % adapted from SolverOptions
            
            if nargin > 0 
                
                % Deal with the case where the first input to the
                % constructor is a amioptions/struct object.
                if isa(varargin{1},'amioption')
                    if strcmp(class(varargin{1}),class(obj))
                        obj = varargin{1};
                    else
                        % Get the properties from options object passed
                        % into the constructor.
                        thisProps = properties(obj);
                        % Set the common properties. Note that we
                        % investigated first finding the properties that
                        % are common to both objects and just looping over
                        % those. We found that in most cases this was no
                        % quicker than just looping over the properties of
                        % the object passed in.
                        for i = 1:length(thisProps)
                            try %#ok
                                % Try to set one of the properties of the
                                % old object in the new one.
                                obj.(thisProps{i}) = varargin{1}.(thisProps{i});
                            end
                        end
                    end
                    firstInputObj = true;
                elseif isstruct(varargin{1})
                    fieldlist = fieldnames(varargin{1});
                    for ifield = 1:length(fieldlist)
                        obj.(fieldlist{ifield}) = varargin{1}.(fieldlist{ifield});
                    end
                    firstInputObj = true;
                elseif isempty(varargin{1})
                    firstInputObj = true;
                else
                    firstInputObj = false;
                end
                
                % Extract the options that the caller of the constructor
                % wants to set.
                if firstInputObj
                    pvPairs = varargin(2:end);
                else
                    pvPairs = varargin;
                end
                
                % Loop through each param-value pair and just try to set
                % the option. When the option has been fully specified with
                % the correct case, this is fast. The catch clause deals
                % with partial matches or errors.
                haveCreatedInputParser = false;
                for i = 1:2:length(pvPairs)
                    try
                        obj.(pvPairs{i}) = pvPairs{i+1};
                    catch ME %#ok
                        
                        % Create the input parser if we haven't already. We
                        % do it here to avoid creating it if possible, as
                        % it is slow to set up.
                        if ~haveCreatedInputParser
                            ip = inputParser;
                            % Structures are currently not supported as
                            % an input to optimoptions. Setting the
                            % StructExpand property of the input parser to
                            % false, forces the parser to treat the
                            % structure as a single input and not a set of
                            % param-value pairs.
                            ip.StructExpand =  false;
                            % Get list of option names
                            allOptionNames = properties(obj);
                            for j = 1:length(allOptionNames)
                                % Just specify an empty default as we already have the
                                % defaults in the options object.
                                ip.addParameter(allOptionNames{j}, []);
                            end
                            haveCreatedInputParser = true;
                        end
                        
                        % Get the p-v pair to parse.
                        thisPair = pvPairs(i:min(i+1, length(pvPairs)));
                        ip.parse(thisPair{:});
                        
                        % Determine the option that was specified in p-v pairs.
                        % These options will now be matched even if only partially
                        % specified (by 13a). Now set the specified value in the
                        % options object.
                        optionSet = setdiff(allOptionNames, ip.UsingDefaults);
                        obj.(optionSet{1}) = ip.Results.(optionSet{1});
                    end
                end
            end
            
            
        end
        
        function this = set.sensi_meth(this,value)
            if(ischar(value))
                switch(value)
                    case 'forward'
                        this.sensi_meth = 1;
                    case 'adjoint' 
                        this.sensi_meth = 2;
                    case 'ss'
                        this.sensi_meth = 3;
                    otherwise
                        error('Unknown sensitivity method. Must be either ''forward'',''adjoint'' or ''ss''!');
                end
            else
                assert(isnumeric(value),'The option sensi_meth must have a numeric value!')
                assert(floor(value)==value,'The option sensi_meth must be an integer!')
                assert(value<=4,'Only 1, 2, 3 are valid options for sensi_meth!')
                assert(value>=0,'Only 1, 2, 3 are valid options for sensi_meth!')
                this.sensi_meth = value;
            end
        end
        
        function this = set.sensi(this,value)
            assert(isnumeric(value),'The option sensi must have a numeric value!')
            assert(floor(value)==value,'The option sensi must be an integer!')
            assert(value<=4,'Only 0, 1, 2 are valid options for sensi!')
            this.sensi = value;
        end
        
        function this = set.ns_linsol(this,value)
            assert(isnumeric(value),'The option ns_linsol must have a numeric value!')
            assert(floor(value)==value,'The option ns_linsol must be an integer!')
            assert(value<=2,'Only 0, 1, and 2 are valid options for ns_linsol!')
            this.ns_linsol = value;
        end
        
        function this = set.ns_precon(this,value)
            assert(isnumeric(value),'The option ns_precon must have a numeric value!')
            assert(floor(value)==value,'The option ns_precon must be an integer!')
            assert(value<=2,'Only 0, 1, and 2 are valid options for ns_precon!')
            this.ns_precon = value;
        end
        
        function this = set.ns_maxsteps(this,value)
            assert(isnumeric(value),'The option ns_maxsteps must have a numeric value!')
            assert(floor(value)==value,'The option ns_maxsteps must be an integer!')
            this.ns_maxsteps = value;
        end
        
        function this = set.ns_maxlinsteps(this,value)
            assert(isnumeric(value),'The option ns_maxlinsteps must have a numeric value!')
            assert(floor(value)==value,'The option ns_maxlinsteps must be an integer!')
            this.ns_maxlinsteps = value;
        end

        function this = set.preequil(this,value)
            assert(isnumeric(value),'The option preequil must have a numeric value!')
            assert(floor(value)==value,'The option preequil must be an integer!')
            assert(value<=2,'Only 0 and 1 are valid options for preequil!')
            this.preequil = value;
        end
    end
end