/*
atlc - arbitrary transmission line calculator, for the analysis of
transmission lines are directional couplers. 

Copyright (C) 2002. Dr. David Kirkby, PhD (G8WRB).

This program is free software; you can redistribute it and/or
modify it under the terms of the GNU General Public License
as published by the Free Software Foundation; either package_version 2
of the License, or (at your option) any later package_version.

This program is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
GNU General Public License for more details.

You should have received a copy of the GNU General Public License
along with this program; if not, write to the Free Software
Foundation, Inc., 59 Temple Place - Suite 330, Boston, MA  02111-1307,
USA.

Dr. David Kirkby, e-mail drkirkby at gmail.com 

*/

/*
The following code is taken from the GNU Scientifi Library, gsl, 
which is also issued under the GPL. 

*/
#define GSL_PREC_DOUBLE                    0
#define GSL_SUCCESS                      0
/*
These values suita IEEE machines but might be too large 
for non-IEEE machines. Since I don't think its that 
important, I've changed the values a bit to be sure
double will work out okay. 

#define GSL_DBL_EPSILON        2.2204460492503131e-16
#define GSL_SQRT_DBL_EPSILON   1.4901161193847656e-08
#define GSL_DBL_MIN        2.2250738585072014e-308
#define GSL_DBL_MAX        1.7976931348623157e+308
*/

#define GSL_DBL_EPSILON        1e-14
#define GSL_SQRT_DBL_EPSILON   1e-7
#define GSL_DBL_MIN        1e-100
#define GSL_DBL_MAX        1e+100

#define GSL_MODE_PREC(mt) ((mt) & (unsigned int)7)
#define GSL_MAX(a,b) ((a) > (b) ? (a) : (b))
/* GSL_VAR const double gsl_prec_eps[]; */

typedef unsigned int gsl_mode_t;
typedef unsigned int gsl_prec_t;

typedef struct
{
  double val;
  double err;
} gsl_sf_result;

double gsl_sf_ellint_Kcomp(double k, gsl_mode_t mode);
int gsl_sf_ellint_Kcomp_e(double k, gsl_mode_t mode, gsl_sf_result * result);
int gsl_sf_ellint_RF_e(double x, double y, double z, gsl_mode_t mode, gsl_sf_result * result);
double locMAX3(double x, double y, double z);


/* End of things taken from gsl library */
