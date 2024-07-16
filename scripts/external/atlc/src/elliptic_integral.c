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

#include "config.h"

#include "definitions.h"

/* The following function computes:

r=K(k)/K'(k) where
K is the complete elliptic integral of the first kind,
K' is the complementary complete elliptic integral of the first kind

This simple routine was given to my by Dan  - it is one hell
of a lot simplier than the routine in the numerical recipes book

*/

double K_over_Kdash(double k)
{
  double kp, r, kf;
  kp = sqrt(1.0-pow(k,2.0));
  r = 1.0;
  kf=(1.0+k)/(1.0+kp);
  while(kf != 1.0)
  {
    r = r*kf;
    k = 2.0*sqrt(k)/(1.0+k);
    kp = 2.0*sqrt(kp)/(1.0+kp);
    kf=(1.0+k)/(1.0+kp);
  }
  return(r);
}
