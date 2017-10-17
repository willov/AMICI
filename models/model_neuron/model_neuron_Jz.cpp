
#include <include/symbolic_functions.h>
#include <include/amici.h>
#include <include/amici_model.h>
#include <string.h>
#include <include/tdata.h>
#include <include/udata.h>
#include <include/rdata.h>
#include <include/edata.h>
#include "model_neuron_w.h"

int Jz_model_neuron(realtype t, int ie, N_Vector x, TempData *tdata, const ExpData *edata, ReturnData *rdata) {
int status = 0;
Model *model = (Model*) tdata->model;
UserData *udata = (UserData*) tdata->udata;
realtype *x_tmp = nullptr;
if(x)
    x_tmp = N_VGetArrayPointer(x);
status = w_model_neuron(t,x,NULL,tdata);
int iz;
if(!amiIsNaN(edata->mz[0*udata->nmaxevent+tdata->nroots[ie]])){
    iz = 0;
  tdata->Jz[0] += amilog((tdata->sigmaz[0]*tdata->sigmaz[0])*3.141592653589793*2.0)*5.0E-1+1.0/(tdata->sigmaz[0]*tdata->sigmaz[0])*pow(edata->mz[tdata->nroots[ie]+udata->nmaxevent*0]-rdata->z[tdata->nroots[ie]+udata->nmaxevent*0],2.0)*5.0E-1;
}
return(status);

}

