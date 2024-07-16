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

/* This routine calaculates the impedance exaclty for the case of two
infinity wide conductors sepparated a distance H, with between them
placed centrally a conductor of width w and infinitely thin. 

i.e.
******^***********************************************************************
      |
      |
      H                    ----------w----------
      |
      |
******Vij***********************************************************************

It uses the method given in "Filed Theory of Guided Waves, Colen R.E.,
2nd edition, pp 259-273, IEEE Press, (1990). */

#include "config.h"


#ifdef HAVE_MATH_H
#include <math.h>
#endif

#include "definitions.h"
#include "exit_codes.h"

extern int verbose;

double calculate_symmetrical_stripline_impedance(int H, int w)
{
  double Zo;
  double mu=4*M_PI*1e-7, x0, v0,  c, l, k;
  x0=pow(cosh(M_PI*w/(2.0*H)),2.0);
  if (verbose >=2)
    printf("w=%d H=%d w/H=%f xo=%g\n",w,H,(double)w/H,x0);
  if((double) w / (double) H > 226.369458)
    exit_with_msg_and_exit_code("Bitmap is written fine, but can't compute impedance", THE_WIDTH_w_DIVIDED_BY_THE_HEIGHT_H_IS_TOO_LARGE);
  k=1.0/sqrt(x0);
  v0=K_over_Kdash(k);
  c=4*EPSILON_0/v0;
  l=mu*EPSILON_0/c;
  Zo=sqrt(l/c);
  return(Zo);
}


