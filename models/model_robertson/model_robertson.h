#ifndef _amici_model_robertson_h
#define _amici_model_robertson_h
/* Generated by amiwrap (R2017b) 7740dbf2a3b308b3a28335e6e55b0a1f492791b2 */
#include <cmath>
#include <memory>
#include "amici/defines.h"
#include <sunmatrix/sunmatrix_sparse.h> //SUNMatrixContent_Sparse definition
#include "amici/solver_idas.h"
#include "amici/model_dae.h"

namespace amici {

class Solver;

namespace model_model_robertson{

extern void JSparse_model_robertson(SUNMatrixContent_Sparse JSparse, const realtype t, const realtype *x, const realtype *p, const realtype *k, const realtype *h, const realtype cj, const realtype *dx, const realtype *w, const realtype *dwdx);
extern void Jy_model_robertson(double *nllh, const int iy, const realtype *p, const realtype *k, const double *y, const double *sigmay, const double *my);
extern void M_model_robertson(realtype *M, const realtype t, const realtype *x, const realtype *p, const realtype *k);
extern void dJydsigma_model_robertson(double *dJydsigma, const int iy, const realtype *p, const realtype *k, const double *y, const double *sigmay, const double *my);
extern void dJydy_model_robertson(double *dJydy, const int iy, const realtype *p, const realtype *k, const double *y, const double *sigmay, const double *my);
extern void dwdp_model_robertson(realtype *dwdp, const realtype t, const realtype *x, const realtype *p, const realtype *k, const realtype *h, const realtype *w, const realtype *tcl, const realtype *stcl);
extern void dwdx_model_robertson(realtype *dwdx, const realtype t, const realtype *x, const realtype *p, const realtype *k, const realtype *h, const realtype *w, const realtype *tcl);
extern void dxdotdp_model_robertson(realtype *dxdotdp, const realtype t, const realtype *x, const realtype *p, const realtype *k, const realtype *h, const int ip, const realtype *dx, const realtype *w, const realtype *dwdp);
extern void dydx_model_robertson(double *dydx, const realtype t, const realtype *x, const realtype *p, const realtype *k, const realtype *h, const realtype *w, const realtype *dwdx);
extern void sigmay_model_robertson(double *sigmay, const realtype t, const realtype *p, const realtype *k, const realtype *y);
extern void w_model_robertson(realtype *w, const realtype t, const realtype *x, const realtype *p, const realtype *k, const realtype *h, const realtype *tcl);
extern void x0_model_robertson(realtype *x0, const realtype t, const realtype *p, const realtype *k);
extern void xdot_model_robertson(realtype *xdot, const realtype t, const realtype *x, const realtype *p, const realtype *k, const realtype *h, const realtype *dx, const realtype *w);
extern void y_model_robertson(double *y, const realtype t, const realtype *x, const realtype *p, const realtype *k, const realtype *h, const realtype *w);

class Model_model_robertson : public amici::Model_DAE {
public:
    Model_model_robertson()
        : amici::Model_DAE(
              amici::ModelDimensions(
                  3,
                  3,
                  3,
                  3,
                  0,
                  3,
                  1,
                  3,
                  3,
                  0,
                  0,
                  0,
                  1,
                  1,
                  2,
                  1,
                  0,
                  0,
                  {},
                  0,
                  0,
                  0,
                  9,
                  2,
                  2
              ),
              amici::SimulationParameters(
                  std::vector<realtype>(1, 1.0),
                  std::vector<realtype>(3, 1.0)
              ),
              amici::SecondOrderMode::none,
              std::vector<realtype>{1, 1, 0},
              std::vector<int>{})
              {};

    amici::Model* clone() const override { return new Model_model_robertson(*this); };

    std::string getAmiciCommit() const override { return "7740dbf2a3b308b3a28335e6e55b0a1f492791b2"; };

    void fJSparse(SUNMatrixContent_Sparse JSparse, const realtype t, const realtype *x, const realtype *p, const realtype *k, const realtype *h, const realtype cj, const realtype *dx, const realtype *w, const realtype *dwdx) override {
        JSparse_model_robertson(JSparse, t, x, p, k, h, cj, dx, w, dwdx);
    }

    void fJrz(double *nllh, const int iz, const realtype *p, const realtype *k, const double *rz, const double *sigmaz) override {
    }

    void fJy(double *nllh, const int iy, const realtype *p, const realtype *k, const double *y, const double *sigmay, const double *my) override {
        Jy_model_robertson(nllh, iy, p, k, y, sigmay, my);
    }

    void fJz(double *nllh, const int iz, const realtype *p, const realtype *k, const double *z, const double *sigmaz, const double *mz) override {
    }

    void fM(realtype *M, const realtype t, const realtype *x, const realtype *p, const realtype *k) override {
        M_model_robertson(M, t, x, p, k);
    }

    void fdJrzdsigma(double *dJrzdsigma, const int iz, const realtype *p, const realtype *k, const double *rz, const double *sigmaz) override {
    }

    void fdJrzdz(double *dJrzdz, const int iz, const realtype *p, const realtype *k, const double *rz, const double *sigmaz) override {
    }

    void fdJydsigma(double *dJydsigma, const int iy, const realtype *p, const realtype *k, const double *y, const double *sigmay, const double *my) override {
        dJydsigma_model_robertson(dJydsigma, iy, p, k, y, sigmay, my);
    }

    void fdJydy(double *dJydy, const int iy, const realtype *p, const realtype *k, const double *y, const double *sigmay, const double *my) override {
        dJydy_model_robertson(dJydy, iy, p, k, y, sigmay, my);
    }

    void fdJzdsigma(double *dJzdsigma, const int iz, const realtype *p, const realtype *k, const double *z, const double *sigmaz, const double *mz) override {
    }

