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
#include "exit_codes.h"

extern int main(int argc, char **argv) /* Read parameters from command line here   */
{
#ifdef GGG
   int  bmp_size=DEFAULT_BMP_SIZE;
   int q;
   FILE *image_data_fp=stdout;
   struct transmission_line_properties not_used;

   while((q=get_options(argc,argv,"b:f:v")) != -1)
   switch (q) 
   {
      case 'b':
      bmp_size=atol(my_optarg); 
      break;
      case 'v':
      verbose=TRUE; 
      break;
      case '?':
      printf("read a ? exiting\n");
   }
   if(argc-my_optind ==6)
   {

      WW=atof(argv[my_optind]);
      HH=atof(argv[my_optind+1]);
      ww=atof(argv[my_optind+2]);
      cc=atof(argv[my_optind+3]);
      Er1=atof(argv[my_optind+4]);
      if((image_data_fp=fopen(argv[my_optind+5],"wb"))==NULL)
	 exit_and_error("Can't open file for writing",CANT_OPEN_FOR_WRITING);

      /* To make the program easier to write, rect_cen_in_rect uses 
      the same variables as create_bmp_for_rect_in_rect. We just calculate the 
      values not given (a, b, d, h and Er1 from those given
      (W, H, c and w) */

      aa=(WW-ww)/2.0;
      bb=(WW-ww)/2.0;
      dd=ww;
      hh=(HH-cc)/2.0;
      Er2=Er1;
      check_parameters_of_create_bmp_for_rect_in_rect();
      convert_create_bmp_for_rect_in_rect_dimensions_to_integers(bmp_size);
      write_bitmap(image_data_fp, not_used);
   }
   else
      usage_create_bmp_for_rect_cen_in_rect();
   return(0);
#endif 
  exit_with_msg_and_exit_code("This program is not implemented", PROGRAM_NOT_IMPLEMENTED);
return(0);
}
