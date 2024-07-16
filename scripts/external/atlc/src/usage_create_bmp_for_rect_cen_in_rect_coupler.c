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
#include "exit_codes.h"

void usage_create_bmp_for_rect_cen_in_rect_coupler(void)
{
      fprintf(stderr,"Usage: rect_cen_in_rect [-b bmp_size] [-f outfile] [-v] W H w h Er1 outfile.bmp\n\n");
      fprintf(stderr,"Version %s\n",PACKAGE_VERSION);
      fprintf(stderr,"outfile.bmp is the file to write the bitmap to\n");      
      fprintf(stderr,"W, H, w, and h  are all in mm or all in inches\n");      
      fprintf(stderr,"(they *must* use the same units. Non-integers allowed for all parameters)\n");
      fprintf(stderr,"options are:\n");
      fprintf(stderr,"  -b bmp_size\n     Sets the size of the bitmap, in the range 1 to 15 (default %d).\n",DEFAULT_BMP_SIZE);
      fprintf(stderr,"  -v         \n     Write diagnostic information to stdout\n");
      fprintf(stderr,"-----------------------------------------------------  ^\n");
      fprintf(stderr,"|                                                   |  |\n");
      fprintf(stderr,"|     Er1     <----------w----------->              |  |\n");
      fprintf(stderr,"|             ------------------------   ^          |  |\n");
      fprintf(stderr,"|             |                      |   |          |  |\n");
      fprintf(stderr,"|             |  Metallic conductor  |   |          |  H\n");
      fprintf(stderr,"|             |  conductor (centred  |   h          |  |\n");
      fprintf(stderr,"|             |  vertically and      |   |          |  |\n");
      fprintf(stderr,"|             |  horizontally)       |   |          |  |\n");
      fprintf(stderr,"|             ------------------------              |  |\n");
      fprintf(stderr,"|                                                   |  |\n");
      fprintf(stderr,"-----------------------------------------------------  |\n");
      fprintf(stderr,"<-------------------------W------------------------->\n\n");
      fprintf(stderr,"Eg: create_bmp_for_rect_cen_in_rect 200 100 30 30 1.0 foo.bmp\n\n");

      exit_with_msg_and_exit_code("",PROGRAM_CALLED_WITH_WRONG_NUMBER_OF_ARGUMENTS); 
}
