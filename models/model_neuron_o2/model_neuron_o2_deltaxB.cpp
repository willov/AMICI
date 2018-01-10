
#include <include/symbolic_functions.h>
#include <include/amici_defines.h> //realtype definition
typedef amici::realtype realtype;
#include <cmath> 

void deltaxB_model_neuron_o2(double *deltaxB, const realtype t, const realtype *x, const realtype *p, const realtype *k, const realtype *h, const int ie, const realtype *xdot, const realtype *xdot_old, const realtype *xB) {
              switch(ie) { 
              case 0: {
  deltaxB[0] = xB[0]+xB[2]*((x[2]*(x[0]*(2.0/2.5E1)+5.0))/(k[1]+x[0]*5.0-x[1]+(x[0]*x[0])*(1.0/2.5E1)+1.4E2)-x[2]*(x[0]*(2.0/2.5E1)+5.0)*1.0/pow(k[1]+x[0]*5.0-x[1]+(x[0]*x[0])*(1.0/2.5E1)+1.4E2,2.0)*(p[2]*5.0+p[3]+x[0]*5.0-(p[2]*p[2])*(1.0/2.5E1)+(x[0]*x[0])*(1.0/2.5E1)))+xB[4]*((x[4]*(x[0]*(2.0/2.5E1)+5.0))/(k[1]+x[0]*5.0-x[1]+(x[0]*x[0])*(1.0/2.5E1)+1.4E2)-x[4]*(x[0]*(2.0/2.5E1)+5.0)*1.0/pow(k[1]+x[0]*5.0-x[1]+(x[0]*x[0])*(1.0/2.5E1)+1.4E2,2.0)*(p[2]*5.0+p[3]+x[0]*5.0-(p[2]*p[2])*(1.0/2.5E1)+(x[0]*x[0])*(1.0/2.5E1)))+xB[6]*((x[6]*(x[0]*(2.0/2.5E1)+5.0))/(k[1]+x[0]*5.0-x[1]+(x[0]*x[0])*(1.0/2.5E1)+1.4E2)-x[6]*(x[0]*(2.0/2.5E1)+5.0)*1.0/pow(k[1]+x[0]*5.0-x[1]+(x[0]*x[0])*(1.0/2.5E1)+1.4E2,2.0)*(p[2]*5.0+p[3]+x[0]*5.0-(p[2]*p[2])*(1.0/2.5E1)+(x[0]*x[0])*(1.0/2.5E1)))+xB[8]*((x[8]*(x[0]*(2.0/2.5E1)+5.0))/(k[1]+x[0]*5.0-x[1]+(x[0]*x[0])*(1.0/2.5E1)+1.4E2)-x[8]*(x[0]*(2.0/2.5E1)+5.0)*1.0/pow(k[1]+x[0]*5.0-x[1]+(x[0]*x[0])*(1.0/2.5E1)+1.4E2,2.0)*(p[2]*5.0+p[3]+x[0]*5.0-(p[2]*p[2])*(1.0/2.5E1)+(x[0]*x[0])*(1.0/2.5E1)))+xB[3]*((p[0]*p[1]*x[2])/(k[1]+x[0]*5.0-x[1]+(x[0]*x[0])*(1.0/2.5E1)+1.4E2)-x[2]*(x[0]*(2.0/2.5E1)+5.0)*(p[0]*(p[3]+x[1]+p[1]*p[2])-p[0]*(x[1]-p[1]*x[0]))*1.0/pow(k[1]+x[0]*5.0-x[1]+(x[0]*x[0])*(1.0/2.5E1)+1.4E2,2.0))+xB[5]*((p[0]*p[1]*x[4])/(k[1]+x[0]*5.0-x[1]+(x[0]*x[0])*(1.0/2.5E1)+1.4E2)-x[4]*(x[0]*(2.0/2.5E1)+5.0)*(p[0]*(p[3]+x[1]+p[1]*p[2])-p[0]*(x[1]-p[1]*x[0]))*1.0/pow(k[1]+x[0]*5.0-x[1]+(x[0]*x[0])*(1.0/2.5E1)+1.4E2,2.0))+xB[7]*((p[0]*p[1]*x[6])/(k[1]+x[0]*5.0-x[1]+(x[0]*x[0])*(1.0/2.5E1)+1.4E2)-x[6]*(x[0]*(2.0/2.5E1)+5.0)*(p[0]*(p[3]+x[1]+p[1]*p[2])-p[0]*(x[1]-p[1]*x[0]))*1.0/pow(k[1]+x[0]*5.0-x[1]+(x[0]*x[0])*(1.0/2.5E1)+1.4E2,2.0))+xB[9]*((p[0]*p[1]*x[8])/(k[1]+x[0]*5.0-x[1]+(x[0]*x[0])*(1.0/2.5E1)+1.4E2)-x[8]*(x[0]*(2.0/2.5E1)+5.0)*(p[0]*(p[3]+x[1]+p[1]*p[2])-p[0]*(x[1]-p[1]*x[0]))*1.0/pow(k[1]+x[0]*5.0-x[1]+(x[0]*x[0])*(1.0/2.5E1)+1.4E2,2.0));
  deltaxB[1] = x[2]*xB[3]*(p[0]*(p[3]+x[1]+p[1]*p[2])-p[0]*(x[1]-p[1]*x[0]))*1.0/pow(k[1]+x[0]*5.0-x[1]+(x[0]*x[0])*(1.0/2.5E1)+1.4E2,2.0)+x[4]*xB[5]*(p[0]*(p[3]+x[1]+p[1]*p[2])-p[0]*(x[1]-p[1]*x[0]))*1.0/pow(k[1]+x[0]*5.0-x[1]+(x[0]*x[0])*(1.0/2.5E1)+1.4E2,2.0)+x[6]*xB[7]*(p[0]*(p[3]+x[1]+p[1]*p[2])-p[0]*(x[1]-p[1]*x[0]))*1.0/pow(k[1]+x[0]*5.0-x[1]+(x[0]*x[0])*(1.0/2.5E1)+1.4E2,2.0)+x[8]*xB[9]*(p[0]*(p[3]+x[1]+p[1]*p[2])-p[0]*(x[1]-p[1]*x[0]))*1.0/pow(k[1]+x[0]*5.0-x[1]+(x[0]*x[0])*(1.0/2.5E1)+1.4E2,2.0)+x[2]*xB[2]*1.0/pow(k[1]+x[0]*5.0-x[1]+(x[0]*x[0])*(1.0/2.5E1)+1.4E2,2.0)*(p[2]*5.0+p[3]+x[0]*5.0-(p[2]*p[2])*(1.0/2.5E1)+(x[0]*x[0])*(1.0/2.5E1))+x[4]*xB[4]*1.0/pow(k[1]+x[0]*5.0-x[1]+(x[0]*x[0])*(1.0/2.5E1)+1.4E2,2.0)*(p[2]*5.0+p[3]+x[0]*5.0-(p[2]*p[2])*(1.0/2.5E1)+(x[0]*x[0])*(1.0/2.5E1))+x[6]*xB[6]*1.0/pow(k[1]+x[0]*5.0-x[1]+(x[0]*x[0])*(1.0/2.5E1)+1.4E2,2.0)*(p[2]*5.0+p[3]+x[0]*5.0-(p[2]*p[2])*(1.0/2.5E1)+(x[0]*x[0])*(1.0/2.5E1))+x[8]*xB[8]*1.0/pow(k[1]+x[0]*5.0-x[1]+(x[0]*x[0])*(1.0/2.5E1)+1.4E2,2.0)*(p[2]*5.0+p[3]+x[0]*5.0-(p[2]*p[2])*(1.0/2.5E1)+(x[0]*x[0])*(1.0/2.5E1));
  deltaxB[2] = (xB[3]*(p[0]*(p[3]+x[1]+p[1]*p[2])-p[0]*(x[1]-p[1]*x[0])))/(k[1]+x[0]*5.0-x[1]+(x[0]*x[0])*(1.0/2.5E1)+1.4E2)+(xB[2]*(p[2]*5.0+p[3]+x[0]*5.0-(p[2]*p[2])*(1.0/2.5E1)+(x[0]*x[0])*(1.0/2.5E1)))/(k[1]+x[0]*5.0-x[1]+(x[0]*x[0])*(1.0/2.5E1)+1.4E2);
  deltaxB[4] = (xB[5]*(p[0]*(p[3]+x[1]+p[1]*p[2])-p[0]*(x[1]-p[1]*x[0])))/(k[1]+x[0]*5.0-x[1]+(x[0]*x[0])*(1.0/2.5E1)+1.4E2)+(xB[4]*(p[2]*5.0+p[3]+x[0]*5.0-(p[2]*p[2])*(1.0/2.5E1)+(x[0]*x[0])*(1.0/2.5E1)))/(k[1]+x[0]*5.0-x[1]+(x[0]*x[0])*(1.0/2.5E1)+1.4E2);
  deltaxB[6] = (xB[7]*(p[0]*(p[3]+x[1]+p[1]*p[2])-p[0]*(x[1]-p[1]*x[0])))/(k[1]+x[0]*5.0-x[1]+(x[0]*x[0])*(1.0/2.5E1)+1.4E2)+(xB[6]*(p[2]*5.0+p[3]+x[0]*5.0-(p[2]*p[2])*(1.0/2.5E1)+(x[0]*x[0])*(1.0/2.5E1)))/(k[1]+x[0]*5.0-x[1]+(x[0]*x[0])*(1.0/2.5E1)+1.4E2);
  deltaxB[8] = (xB[9]*(p[0]*(p[3]+x[1]+p[1]*p[2])-p[0]*(x[1]-p[1]*x[0])))/(k[1]+x[0]*5.0-x[1]+(x[0]*x[0])*(1.0/2.5E1)+1.4E2)+(xB[8]*(p[2]*5.0+p[3]+x[0]*5.0-(p[2]*p[2])*(1.0/2.5E1)+(x[0]*x[0])*(1.0/2.5E1)))/(k[1]+x[0]*5.0-x[1]+(x[0]*x[0])*(1.0/2.5E1)+1.4E2);

              } break;

              } 
}

