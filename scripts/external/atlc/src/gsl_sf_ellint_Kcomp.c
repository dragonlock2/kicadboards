

#include "config.h"

#ifdef HAVE_MATH_H
#include <math.h>
#endif

#include "definitions.h"
#include "gsl_types.h"
#include "gsl_definitions.h"
#include "exit_codes.h"

/* This part of atlc is a copy from the code in the GPL'ed 
GNU Scientific Library, gsl. By including this code, it saves 
the user having to like with gsl. */

const double gsl_prec_eps[3];



double gsl_sf_ellint_Kcomp(double k, gsl_mode_t mode)
{
  gsl_sf_result result;
  gsl_sf_ellint_Kcomp_e(k, mode, &result);
  return result.val;
}


/* [Carlson, Numer. Math. 33 (1979) 1, (4.5)] */
int gsl_sf_ellint_Kcomp_e(double k, gsl_mode_t mode, gsl_sf_result * result)
{
  int return_val=0;
  if(k*k >= 1.0) {
    exit_with_msg_and_exit_code("domain error in gsl_sf_Kcomp_e", DOMAIN_ERROR);
  }
  else if(k*k >= 1.0 - GSL_SQRT_DBL_EPSILON) {
    /* [Abramowitz+Stegun, 17.3.33] */
    const double y = 1.0 - k*k;
    const double a[] = { 1.38629436112, 0.09666344259, 0.03590092383 };
    const double b[] = { 0.5, 0.12498593597, 0.06880248576 };
    const double ta = a[0] + y*(a[1] + y*a[2]);
    const double tb = -log(y) * (b[0] * y*(b[1] + y*b[2]));
    result->val = ta + tb;
    result->err = 2.0 * GSL_DBL_EPSILON * result->val;
    return_val=GSL_SUCCESS;
  }
  else {
    /* This was previously computed as,

         return gsl_sf_ellint_RF_e(0.0, 1.0 - k*k, 1.0, mode, result);

       but this underestimated the total error for small k, since the 
       argument y=1-k^2 is not exact (there is an absolute error of
       GSL_DBL_EPSILON near y=0 due to cancellation in the subtraction).
       Taking the singular behavior of -log(y) above gives an error
       of 0.5*epsilon/y near y=0. (BJG) */

    double y = 1.0 - k*k;
    int status = gsl_sf_ellint_RF_e(0.0, y, 1.0, mode, result);
    result->err += 0.5 * GSL_DBL_EPSILON / y;
    return_val=status ;
  }
  return(return_val);
}

int gsl_sf_ellint_RF_e(double x, double y, double z, gsl_mode_t mode, gsl_sf_result * result)
{
  int return_val=0;
  const double lolim = 5.0 * GSL_DBL_MIN;
  const double uplim = 0.2 * GSL_DBL_MAX;
  const gsl_prec_t goal = GSL_MODE_PREC(mode);
  const double errtol = ( goal == GSL_PREC_DOUBLE ? 0.001 : 0.03 );
  const double prec   = gsl_prec_eps[goal];

  if(x < 0.0 || y < 0.0 || z < 0.0) {
    exit_with_msg_and_exit_code("domain error in gsl_sf_ellint_RF_e", DOMAIN_ERROR);
  }
  else if(x+y < lolim || x+z < lolim || y+z < lolim) {
    exit_with_msg_and_exit_code("domain error in gsl_sf_ellint_RF_e", DOMAIN_ERROR);
  }
  else if(locMAX3(x,y,z) < uplim) { 
    const double c1 = 1.0 / 24.0;
    const double c2 = 3.0 / 44.0;
    const double c3 = 1.0 / 14.0;
    double xn = x;
    double yn = y;
    double zn = z;
    double mu, xndev, yndev, zndev, e2, e3, s;
    while(1) {
      double epslon, lamda;
      double xnroot, ynroot, znroot;
      mu = (xn + yn + zn) / 3.0;
      xndev = 2.0 - (mu + xn) / mu;
      yndev = 2.0 - (mu + yn) / mu;
      zndev = 2.0 - (mu + zn) / mu;
      epslon = locMAX3(fabs(xndev), fabs(yndev), fabs(zndev));
      if (epslon < errtol) break;
      xnroot = sqrt(xn);
      ynroot = sqrt(yn);
      znroot = sqrt(zn);
      lamda = xnroot * (ynroot + znroot) + ynroot * znroot;
      xn = (xn + lamda) * 0.25;
      yn = (yn + lamda) * 0.25;
      zn = (zn + lamda) * 0.25;
    }
    e2 = xndev * yndev - zndev * zndev;
    e3 = xndev * yndev * zndev;
    s = 1.0 + (c1 * e2 - 0.1 - c2 * e3) * e2 + c3 * e3;
    result->val = s / sqrt(mu);
    result->err = prec * fabs(result->val);
    return_val= GSL_SUCCESS;
  }
  else {
    exit_with_msg_and_exit_code("domain error in gsl_sf_ellint_RF_e", DOMAIN_ERROR);
  }
  return(return_val);
}


/* static double locMAX3(double x, double y, double z) */
double locMAX3(double x, double y, double z)
{
  double xy = GSL_MAX(x, y);
  return GSL_MAX(xy, z);
}


#define EVAL_RESULT(fn) \
   gsl_sf_result result; \
   int status = fn; \
   if (status != GSL_SUCCESS) { \
     GSL_ERROR_VAL(#fn, status, result.val); \
   } ; \
return result.val;

