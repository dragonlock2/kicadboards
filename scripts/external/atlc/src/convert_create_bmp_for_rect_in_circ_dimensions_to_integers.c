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
#include "definitions.h"

/* names, colours and Ers are all arrays of 10. It would be better they were 
in a structure as they are all linked closely, but they are not and I
can't be bothered to change it */

extern double DD, ww, hh, xx, yy, Er1;
extern int D, w, h, x, y;
extern int lowest;
extern int highest, verbose;

void convert_create_bmp_for_rect_in_circ_dimensions_to_integers(int accuracy_level) 
{
   int best_D=-1, best_w=-1, best_h=-1, best_x=-1, best_y=-1;
   int min=-1, max=-1;
   int i;
   double error, error_min=VERY_LARGE, gridsize, best_grid_size=-1;

   /* scale grid size,  according to a command line option */
   lowest*=(int) 0.5+pow(2.0,(double) accuracy_level);
   highest*=(int) 0.5+pow(2.0,(double) accuracy_level);

   for(i=min;i<=max;++i)
   {
      /* Try various combinations for  D, w, h, x, & y etc */
      gridsize=DD/i;
      D=(int)(DD/gridsize + 0.5);
      w=(int)(ww/gridsize + 0.5);
      h=(int)(hh/gridsize + 0.5);
      x=(int)(xx/gridsize + 0.5);
      y=(int)(yy/gridsize + 0.5);
      error=0.0;
      error+=pow((DD-D*gridsize)/DD,2.0); /* relative error in D */
      error+=pow((ww-w*gridsize)/ww,2.0);
      error+=pow((hh-h*gridsize)/hh,2.0);
      if(x>0)
         error+=pow((xx-x*gridsize)/xx,2.0);
      if(y>0)
          error+=pow((yy-y*gridsize)/yy,2.0);
      if(error < error_min-TINY)
      {
          error_min=error;
          best_D=D;
          best_w=w;
          best_h=h;
          best_x=x;
          best_y=y;
          best_grid_size=gridsize;
      }
   }
   D=best_D;
   w=best_w;
   h=best_h;
   x=best_x;
   y=best_y;
   if(verbose==TRUE)
   {
      fprintf(stderr,"error_min=%.16f\n",error_min);
      fprintf(stderr,"User requested: D=%f w=%f h=%f x=%f y=%f Er1=%f\n\n",DD,ww,hh,xx,yy,Er1);
      fprintf(stderr,"Internally the program is using the following grid:\n");
      fprintf(stderr,"D=%d w=%d h=%d x=%d y=%d \n", D, w, h, x, y);
      fprintf(stderr,"which equates to dimensions of D=%f w=%f h=%f x=%f y=%f\n", D*gridsize, w*gridsize, h*gridsize, x*gridsize,
      y*gridsize);
      if(error_min > TINY)
      {
         fprintf(stderr,"This means we are simulating a transmission line with these dimensions:\n");
         fprintf(stderr,"W=%f w=%f h=%f x=%f y=%f (mm, inches or whatever)\n",D*best_grid_size,w*best_grid_size,h*best_grid_size,x*best_grid_size,y*best_grid_size);
         fprintf(stderr,"\nThese are slightly different to what you indicated on the command line,\n");
         fprintf(stderr,"but they are the best approximation possible, given the grid size\n");
      }
   }
   check_error(DD,D,best_grid_size,"D");
   check_error(ww,w,best_grid_size,"w");
   check_error(hh,h,best_grid_size,"h");
   check_error(xx,x,best_grid_size,"x");
   check_error(yy,y,best_grid_size,"y");
}
