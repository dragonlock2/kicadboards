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


#ifdef HAVE_STRING_H
#include <string.h>
#endif

#ifdef HAVE_STRINGS_H
#include <strings.h>
#endif

#ifdef HAVE_STDLIB_H
#include <stdlib.h>
#endif

#ifdef HAVE_MATH_H
#include <math.h>
#endif

#include "definitions.h"
#include "exit_codes.h"

/* names, colours and Ers are all arrays of 10. It would be better they were 
in a structure as they are all linked closely, but they are not and I
can't be bothered to change it */

extern double WW, HH, aa, bb, cc, dd, ww, hh, Er1, Er2;
extern int W, H, a, b, c, d, w, h;
extern int verbose;
extern int lowest;
extern int highest;

void convert_create_bmp_for_rect_in_rect_dimensions_to_integers(int accuracy_level) 
{
   /* A number of paramters are set to -1, as otherwise the compiler   
   complaings they may be used unitialised. It is wise to check they
   are not -1 before assining a variable to their contents, 
   but I can't be bothered. */
   int best_W=-1, best_H=-1, best_a=-1, best_b=-1, best_c=-1;
   int best_d=-1, best_w=-1, best_h=-1;
   int min, max;
   int i;
   double max_gridsize, min_gridsize;
   double error, error_min=VERY_LARGE, gridsize=-1, best_grid_size=-1;

   /* scale grid size,  according to a command line option */
   /*lowest*=(int) 0.5+pow(2,accuracy_level); */
   /*highest*=(int) 0.5+pow(2,accuracy_level); */
   lowest*=1<<accuracy_level;
   highest*=1<<accuracy_level;

   max_gridsize=sqrt(WW*HH/(double )lowest);  /* minimum dimension in m */
   min_gridsize=sqrt(WW*HH/(double )highest);
   if(WW>=HH)
   {
      min=WW/max_gridsize;
      max=WW/min_gridsize;
   }
   else
   {
      min=HH/max_gridsize;
      max=HH/min_gridsize;
   }
   for(i=min;i<=max;++i)
   {
      /* Try various combinations for  H,a,b,c, etc */
      if(W>H)
         gridsize=WW/i;
      else
         gridsize=HH/i;
      W=(int)(WW/gridsize + 0.5);
      H=(int)(HH/gridsize + 0.5);
      a=(int)(aa/gridsize + 0.5);
      b=(int)(bb/gridsize + 0.5);
      c=(int)(cc/gridsize + 0.5);
      d=(int)(dd/gridsize + 0.5);
      w=(int)(ww/gridsize + 0.5);
      h=(int)(hh/gridsize + 0.5);
      error=0.0;
      error+=pow((WW-W*gridsize)/WW,2.0); /* relative error in W */
      error+=pow((HH-H*gridsize)/HH,2.0);
      if(a>0)
         error+=pow((aa-a*gridsize)/aa,2.0);
      if(b>0)
          error+=pow((bb-b*gridsize)/bb,2.0);
      if(c>0)
          error+=pow((cc-c*gridsize)/cc,2.0);
      if(d>0)
          error+=pow((dd-d*gridsize)/dd,2.0);
      if(w>0)
          error+=pow((ww-w*gridsize)/ww,2.0);
      if(h>0)
          error+=pow((hh-h*gridsize)/hh,2.0);
      if(error < (error_min-TINY))
      {
          error_min=error;
          best_W=W;
          best_H=H;
          best_a=a;
          best_b=b;
          best_c=c;
          best_d=d;
          best_w=w;
          best_h=h;
          best_grid_size=gridsize;
      }
   }
   W=best_W;
   H=best_H;
   a=best_a;
   b=best_b;
   c=best_c;
   d=best_d;
   w=best_w;
   h=best_h;
   if(verbose==TRUE)
   {
      fprintf(stderr,"error_min=%.16f\n",error_min);
      fprintf(stderr,"User requested: WW=%f HH=%f a=%f b=%f c=%f\nd=%f w=%f h=%fEr1=%f Er2=%f\n\n",WW,HH,aa,bb,cc,dd,ww,hh,Er1,Er2);
      fprintf(stderr,"Internally the program is using the following grid:\n");
      fprintf(stderr,"W=%d H=%d a=%d b=%d c=%d d=%d w=%d h=%d. \nThe  grid size is %f mm, inches or whatever\n\n", W, H, a, b, c, d, w, h,best_grid_size);
      if(error_min > TINY)
      {
         fprintf(stderr,"This means we are simulating a transmission line with these dimensions:\n");
         fprintf(stderr,"W=%f H=%f a=%f b=%f c=%f d=%f\nw=%f h=%f (mm, inches or whatever)\n",W*best_grid_size,H*best_grid_size,a*best_grid_size,b*best_grid_size,c*best_grid_size,d*best_grid_size,w*best_grid_size,h*best_grid_size);
         fprintf(stderr,"\nThese are slightly different to what you indicated on the command line,\n");
         fprintf(stderr,"but they are the best approximation possible, given the grid size\n");
      }
   }
   if(b == 0)
   {
      fprintf(stderr,"Error #12. The gap between the two conductors (b) is too small. Either increase the bitmap size (-b option), or make b at least %f\n",gridsize);
      exit_with_msg_and_exit_code("",GAP_BETWEEN_CONDUCTORS_TOO_SMALL);
   }
   if(c == 0)
   {
      fprintf(stderr,"Error #13. The thickness of the inner conductor (c) is too small. Either increase the bitmap size (-b option), or make c at least %f\n",gridsize);
      exit_with_msg_and_exit_code("",GAP_BETWEEN_CONDUCTORS_TOO_SMALL);
   }
   if(h == 0)
   {
      fprintf(stderr,"Error #14. The thickness of the dielectric of Er2 (h) is too small. Either increase the bitmap size (-b option), or make h at least %f\n",gridsize);
      exit_with_msg_and_exit_code("",GAP_BETWEEN_CONDUCTORS_TOO_SMALL);
   }
   check_error(WW,W,best_grid_size,"W");
   check_error(HH,H,best_grid_size,"H");
   check_error(aa,a,best_grid_size,"a");
   check_error(bb,b,best_grid_size,"b");
   check_error(cc,c,best_grid_size,"c");
   check_error(dd,d,best_grid_size,"d");
   check_error(ww,w,best_grid_size,"w");
   check_error(hh,h,best_grid_size,"h");
}
