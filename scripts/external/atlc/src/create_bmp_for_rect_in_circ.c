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

#ifdef WINDOWS
#pragma hrdstop
#include <condefs.h>
#endif

#include "definitions.h"
#include "exit_codes.h"


double DD, ww, hh, xx, yy, Er1, Er2;
int D, w, h, x, y, W, H;

int verbose=FALSE;
int lowest=2500, highest=10000;
int fileflag=FALSE;

extern int main(int argc, char **argv) /* Read parameters from command line here   */
{
   int  bmp_size=DEFAULT_BMP_SIZE;
   int q;
   struct transmission_line_properties not_used;
   FILE *image_data_fp=stdout;

   not_used.W=1; /* Keeps SGI's MipsPro compiler happy */

   while((q=get_options(argc,argv,"b:f:v")) != -1)
   switch (q) 
   {
      case 'b':
      bmp_size=atol(my_optarg); 
      break;
      case 'f':
      /* By default bitmap image goes to stdout, but we can send to a file 
      with the -f option. */
      if((image_data_fp=fopen(my_optarg,"wb"))==NULL)
      {
	 fprintf(stderr,"Can't write to %s. Exiting ...\n",my_optarg);
	 exit_with_msg_and_exit_code("",CANT_OPEN_FOR_WRITING);
      }
      fileflag=TRUE;
      break;
      case 'v':
      verbose=TRUE; 
      break;
      case '?':
      printf("read a ? exiting\n");
   }
      /*usage_create_bmp_for_rect_in_circ();*/
      fprintf(stderr,"SORRY create_bmp_for_rect_in_circ IS NOT YET WORKING, SO HAS BEEN DISABLED. IT\n");
      exit_with_msg_and_exit_code("BE ENABLED ON A FORTHCOMING VERSION",PROGRAM_NOT_IMPLEMENTED);
   if(argc-my_optind == 6)
   {
      DD=atof(argv[my_optind]);
      ww=atof(argv[my_optind+1]);
      hh=atof(argv[my_optind+2]);
      xx=atof(argv[my_optind+3]);
      yy=atof(argv[my_optind+4]);
      Er1=atof(argv[my_optind+5]);
      check_parameters_of_create_bmp_for_rect_in_circ();
      convert_create_bmp_for_rect_in_circ_dimensions_to_integers(bmp_size);
      write_bitmap(image_data_fp, not_used);
   }
   else
      usage_create_bmp_for_rect_in_circ();
   return(0);
}
