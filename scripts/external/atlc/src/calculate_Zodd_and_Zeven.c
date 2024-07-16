/* atlc - arbitrary transmission line calculator, for the analysis of
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

/* The following calculates the odd and even mode impedances between two
zero thickness strips of width w, spaced a distance s between two
groundplanes of spacing h. */

#include "config.h"

#include "gsl_types.h"
#include "gsl_definitions.h"
#include "definitions.h"

#ifdef HAVE_STDLIB_H
#include <stdlib.h>
#endif

#ifdef HAVE_MATH_H
#include <math.h>
#endif

#include "exit_codes.h"
/* formuals taken from Matthaei, Young and Jones, Microwave Filters, Impedance Matching
Networks and Coupling Structures, Artech House, Dedham, MA., 1980. , but I've substituted
29.97924580105028, as its clear 30 is just a close approximation */

void calculate_Zodd_and_Zeven(double *Zodd, double *Zeven, double *Zo, double w, double H, double s, double er)
{
  double ke, ko, ko_dash, ke_dash;
  ke=(tanh((M_PI/2)*(w/H)))*tanh((M_PI/2)*(w+s)/H);
  ko=(tanh((M_PI/2)*(w/H)))/tanh((M_PI/2)*(w+s)/H);

  ke_dash=sqrt(1-ke*ke);
  ko_dash=sqrt(1-ko*ko);

  *Zeven=29.9792458010502837*M_PI*gsl_sf_ellint_Kcomp(ke_dash, GSL_PREC_DOUBLE)/(gsl_sf_ellint_Kcomp(ke,GSL_PREC_DOUBLE)*sqrt(er));
  *Zodd= 29.9792458010502837*M_PI*gsl_sf_ellint_Kcomp(ko_dash, GSL_PREC_DOUBLE)/(gsl_sf_ellint_Kcomp(ko,GSL_PREC_DOUBLE)*sqrt(er));
  *Zo=sqrt( (*Zodd)*(*Zeven));
}
