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
#include "exit_codes.h"


/* names, colours and Ers are all arrays of 10. It would be better they were 
in a structure as they are all linked closely, but they are not and I
can't be bothered to change it */

extern double dd, WW, HH, xx, yy, Er1;
extern int d, W, H, x, y;
extern int lowest;
extern int highest;
extern int verbose;

void convert_create_bmp_for_circ_in_rect_dimensions_to_integers(int accuracy_level) 
{
   int best_d=-1, best_W=-1, best_H=-1, best_x=-1, best_y=-1;
   int min, max;
   int i;
   double max_gridsize, min_gridsize;
   double error, error_min=VERY_LARGE, gridsize, best_grid_size=-1;

   /* scale grid size,  according to a command line option */
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
      /* Try various combinations for  d, W, H, etc */
      if(W>H)
         gridsize=WW/i;
      else
         gridsize=HH/i;
      d=(int)(dd/gridsize + 0.5);
      W=(int)(WW/gridsize + 0.5);
      H=(int)(HH/gridsize + 0.5);
      x=(int)(xx/gridsize + 0.5);
      y=(int)(yy/gridsize + 0.5);
      error=0.0;
      error+=pow((WW-W*gridsize)/WW,2.0); /* relative error in W */
      error+=pow((HH-H*gridsize)/HH,2.0);
      error+=pow((dd-d*gridsize)/dd,2.0);
      if(x>0)
         error+=pow((xx-x*gridsize)/xx,2.0);
      if(y>0)
          error+=pow((yy-y*gridsize)/yy,2.0);
      if(error < (error_min-TINY))
      {
          error_min=error;
          best_d=d;
          best_W=W;
          best_H=H;
          best_x=x;
          best_y=y;
          best_grid_size=gridsize;
      }
   }
   if(best_d==-1) /* it has not been initialised */
      exit_with_msg_and_exit_code("d has not been initialised",VARIABLE_NOT_INITIALISED);
   else
     d=best_d;
   if(best_W==-1) /* it has not been initialised */
      exit_with_msg_and_exit_code("W has not been initialised",VARIABLE_NOT_INITIALISED);
   else
     W=best_W;
   if(best_H==-1) /* it has not been initialised */
      exit_with_msg_and_exit_code("H has not been initialised",VARIABLE_NOT_INITIALISED);
   else
     H=best_H;
   if(best_x==-1) /* it has not been initialised */
      exit_with_msg_and_exit_code("x has not been initialised",VARIABLE_NOT_INITIALISED);
   else
     x=best_x;
   if(best_y==-1) /* it has not been initialised */
      exit_with_msg_and_exit_code("y has not been initialised",VARIABLE_NOT_INITIALISED);
   else
     y=best_y;
   if(verbose==TRUE)
   {
      fprintf(stderr,"error_min=%.16f\n",error_min);
      fprintf(stderr,"User requested: dd=%f WW=%f HH=%f xx=%f yy=%f Er=%f\n\n",dd,WW,HH,xx,yy,Er1);
      fprintf(stderr,"Internally the program is using the following grid:\n");
      fprintf(stderr,"d=%d W=%d H=%d x=%d y=%d \n", d, W, H, x, y);
      fprintf(stderr,"The  grid size is %f mm, inches or whatever\n\n", best_grid_size);
      if(error_min > TINY)
      {
         fprintf(stderr,"This means we are simulating a transmission line with these dimensions:\n");
         fprintf(stderr,"d=%f W=%f H=%f x=%f y=%f (mm, inches or whatever)\n",d*best_grid_size,W*best_grid_size,H*best_grid_size,x*best_grid_size,y*best_grid_size);
         fprintf(stderr,"\nThese are slightly different to what you indicated on the command line,\n");
         fprintf(stderr,"but they are the best approximation possible, given the grid size\n");
      }
   }
   if( (d/2+x >= W) || (d/2+y >=H))
   {
      exit_with_msg_and_exit_code("The gap between the two conductors is too small. Either increase the bitmap size (-b option), or change the dimensions of one the conductors",GAP_BETWEEN_CONDUCTORS_TOO_SMALL);
   }
   check_error(dd,d,best_grid_size,"d");
   check_error(WW,W,best_grid_size,"W");
   check_error(HH,H,best_grid_size,"H");
   check_error(xx,x,best_grid_size,"x");
   check_error(yy,y,best_grid_size,"y");
}
