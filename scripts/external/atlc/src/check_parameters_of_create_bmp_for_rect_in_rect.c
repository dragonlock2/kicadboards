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


#ifdef HAVE_STDLIB_H
#include <stdlib.h>
#endif  

#include "definitions.h"


/* These items are supplied on the command line */

extern double WW, HH, aa, bb, cc, dd, ww, hh, Er1, Er2;
extern int W, H, a, b, c, d, w, h;
extern int verbose;

void check_parameters_of_create_bmp_for_rect_in_rect(void)
{
   if( (Er1<1.0) || (Er2 <1.0))
      exit_with_msg_and_exit_code((char *) "Both Er1  and Er2 must be >= 1.0",100);
   if(aa+dd>WW)
      exit_with_msg_and_exit_code((char *) "the dielectric extends horizontally outside the box (a+d>W)",100);
   if(bb+ww>=WW)
      exit_with_msg_and_exit_code((char *) "the inner conductor extends horizontally beyond the outer conductor(b+w>=W)",101);
   if(cc<=0.0)
      exit_with_msg_and_exit_code((char *) "The inner conductors's thickness (c) must be greater than zero ",12);
   if(hh<=0.0)
      exit_with_msg_and_exit_code((char *) "The thickness of dielectric Er2 (h) must be greater than zero ",12);
   if(hh+cc>=HH)
      exit_with_msg_and_exit_code((char *) "the inner conductor extends verticaly beyond the outer conductor(c+h>=H)",101);
   if((WW<=0.0) || (HH<=0.0) || (aa<0.0) || (bb<0.0) || (cc<=0.0) || (dd<=0.0)
   ||(ww<=0.0) || (hh<=0.0))
      exit_with_msg_and_exit_code((char *) "W,H,c,d,w, & h must be positive numbers. Non-integers are okay, but they must be >0 \n",102); 
      
}

void check_create_bmp_for_rect_in_circ_int(void)
{
   if(verbose==TRUE)
      fprintf(stderr,"W=%d H=%d a=%d b=%d c=%d d=%d w=%d h=%d\n",W,H,a,b,c,d,w,h);
   if(a < 1)
      exit_with_msg_and_exit_code("internal paramter 'a' is less that 1. This indicates the LHS of the dielectric",102); 
}
