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

extern double Er1, Er2;
extern double Ers[];
extern int colours[];

void convert_create_create_bmp_for_coupled_microstrip_dimensions_to_integers(struct transmission_line_properties *pcb)
{
   /* A number of paramters are set to -1, as otherwise the compiler   
   complains they may be used unitialised. It is wise to check they
   are not -1 before assining a variable to their contents, 
   but I can't be bothered. */
   int best_W=-1, best_H=-1, best_w=-1, best_s=-1, best_g=-1;
   int best_h=-1, best_t=-1;
   int min, max, lowest =  2500, highest=10000;
   int i;
   double max_gridsize, min_gridsize;
   double error, error_min=VERY_LARGE, gridsize=-1, best_grid_size=-1;


   /* scale grid size,  according to a command line option */
   lowest*=(int) 0.5+pow(2.0,(double)pcb->bmp_size);
   highest*=(int) 0.5+pow(2.0,(double)pcb->bmp_size);

   max_gridsize=sqrt(pcb->WW*pcb->HH/(double )lowest);  /* minimum dimension in m */
   min_gridsize=sqrt(pcb->WW*pcb->HH/(double )highest);
   if(pcb->WW>=pcb->HH)
   {
      min=pcb->WW/max_gridsize;
      max=pcb->WW/min_gridsize;
   }
   else
   {
      min=pcb->HH/max_gridsize;
      max=pcb->HH/min_gridsize;
   }
   if (pcb->verbose_level >= 2)
     printf("WW=%f HH=%f lowest=%d higherst = %d min=%d max=%d\n",pcb->WW,pcb->HH,lowest, highest, min, max);
   for(i=min;i<=max;++i)
   {
      /* Try various combinations for  H,a,b,c, etc */
      if(pcb->W>pcb->H)
         gridsize=pcb->WW/i;
      else
         gridsize=pcb->HH/i;
      pcb->W=(int)(pcb->WW/gridsize + 0.5);
      pcb->H=(int)(pcb->HH/gridsize + 0.5);
      pcb->w=(int)(pcb->ww/gridsize + 0.5);
      pcb->s=(int)(pcb->ss/gridsize + 0.5);
      pcb->g=(int)(pcb->gg/gridsize + 0.5);
      pcb->h=(int)(pcb->hh/gridsize + 0.5);
      pcb->t=(int)(pcb->tt/gridsize + 0.5);
      error=0.0;
      /*error+=pow((pcb->WW-pcb->W*gridsize)/pcb->WW,2.0); */ /* relative error in W */
      /*error+=pow((pcb->HH-pcb->H*gridsize)/pcb->HH,2.0); */ 
      if(pcb->w>0)
         error+=pow((pcb->ww-pcb->w*gridsize)/pcb->ww,2.0);
      if(pcb->s>0)
          error+=pow((pcb->ss-pcb->s*gridsize)/pcb->ss,2.0);
      if(pcb->g>0)
          error+=pow((pcb->gg-pcb->g*gridsize)/pcb->gg,2.0);
      if(pcb->h>0)
          error+=pow((pcb->hh-pcb->h*gridsize)/pcb->hh,2.0);
      if(pcb->t>0)
          error+=pow((pcb->tt-pcb->t*gridsize)/pcb->tt,2.0);
      if(error < (error_min-TINY))
      {
          error_min=error;
          best_W=pcb->W;
          best_H=pcb->H;
          best_w=pcb->w;
          best_s=pcb->s;
          best_g=pcb->g;
          best_h=pcb->h;
          best_t=pcb->t;
          best_grid_size=gridsize;
      }
   }
   pcb->W=best_W;
   pcb->H=best_H;
   pcb->w=best_w;
   pcb->s=best_s;
   pcb->g=best_g;
   pcb->h=best_h;
   pcb->t=best_t;
   if(pcb->verbose_level > 0)
   {
      fprintf(stderr,"error_min=%.16f\n",error_min);
      fprintf(stderr,"User requested: W=%f H=%f w=%f s=%f g=%f h=%f t=%f Er1=%f Er2=%f\n\n",pcb->WW,pcb->HH,pcb->ww,pcb->ss,pcb->gg,pcb->hh,pcb->tt,Er1,Er2);
      fprintf(stderr,"Internally the program is using the following grid:\n");
      fprintf(stderr,"W=%d H=%d w=%d s=%d g=%d h=%d t=%d\nThe  grid size is %f mm, inches or whatever\n\n", pcb->W, pcb->H, pcb->w, pcb->s, pcb->g,pcb->h, pcb->t,best_grid_size);
      if(error_min > TINY)
      {
         fprintf(stderr,"This means we are simulating a transmission line with these dimensions:\n");
         fprintf(stderr,"W=%f H=%f w=%f s=%f g=%f h=%f t=%f (mm, inches or whatever)\n",pcb->W*best_grid_size,pcb->H*best_grid_size,pcb->w*best_grid_size,pcb->s*best_grid_size,pcb->g*best_grid_size,pcb->h*best_grid_size,pcb->t*best_grid_size);
         fprintf(stderr,"\nThese are slightly different to what you indicated on the command line,\n");
         fprintf(stderr,"but they are the best approximation possible, given the grid size\n");
      }
   }
   if(pcb->s == 0)
   {
      fprintf(stderr,"Error #12. The gap between the two conductors coupled lines (s) is too small. Either increase the bitmap size (-b option), or make s at least %f\n",gridsize);
      exit_with_msg_and_exit_code("",GAP_BETWEEN_CONDUCTORS_TOO_SMALL);
   }
   if(pcb->g == 0)
   {
      fprintf(stderr,"Error #13. The gap between the groundplane (g) and coupled lines is too small. Either increase the bitmap size (-b option), or make g at least %f\n",gridsize);
      exit_with_msg_and_exit_code("",GAP_BETWEEN_CONDUCTORS_TOO_SMALL);
   }
   if(pcb->h == 0)
   {
      fprintf(stderr,"Error #14. The thickness of the dielectric of Er2 (h) is too small. Either increase the bitmap size (-b option), or make h at least %f\n",gridsize);
      exit_with_msg_and_exit_code("",GAP_BETWEEN_CONDUCTORS_TOO_SMALL);
   }
   check_error(pcb->WW,pcb->W,best_grid_size,"W");
   check_error(pcb->HH,pcb->H,best_grid_size,"H");
   check_error(pcb->ww,pcb->w,best_grid_size,"w");
   check_error(pcb->ss,pcb->s,best_grid_size,"s");
   check_error(pcb->gg,pcb->g,best_grid_size,"g");
   check_error(pcb->hh,pcb->h,best_grid_size,"h");
   check_error(pcb->tt,pcb->t,best_grid_size,"t");
}
