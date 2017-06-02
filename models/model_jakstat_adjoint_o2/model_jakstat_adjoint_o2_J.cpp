
#include <include/symbolic_functions.h>
#include <string.h>
#include <include/udata.h>
#include "model_jakstat_adjoint_o2_dwdx.h"
#include "model_jakstat_adjoint_o2_w.h"

int J_model_jakstat_adjoint_o2(long int N, realtype t, N_Vector x, N_Vector xdot, DlsMat J, void *user_data, N_Vector tmp1, N_Vector tmp2, N_Vector tmp3) {
int status = 0;
UserData *udata = (UserData*) user_data;
realtype *x_tmp = N_VGetArrayPointer(x);
realtype *xdot_tmp = N_VGetArrayPointer(xdot);
int ix;
memset(J->data,0,sizeof(realtype)*26244);
status = w_model_jakstat_adjoint_o2(t,x,NULL,user_data);
status = dwdx_model_jakstat_adjoint_o2(t,x,NULL,user_data);
  J->data[0+0*162] = -udata->k[0]*udata->p[0]*udata->w[0]*udata->w[2];
  J->data[0+8*162] = udata->k[1]*udata->p[3]*udata->w[2];
  J->data[1+0*162] = udata->p[0]*udata->w[0];
  J->data[1+1*162] = udata->dwdx[0]*udata->p[1]*-2.0;
  J->data[2+1*162] = udata->dwdx[0]*udata->p[1];
  J->data[2+2*162] = -udata->p[2];
  J->data[3+2*162] = udata->k[0]*udata->p[2]*udata->w[3];
  J->data[3+3*162] = -udata->k[1]*udata->p[3]*udata->w[3];
  J->data[4+3*162] = udata->dwdx[1]*udata->p[3];
  J->data[4+4*162] = -udata->p[3];
  J->data[5+4*162] = udata->p[3];
  J->data[5+5*162] = -udata->p[3];
  J->data[6+5*162] = udata->p[3];
  J->data[6+6*162] = -udata->p[3];
  J->data[7+6*162] = udata->p[3];
  J->data[7+7*162] = -udata->p[3];
  J->data[8+7*162] = udata->p[3];
  J->data[8+8*162] = -udata->p[3];
  J->data[9+0*162] = -udata->w[0];
  J->data[9+9*162] = -udata->p[0]*udata->w[0];
  J->data[9+17*162] = udata->k[1]*udata->p[3]*udata->w[2];
  J->data[10+0*162] = udata->w[0];
  J->data[10+1*162] = udata->p[1]*x_tmp[10]*-4.0;
  J->data[10+9*162] = udata->p[0]*udata->w[0];
  J->data[10+10*162] = udata->p[1]*x_tmp[1]*-4.0;
  J->data[11+1*162] = udata->p[1]*x_tmp[10]*2.0;
  J->data[11+10*162] = udata->p[1]*x_tmp[1]*2.0;
  J->data[11+11*162] = -udata->p[2];
  J->data[12+11*162] = udata->k[0]*udata->p[2]*udata->w[3];
  J->data[12+12*162] = -udata->p[3];
  J->data[13+12*162] = udata->p[3]*2.0;
  J->data[13+13*162] = -udata->p[3];
  J->data[14+13*162] = udata->p[3];
  J->data[14+14*162] = -udata->p[3];
  J->data[15+14*162] = udata->p[3];
  J->data[15+15*162] = -udata->p[3];
  J->data[16+15*162] = udata->p[3];
  J->data[16+16*162] = -udata->p[3];
  J->data[17+16*162] = udata->p[3];
  J->data[17+17*162] = -udata->p[3];
  J->data[18+18*162] = -udata->p[0]*udata->w[0];
  J->data[18+26*162] = udata->k[1]*udata->p[3]*udata->w[2];
  J->data[19+1*162] = udata->dwdx[0]*-2.0-udata->p[1]*x_tmp[19]*4.0;
  J->data[19+18*162] = udata->p[0]*udata->w[0];
  J->data[19+19*162] = udata->p[1]*x_tmp[1]*-4.0;
  J->data[20+1*162] = udata->dwdx[0]+udata->p[1]*x_tmp[19]*2.0;
  J->data[20+19*162] = udata->p[1]*x_tmp[1]*2.0;
  J->data[20+20*162] = -udata->p[2];
  J->data[21+20*162] = udata->k[0]*udata->p[2]*udata->w[3];
  J->data[21+21*162] = -udata->p[3];
  J->data[22+21*162] = udata->p[3]*2.0;
  J->data[22+22*162] = -udata->p[3];
  J->data[23+22*162] = udata->p[3];
  J->data[23+23*162] = -udata->p[3];
  J->data[24+23*162] = udata->p[3];
  J->data[24+24*162] = -udata->p[3];
  J->data[25+24*162] = udata->p[3];
  J->data[25+25*162] = -udata->p[3];
  J->data[26+25*162] = udata->p[3];
  J->data[26+26*162] = -udata->p[3];
  J->data[27+27*162] = -udata->p[0]*udata->w[0];
  J->data[27+35*162] = udata->k[1]*udata->p[3]*udata->w[2];
  J->data[28+1*162] = udata->p[1]*x_tmp[28]*-4.0;
  J->data[28+27*162] = udata->p[0]*udata->w[0];
  J->data[28+28*162] = udata->p[1]*x_tmp[1]*-4.0;
  J->data[29+1*162] = udata->p[1]*x_tmp[28]*2.0;
  J->data[29+2*162] = -1.0;
  J->data[29+28*162] = udata->p[1]*x_tmp[1]*2.0;
  J->data[29+29*162] = -udata->p[2];
  J->data[30+2*162] = udata->k[0]*udata->w[3];
  J->data[30+29*162] = udata->k[0]*udata->p[2]*udata->w[3];
  J->data[30+30*162] = -udata->p[3];
  J->data[31+30*162] = udata->p[3]*2.0;
  J->data[31+31*162] = -udata->p[3];
  J->data[32+31*162] = udata->p[3];
  J->data[32+32*162] = -udata->p[3];
  J->data[33+32*162] = udata->p[3];
  J->data[33+33*162] = -udata->p[3];
  J->data[34+33*162] = udata->p[3];
  J->data[34+34*162] = -udata->p[3];
  J->data[35+34*162] = udata->p[3];
  J->data[35+35*162] = -udata->p[3];
  J->data[36+8*162] = udata->k[1]*udata->w[2];
  J->data[36+36*162] = -udata->p[0]*udata->w[0];
  J->data[36+44*162] = udata->k[1]*udata->p[3]*udata->w[2];
  J->data[37+1*162] = udata->p[1]*x_tmp[37]*-4.0;
  J->data[37+36*162] = udata->p[0]*udata->w[0];
  J->data[37+37*162] = udata->p[1]*x_tmp[1]*-4.0;
  J->data[38+1*162] = udata->p[1]*x_tmp[37]*2.0;
  J->data[38+37*162] = udata->p[1]*x_tmp[1]*2.0;
  J->data[38+38*162] = -udata->p[2];
  J->data[39+3*162] = -1.0;
  J->data[39+38*162] = udata->k[0]*udata->p[2]*udata->w[3];
  J->data[39+39*162] = -udata->p[3];
  J->data[40+3*162] = udata->dwdx[1];
  J->data[40+4*162] = -1.0;
  J->data[40+39*162] = udata->p[3]*2.0;
  J->data[40+40*162] = -udata->p[3];
  J->data[41+4*162] = 1.0;
  J->data[41+5*162] = -1.0;
  J->data[41+40*162] = udata->p[3];
  J->data[41+41*162] = -udata->p[3];
  J->data[42+5*162] = 1.0;
  J->data[42+6*162] = -1.0;
  J->data[42+41*162] = udata->p[3];
  J->data[42+42*162] = -udata->p[3];
  J->data[43+6*162] = 1.0;
  J->data[43+7*162] = -1.0;
  J->data[43+42*162] = udata->p[3];
  J->data[43+43*162] = -udata->p[3];
  J->data[44+7*162] = 1.0;
  J->data[44+8*162] = -1.0;
  J->data[44+43*162] = udata->p[3];
  J->data[44+44*162] = -udata->p[3];
  J->data[45+45*162] = -udata->p[0]*udata->w[0];
  J->data[45+53*162] = udata->k[1]*udata->p[3]*udata->w[2];
  J->data[46+1*162] = udata->p[1]*x_tmp[46]*-4.0;
  J->data[46+45*162] = udata->p[0]*udata->w[0];
  J->data[46+46*162] = udata->p[1]*x_tmp[1]*-4.0;
  J->data[47+1*162] = udata->p[1]*x_tmp[46]*2.0;
  J->data[47+46*162] = udata->p[1]*x_tmp[1]*2.0;
  J->data[47+47*162] = -udata->p[2];
  J->data[48+47*162] = udata->k[0]*udata->p[2]*udata->w[3];
  J->data[48+48*162] = -udata->p[3];
  J->data[49+48*162] = udata->p[3]*2.0;
  J->data[49+49*162] = -udata->p[3];
  J->data[50+49*162] = udata->p[3];
  J->data[50+50*162] = -udata->p[3];
  J->data[51+50*162] = udata->p[3];
  J->data[51+51*162] = -udata->p[3];
  J->data[52+51*162] = udata->p[3];
  J->data[52+52*162] = -udata->p[3];
  J->data[53+52*162] = udata->p[3];
  J->data[53+53*162] = -udata->p[3];
  J->data[54+0*162] = -udata->p[0]*udata->w[5];
  J->data[54+54*162] = -udata->p[0]*udata->w[0];
  J->data[54+62*162] = udata->k[1]*udata->p[3]*udata->w[2];
  J->data[55+0*162] = udata->p[0]*udata->w[5];
  J->data[55+1*162] = udata->p[1]*x_tmp[55]*-4.0;
  J->data[55+54*162] = udata->p[0]*udata->w[0];
  J->data[55+55*162] = udata->p[1]*x_tmp[1]*-4.0;
  J->data[56+1*162] = udata->p[1]*x_tmp[55]*2.0;
  J->data[56+55*162] = udata->p[1]*x_tmp[1]*2.0;
  J->data[56+56*162] = -udata->p[2];
  J->data[57+56*162] = udata->k[0]*udata->p[2]*udata->w[3];
  J->data[57+57*162] = -udata->p[3];
  J->data[58+57*162] = udata->p[3]*2.0;
  J->data[58+58*162] = -udata->p[3];
  J->data[59+58*162] = udata->p[3];
  J->data[59+59*162] = -udata->p[3];
  J->data[60+59*162] = udata->p[3];
  J->data[60+60*162] = -udata->p[3];
  J->data[61+60*162] = udata->p[3];
  J->data[61+61*162] = -udata->p[3];
  J->data[62+61*162] = udata->p[3];
  J->data[62+62*162] = -udata->p[3];
  J->data[63+0*162] = -udata->p[0]*udata->w[6];
  J->data[63+63*162] = -udata->p[0]*udata->w[0];
  J->data[63+71*162] = udata->k[1]*udata->p[3]*udata->w[2];
  J->data[64+0*162] = udata->p[0]*udata->w[6];
  J->data[64+1*162] = udata->p[1]*x_tmp[64]*-4.0;
  J->data[64+63*162] = udata->p[0]*udata->w[0];
  J->data[64+64*162] = udata->p[1]*x_tmp[1]*-4.0;
  J->data[65+1*162] = udata->p[1]*x_tmp[64]*2.0;
  J->data[65+64*162] = udata->p[1]*x_tmp[1]*2.0;
  J->data[65+65*162] = -udata->p[2];
  J->data[66+65*162] = udata->k[0]*udata->p[2]*udata->w[3];
  J->data[66+66*162] = -udata->p[3];
  J->data[67+66*162] = udata->p[3]*2.0;
  J->data[67+67*162] = -udata->p[3];
  J->data[68+67*162] = udata->p[3];
  J->data[68+68*162] = -udata->p[3];
  J->data[69+68*162] = udata->p[3];
  J->data[69+69*162] = -udata->p[3];
  J->data[70+69*162] = udata->p[3];
  J->data[70+70*162] = -udata->p[3];
  J->data[71+70*162] = udata->p[3];
  J->data[71+71*162] = -udata->p[3];
  J->data[72+0*162] = -udata->p[0]*udata->w[7];
  J->data[72+72*162] = -udata->p[0]*udata->w[0];
  J->data[72+80*162] = udata->k[1]*udata->p[3]*udata->w[2];
  J->data[73+0*162] = udata->p[0]*udata->w[7];
  J->data[73+1*162] = udata->p[1]*x_tmp[73]*-4.0;
  J->data[73+72*162] = udata->p[0]*udata->w[0];
  J->data[73+73*162] = udata->p[1]*x_tmp[1]*-4.0;
  J->data[74+1*162] = udata->p[1]*x_tmp[73]*2.0;
  J->data[74+73*162] = udata->p[1]*x_tmp[1]*2.0;
  J->data[74+74*162] = -udata->p[2];
  J->data[75+74*162] = udata->k[0]*udata->p[2]*udata->w[3];
  J->data[75+75*162] = -udata->p[3];
  J->data[76+75*162] = udata->p[3]*2.0;
  J->data[76+76*162] = -udata->p[3];
  J->data[77+76*162] = udata->p[3];
  J->data[77+77*162] = -udata->p[3];
  J->data[78+77*162] = udata->p[3];
  J->data[78+78*162] = -udata->p[3];
  J->data[79+78*162] = udata->p[3];
  J->data[79+79*162] = -udata->p[3];
  J->data[80+79*162] = udata->p[3];
  J->data[80+80*162] = -udata->p[3];
  J->data[81+0*162] = -udata->p[0]*udata->w[8];
  J->data[81+81*162] = -udata->p[0]*udata->w[0];
  J->data[81+89*162] = udata->k[1]*udata->p[3]*udata->w[2];
  J->data[82+0*162] = udata->p[0]*udata->w[8];
  J->data[82+1*162] = udata->p[1]*x_tmp[82]*-4.0;
  J->data[82+81*162] = udata->p[0]*udata->w[0];
  J->data[82+82*162] = udata->p[1]*x_tmp[1]*-4.0;
  J->data[83+1*162] = udata->p[1]*x_tmp[82]*2.0;
  J->data[83+82*162] = udata->p[1]*x_tmp[1]*2.0;
  J->data[83+83*162] = -udata->p[2];
  J->data[84+83*162] = udata->k[0]*udata->p[2]*udata->w[3];
  J->data[84+84*162] = -udata->p[3];
  J->data[85+84*162] = udata->p[3]*2.0;
  J->data[85+85*162] = -udata->p[3];
  J->data[86+85*162] = udata->p[3];
  J->data[86+86*162] = -udata->p[3];
  J->data[87+86*162] = udata->p[3];
  J->data[87+87*162] = -udata->p[3];
  J->data[88+87*162] = udata->p[3];
  J->data[88+88*162] = -udata->p[3];
  J->data[89+88*162] = udata->p[3];
  J->data[89+89*162] = -udata->p[3];
  J->data[90+0*162] = -udata->p[0]*udata->w[9];
  J->data[90+90*162] = -udata->p[0]*udata->w[0];
  J->data[90+98*162] = udata->k[1]*udata->p[3]*udata->w[2];
  J->data[91+0*162] = udata->p[0]*udata->w[9];
  J->data[91+1*162] = udata->p[1]*x_tmp[91]*-4.0;
  J->data[91+90*162] = udata->p[0]*udata->w[0];
  J->data[91+91*162] = udata->p[1]*x_tmp[1]*-4.0;
  J->data[92+1*162] = udata->p[1]*x_tmp[91]*2.0;
  J->data[92+91*162] = udata->p[1]*x_tmp[1]*2.0;
  J->data[92+92*162] = -udata->p[2];
  J->data[93+92*162] = udata->k[0]*udata->p[2]*udata->w[3];
  J->data[93+93*162] = -udata->p[3];
  J->data[94+93*162] = udata->p[3]*2.0;
  J->data[94+94*162] = -udata->p[3];
  J->data[95+94*162] = udata->p[3];
  J->data[95+95*162] = -udata->p[3];
  J->data[96+95*162] = udata->p[3];
  J->data[96+96*162] = -udata->p[3];
  J->data[97+96*162] = udata->p[3];
  J->data[97+97*162] = -udata->p[3];
  J->data[98+97*162] = udata->p[3];
  J->data[98+98*162] = -udata->p[3];
  J->data[99+99*162] = -udata->p[0]*udata->w[0];
  J->data[99+107*162] = udata->k[1]*udata->p[3]*udata->w[2];
  J->data[100+1*162] = udata->p[1]*x_tmp[100]*-4.0;
  J->data[100+99*162] = udata->p[0]*udata->w[0];
  J->data[100+100*162] = udata->p[1]*x_tmp[1]*-4.0;
  J->data[101+1*162] = udata->p[1]*x_tmp[100]*2.0;
  J->data[101+100*162] = udata->p[1]*x_tmp[1]*2.0;
  J->data[101+101*162] = -udata->p[2];
  J->data[102+101*162] = udata->k[0]*udata->p[2]*udata->w[3];
  J->data[102+102*162] = -udata->p[3];
  J->data[103+102*162] = udata->p[3]*2.0;
  J->data[103+103*162] = -udata->p[3];
  J->data[104+103*162] = udata->p[3];
  J->data[104+104*162] = -udata->p[3];
  J->data[105+104*162] = udata->p[3];
  J->data[105+105*162] = -udata->p[3];
  J->data[106+105*162] = udata->p[3];
  J->data[106+106*162] = -udata->p[3];
  J->data[107+106*162] = udata->p[3];
  J->data[107+107*162] = -udata->p[3];
  J->data[108+108*162] = -udata->p[0]*udata->w[0];
  J->data[108+116*162] = udata->k[1]*udata->p[3]*udata->w[2];
  J->data[109+1*162] = udata->p[1]*x_tmp[109]*-4.0;
  J->data[109+108*162] = udata->p[0]*udata->w[0];
  J->data[109+109*162] = udata->p[1]*x_tmp[1]*-4.0;
  J->data[110+1*162] = udata->p[1]*x_tmp[109]*2.0;
  J->data[110+109*162] = udata->p[1]*x_tmp[1]*2.0;
  J->data[110+110*162] = -udata->p[2];
  J->data[111+110*162] = udata->k[0]*udata->p[2]*udata->w[3];
  J->data[111+111*162] = -udata->p[3];
  J->data[112+111*162] = udata->p[3]*2.0;
  J->data[112+112*162] = -udata->p[3];
  J->data[113+112*162] = udata->p[3];
  J->data[113+113*162] = -udata->p[3];
  J->data[114+113*162] = udata->p[3];
  J->data[114+114*162] = -udata->p[3];
  J->data[115+114*162] = udata->p[3];
  J->data[115+115*162] = -udata->p[3];
  J->data[116+115*162] = udata->p[3];
  J->data[116+116*162] = -udata->p[3];
  J->data[117+117*162] = -udata->p[0]*udata->w[0];
  J->data[117+125*162] = udata->k[1]*udata->p[3]*udata->w[2];
  J->data[118+1*162] = udata->p[1]*x_tmp[118]*-4.0;
  J->data[118+117*162] = udata->p[0]*udata->w[0];
  J->data[118+118*162] = udata->p[1]*x_tmp[1]*-4.0;
  J->data[119+1*162] = udata->p[1]*x_tmp[118]*2.0;
  J->data[119+118*162] = udata->p[1]*x_tmp[1]*2.0;
  J->data[119+119*162] = -udata->p[2];
  J->data[120+119*162] = udata->k[0]*udata->p[2]*udata->w[3];
  J->data[120+120*162] = -udata->p[3];
  J->data[121+120*162] = udata->p[3]*2.0;
  J->data[121+121*162] = -udata->p[3];
  J->data[122+121*162] = udata->p[3];
  J->data[122+122*162] = -udata->p[3];
  J->data[123+122*162] = udata->p[3];
  J->data[123+123*162] = -udata->p[3];
  J->data[124+123*162] = udata->p[3];
  J->data[124+124*162] = -udata->p[3];
  J->data[125+124*162] = udata->p[3];
  J->data[125+125*162] = -udata->p[3];
  J->data[126+126*162] = -udata->p[0]*udata->w[0];
  J->data[126+134*162] = udata->k[1]*udata->p[3]*udata->w[2];
  J->data[127+1*162] = udata->p[1]*x_tmp[127]*-4.0;
  J->data[127+126*162] = udata->p[0]*udata->w[0];
  J->data[127+127*162] = udata->p[1]*x_tmp[1]*-4.0;
  J->data[128+1*162] = udata->p[1]*x_tmp[127]*2.0;
  J->data[128+127*162] = udata->p[1]*x_tmp[1]*2.0;
  J->data[128+128*162] = -udata->p[2];
  J->data[129+128*162] = udata->k[0]*udata->p[2]*udata->w[3];
  J->data[129+129*162] = -udata->p[3];
  J->data[130+129*162] = udata->p[3]*2.0;
  J->data[130+130*162] = -udata->p[3];
  J->data[131+130*162] = udata->p[3];
  J->data[131+131*162] = -udata->p[3];
  J->data[132+131*162] = udata->p[3];
  J->data[132+132*162] = -udata->p[3];
  J->data[133+132*162] = udata->p[3];
  J->data[133+133*162] = -udata->p[3];
  J->data[134+133*162] = udata->p[3];
  J->data[134+134*162] = -udata->p[3];
  J->data[135+135*162] = -udata->p[0]*udata->w[0];
  J->data[135+143*162] = udata->k[1]*udata->p[3]*udata->w[2];
  J->data[136+1*162] = udata->p[1]*x_tmp[136]*-4.0;
  J->data[136+135*162] = udata->p[0]*udata->w[0];
  J->data[136+136*162] = udata->p[1]*x_tmp[1]*-4.0;
  J->data[137+1*162] = udata->p[1]*x_tmp[136]*2.0;
  J->data[137+136*162] = udata->p[1]*x_tmp[1]*2.0;
  J->data[137+137*162] = -udata->p[2];
  J->data[138+137*162] = udata->k[0]*udata->p[2]*udata->w[3];
  J->data[138+138*162] = -udata->p[3];
  J->data[139+138*162] = udata->p[3]*2.0;
  J->data[139+139*162] = -udata->p[3];
  J->data[140+139*162] = udata->p[3];
  J->data[140+140*162] = -udata->p[3];
  J->data[141+140*162] = udata->p[3];
  J->data[141+141*162] = -udata->p[3];
  J->data[142+141*162] = udata->p[3];
  J->data[142+142*162] = -udata->p[3];
  J->data[143+142*162] = udata->p[3];
  J->data[143+143*162] = -udata->p[3];
  J->data[144+144*162] = -udata->p[0]*udata->w[0];
  J->data[144+152*162] = udata->k[1]*udata->p[3]*udata->w[2];
  J->data[145+1*162] = udata->p[1]*x_tmp[145]*-4.0;
  J->data[145+144*162] = udata->p[0]*udata->w[0];
  J->data[145+145*162] = udata->p[1]*x_tmp[1]*-4.0;
  J->data[146+1*162] = udata->p[1]*x_tmp[145]*2.0;
  J->data[146+145*162] = udata->p[1]*x_tmp[1]*2.0;
  J->data[146+146*162] = -udata->p[2];
  J->data[147+146*162] = udata->k[0]*udata->p[2]*udata->w[3];
  J->data[147+147*162] = -udata->p[3];
  J->data[148+147*162] = udata->p[3]*2.0;
  J->data[148+148*162] = -udata->p[3];
  J->data[149+148*162] = udata->p[3];
  J->data[149+149*162] = -udata->p[3];
  J->data[150+149*162] = udata->p[3];
  J->data[150+150*162] = -udata->p[3];
  J->data[151+150*162] = udata->p[3];
  J->data[151+151*162] = -udata->p[3];
  J->data[152+151*162] = udata->p[3];
  J->data[152+152*162] = -udata->p[3];
  J->data[153+153*162] = -udata->p[0]*udata->w[0];
  J->data[153+161*162] = udata->k[1]*udata->p[3]*udata->w[2];
  J->data[154+1*162] = udata->p[1]*x_tmp[154]*-4.0;
  J->data[154+153*162] = udata->p[0]*udata->w[0];
  J->data[154+154*162] = udata->p[1]*x_tmp[1]*-4.0;
  J->data[155+1*162] = udata->p[1]*x_tmp[154]*2.0;
  J->data[155+154*162] = udata->p[1]*x_tmp[1]*2.0;
  J->data[155+155*162] = -udata->p[2];
  J->data[156+155*162] = udata->k[0]*udata->p[2]*udata->w[3];
  J->data[156+156*162] = -udata->p[3];
  J->data[157+156*162] = udata->p[3]*2.0;
  J->data[157+157*162] = -udata->p[3];
  J->data[158+157*162] = udata->p[3];
  J->data[158+158*162] = -udata->p[3];
  J->data[159+158*162] = udata->p[3];
  J->data[159+159*162] = -udata->p[3];
  J->data[160+159*162] = udata->p[3];
  J->data[160+160*162] = -udata->p[3];
  J->data[161+160*162] = udata->p[3];
  J->data[161+161*162] = -udata->p[3];
for(ix = 0; ix<26244; ix++) {
   if(amiIsNaN(J->data[ix])) {
       J->data[ix] = 0;
       if(!udata->nan_J) {
           warnMsgIdAndTxt("AMICI:mex:fJ:NaN","AMICI replaced a NaN value in Jacobian and replaced it by 0.0. This will not be reported again for this simulation run.");
           udata->nan_J = TRUE;
       }
   }
   if(amiIsInf(J->data[ix])) {
       warnMsgIdAndTxt("AMICI:mex:fJ:Inf","AMICI encountered an Inf value in Jacobian! Aborting simulation ... ");
       return(-1);
   }
}
return(status);

}

