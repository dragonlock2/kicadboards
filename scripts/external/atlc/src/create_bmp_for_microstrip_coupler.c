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

/* The program create_bmp_for_rect_in_rect is a pre-processor for atlc. It produces bitmaps of rectangular
inner and rectangular outer */
#include "config.h"


#ifdef HAVE_STDLIB_H
#include <stdlib.h>
#endif  

#include "definitions.h"

#ifdef WINDOWS
#pragma hrdstop
#include <condefs.h>
#endif

int W, H; 
double  Er1, Er2;
int main(int argc, char **argv) /* Read parameters from command line here   */
{
   struct transmission_line_properties pcb;
   FILE *image_data_fp;
   int q;
   pcb.verbose_level=0;

   pcb.bmp_size=DEFAULT_BMP_SIZE;
   pcb.WW=-1;
   pcb.HH=-1;

   while((q=get_options(argc,argv,"b:W:H:v")) != -1)
   switch (q) 
   {
      case 'b':
      pcb.bmp_size=atol(my_optarg); 
      break;
      case 'H':
      pcb.HH=atof(my_optarg);
      break;
      case 'W':
      pcb.WW=atof(my_optarg);
      break;
      case 'v':
      pcb.verbose_level++; 
      break;
      case '?':
      printf("read a ? exiting\n");
   }
   if(argc-my_optind ==8)
   {
      pcb.ww=atof(argv[my_optind]);
      pcb.ss=atof(argv[my_optind+1]);
      pcb.gg=atof(argv[my_optind+2]);
      pcb.hh=atof(argv[my_optind+3]);
      pcb.tt=atof(argv[my_optind+4]);
      pcb.Er1=atof(argv[my_optind+5]);
      pcb.Er2=atof(argv[my_optind+6]);
      Er1=pcb.Er1;
      Er2=pcb.Er2;
      if(pcb.WW<0)
        pcb.WW=6*pcb.hh+6*pcb.gg+6*pcb.ww+4*pcb.ss;
      if(pcb.HH<0)
        pcb.HH=6*(pcb.hh+pcb.tt);
      /* Do some sanaity checks */
      check_parameters_of_create_bmp_for_microstrip_coupler(pcb);
      convert_create_create_bmp_for_coupled_microstrip_dimensions_to_integers(&pcb);
      W=pcb.W;
      H=pcb.H;
      image_data_fp=fopen(argv[my_optind+7],"wb");
        /*fprintf(stderr,"ints W=%d H=%d w=%d s=%d g=%d h=%d t=%d\n",pcb.W,pcb.H,pcb.w,pcb.s,pcb.g,pcb.h,pcb.t);*/
      write_bitmap(image_data_fp, pcb);
   }
   else
      usage_create_bmp_for_microstrip_coupler();
   return(0);
}