    void fdJzdz(double *dJzdz, const int iz, const realtype *p, const realtype *k, const double *z, const double *sigmaz, const double *mz) override {
    }

    void fdeltaqB(double *deltaqB, const realtype t, const realtype *x, const realtype *p, const realtype *k, const realtype *h, const int ip, const int ie, const realtype *xdot, const realtype *xdot_old, const realtype *xB, const realtype *xBdot) override {
    }

    void fdeltasx(double *deltasx, const realtype t, const realtype *x, const realtype *p, const realtype *k, const realtype *h, const realtype *w, const int ip, const int ie, const realtype *xdot, const realtype *xdot_old, const realtype *sx, const realtype *stau, const realtype *tcl) override {
    }

    void fdeltax(double *deltax, const realtype t, const realtype *x, const realtype *p, const realtype *k, const realtype *h, const int ie, const realtype *xdot, const realtype *xdot_old) override {
    }

    void fdeltaxB(double *deltaxB, const realtype t, const realtype *x, const realtype *p, const realtype *k, const realtype *h, const int ie, const realtype *xdot, const realtype *xdot_old, const realtype *xB, const realtype *xBdot, const realtype *tcl) override {
    }

    void fdrzdp(double *drzdp, const int ie, const realtype t, const realtype *x, const realtype *p, const realtype *k, const realtype *h, const int ip) override {
    }

    void fdrzdx(double *drzdx, const int ie, const realtype t, const realtype *x, const realtype *p, const realtype *k, const realtype *h) override {
    }

    void fdsigmaydp(double *dsigmaydp, const realtype t, const realtype *p, const realtype *k, const realtype *y, const int ip) override {
    }

    void fdsigmazdp(double *dsigmazdp, const realtype t, const realtype *p, const realtype *k, const int ip) override {
    }

    void fdwdp(realtype *dwdp, const realtype t, const realtype *x, const realtype *p, const realtype *k, const realtype *h, const realtype *w, const realtype *tcl, const realtype *stcl) override {
        dwdp_model_robertson(dwdp, t, x, p, k, h, w, tcl, stcl);
    }

    void fdwdx(realtype *dwdx, const realtype t, const realtype *x, const realtype *p, const realtype *k, const realtype *h, const realtype *w, const realtype *tcl) override {
        dwdx_model_robertson(dwdx, t, x, p, k, h, w, tcl);
    }

    void fdxdotdp(realtype *dxdotdp, const realtype t, const realtype *x, const realtype *p, const realtype *k, const realtype *h, const int ip, const realtype *dx, const realtype *w, const realtype *dwdp) override {
        dxdotdp_model_robertson(dxdotdp, t, x, p, k, h, ip, dx, w, dwdp);
    }

    void fdydp(double *dydp, const realtype t, const realtype *x, const realtype *p, const realtype *k, const realtype *h, const int ip, const realtype *w, const realtype *dwdp) override {
    }

    void fdydx(double *dydx, const realtype t, const realtype *x, const realtype *p, const realtype *k, const realtype *h, const realtype *w, const realtype *dwdx) override {
        dydx_model_robertson(dydx, t, x, p, k, h, w, dwdx);
    }

    void fdzdp(double *dzdp, const int ie, const realtype t, const realtype *x, const realtype *p, const realtype *k, const realtype *h, const int ip) override {
    }

    void fdzdx(double *dzdx, const int ie, const realtype t, const realtype *x, const realtype *p, const realtype *k, const realtype *h) override {
    }

    void froot(realtype *root, const realtype t, const realtype *x, const realtype *p, const realtype *k, const realtype *h, const realtype *dx) override {
    }

    void frz(double *rz, const int ie, const realtype t, const realtype *x, const realtype *p, const realtype *k, const realtype *h) override {
    }

    void fsigmay(double *sigmay, const realtype t, const realtype *p, const realtype *k, const realtype *y) override {
        sigmay_model_robertson(sigmay, t, p, k, y);
    }

    void fsigmaz(double *sigmaz, const realtype t, const realtype *p, const realtype *k) override {
    }

    void fsrz(double *srz, const int ie, const realtype t, const realtype *x, const realtype *p, const realtype *k, const realtype *h, const realtype *sx, const int ip) override {
    }

    void fstau(double *stau, const realtype t, const realtype *x, const realtype *p, const realtype *k, const realtype *h, const realtype *tcl, const realtype *sx, const int ip, const int ie) override {
    }

    void fsx0(realtype *sx0, const realtype t,const realtype *x0, const realtype *p, const realtype *k, const int ip) override {
    }

    void fsz(double *sz, const int ie, const realtype t, const realtype *x, const realtype *p, const realtype *k, const realtype *h, const realtype *sx, const int ip) override {
    }

    void fw(realtype *w, const realtype t, const realtype *x, const realtype *p, const realtype *k, const realtype *h, const realtype *tcl) override {
        w_model_robertson(w, t, x, p, k, h, tcl);
    }

    void fx0(realtype *x0, const realtype t, const realtype *p, const realtype *k) override {
        x0_model_robertson(x0, t, p, k);
    }

    void fxdot(realtype *xdot, const realtype t, const realtype *x, const realtype *p, const realtype *k, const realtype *h, const realtype *dx, const realtype *w) override {
        xdot_model_robertson(xdot, t, x, p, k, h, dx, w);
    }

    void fy(double *y, const realtype t, const realtype *x, const realtype *p, const realtype *k, const realtype *h, const realtype *w) override {
        y_model_robertson(y, t, x, p, k, h, w);
    }

    void fz(double *z, const int ie, const realtype t, const realtype *x, const realtype *p, const realtype *k, const realtype *h) override {
    }

};

} // namespace model_model_robertson

} // namespace amici 

#endif /* _amici_model_robertson_h */
