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

void usage_create_bmp_for_rect_in_rect(void)
{
      fprintf(stderr,"Usage: create_bmp_for_rect_in_rect [-b bmp_size] [-f outfile] [-v] W H a b c d w h Er1 Er2 outfile.bmp\n\n");
      fprintf(stderr,"Version %s\n",PACKAGE_VERSION);
      fprintf(stderr,"where W, H, a, b, c, d, w, and h  are all in mm or all in inches\n");      
      fprintf(stderr,"(they *must* use the same units. Non-integers allowed for all parameters)\n");
      fprintf(stderr,"outfile.bmp is the name of a file to writ the bitmap to\n");
      fprintf(stderr,"Options are:\n");
      fprintf(stderr,"  -C         \n     Print copyright, licencing and distribution information.\n");
      fprintf(stderr,"  -b bmp_size\n     Sets the size of the bitmap, in the range 1 to 15 (default %d).\n",DEFAULT_BMP_SIZE);
      fprintf(stderr,"  -v         \n     Write diagnostic information to stderr\n");
      fprintf(stderr,"-----------------------------------------------------------------------  ^\n");
      fprintf(stderr,"|                                                                     |  |\n");
      fprintf(stderr,"|               Dielectric, permittivity=Er1                          |  |\n");
      fprintf(stderr,"|                                                                     |  |\n");
      fprintf(stderr,"|       <----------------d------------------------->                  |  |\n");
      fprintf(stderr,"|                                                                     |  |\n");
      fprintf(stderr,"|             <----------w----------->                                |  |\n");
      fprintf(stderr,"|             ------------------------   ^                            |  |\n");
      fprintf(stderr,"|             |                      |   |                            |  |\n");
      fprintf(stderr,"|             |  Metallic conductor  |   |                            |  H\n");
      fprintf(stderr,"|<-----b----->|  conductor (can be   |   c                            |  |\n");
      fprintf(stderr,"|             |  off-centre)         |   |                            |  |\n");
      fprintf(stderr,"|             |                      |   |                            |  |\n");
      fprintf(stderr,"|       |------------------------------------------- ^                |  |\n");
      fprintf(stderr,"|       |..........................................| |                |  |\n");
      fprintf(stderr,"|       |.....Dielectric, permittivity=Er2.........| |                |  |\n");
      fprintf(stderr,"|<--a-->|.......(can be off centre )...............| h                |  |\n");
      fprintf(stderr,"|       |..........................................| |                |  |\n");
      fprintf(stderr,"|       |..........................................| |                |  |\n");
      fprintf(stderr,"-----------------------------------------------------------------------  |\n");
      fprintf(stderr,"<----------------------------------W--------------------------------->\n\n");
      fprintf(stderr,"Eg: create_bmp_for_rect_in_rect 250 100 20 100 4.25 205 45 15 1.0006 3.7 ms.bmp \n");
      exit_with_msg_and_exit_code("",PROGRAM_CALLED_WITH_WRONG_NUMBER_OF_ARGUMENTS);
}
