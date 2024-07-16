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

#ifdef HAVE_MATH_H
#include <math.h>
#endif

#ifdef HAVE_STRING_H
#include <string.h>
#endif

#ifdef HAVE_STRINGS_H
#include <strings.h>
#endif

#include "exit_codes.h"
#include "definitions.h"

#ifdef WINDOWS
#pragma hrdstop
#include <condefs.h>
#endif

double aa, bb, cc, dd, hh, ww, DD, WW, HH, Er1, Er2;
int a, b, c, d, h, w, D, W, H;

int verbose=FALSE;
int lowest=50, highest=100;

/* The following are only needed so that I can link in both 
convert_create_bmp_for_circ_in_circ_dimensions_to_integers.c
and convert_create_bmp_for_rect_in_rect_dimensions_to_integers.c
*/


int main(int argc, char **argv) /* Read parameters from command line here   */
{
   int  bmp_size=DEFAULT_BMP_SIZE;
   int q;
   FILE *image_data_fp;
   char *filename;
   struct transmission_line_properties not_used;
   double Zo, x;
   filename=string(0,1010);

   /* The following line just prevents a warning from the compiler (SGI's to 
   be precise). There is not reason to set W=1 */
   not_used.W=1;

   while((q=get_options(argc,argv,"Cb:v")) != -1)
   switch (q) 
   {
      case 'C': 
	print_copyright((char *) "2002");
	exit_with_msg_and_exit_code("",OKAY);
      break;
      case 'b':
      bmp_size=atol(my_optarg); 
      break;
      case 'v':
      verbose=TRUE; 
      break;
      case '?':
      break;
   }
   if(argc-my_optind == 5)
   {
      DD=atof(argv[my_optind]);
      WW=HH=DD;
      dd=atof(argv[my_optind+1]);
      hh=atof(argv[my_optind+2]);
      Er1=atof(argv[my_optind+3]);
      if( dd > DD)
	exit_with_msg_and_exit_code("Error: The Inner conductor is larger than the outer conductor!!!", 1);
      else if (DD == dd) 
	exit_with_msg_and_exit_code("Error: The inner and outer conductors are of the same size!!!", 1);
      else if (dd/2 + hh >= DD/2)
	exit_with_msg_and_exit_code("Error: The inner and outer conductors will touch!!!", 1);
      filename=strncpy(filename, argv[my_optind+4],1000);
      if( (image_data_fp=fopen(filename,"wb")) == NULL)
	exit_with_msg_and_exit_code("Can't open file in create_bmp_for_circ_in_circ.c", CANT_OPEN_FOR_WRITING);
      check_parameters_of_create_bmp_for_circ_in_circ();
      convert_create_bmp_for_circ_in_circ_dimensions_to_integers(bmp_size);
      write_bitmap(image_data_fp, not_used);
      x=(double) (d*d+D*D-4*h*h)/(2*D*d);
      Zo=59.9585*log(x+sqrt(x*x-1))/sqrt(Er1); 
      Zo=log(x+sqrt(x*x-1))/(1000*sqrt(EPSILON_0)*sqrt(Er1)*sqrt(10*M_PI));

      if(verbose == TRUE)
      {
        printf("DD=%f dd=%f hh=%f x=%f\n",DD, dd, hh, x);
        printf("D=%d d=%d h=%d x=%f\n",D, d, h, x);
        printf("Zo is theoretically %f Ohms\n",Zo);
      }
   }
   else
      usage_create_bmp_for_circ_in_circ();
   free_string(filename,0,1010);
   return(OKAY);
}
