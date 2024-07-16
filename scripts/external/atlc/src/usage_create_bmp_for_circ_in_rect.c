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

void usage_create_bmp_for_circ_in_rect(void)
{
      fprintf(stderr,"Usage: create_bmp_for_circ_in_rect [-b bmp_size] [-v] d W H x y Er outputfile\n\n");
      fprintf(stderr,"Version %s\n",PACKAGE_VERSION);
      fprintf(stderr,"Where \n");
      fprintf(stderr,"  d  is the outside diameter of the inner conductor\n");
      fprintf(stderr,"  W  is the horizontal internal dimension of the outer conductor\n");
      fprintf(stderr,"  H  is the vertical internal dimension of the outer conductor\n");
      fprintf(stderr,"  x  is the horizontal offset between the centre of the inner and outer conductors \n");
      fprintf(stderr,"  y  is the vertical offset between the centre of the inner and outer conductors \n");
      fprintf(stderr,"  Er is the relative permittivity of the dielectric.\n");
      fprintf(stderr,"  d, W, H, x and y are either all in mm or all in inches (but not a mixture!!)\n\n");   
      fprintf(stderr,"options are:\n");
      fprintf(stderr,"  -b bmp_size\n     Sets the size of the bitmap, in the range 1 to 15 (default %d).\n",DEFAULT_BMP_SIZE);
      fprintf(stderr,"  -v         \n     Write extra diagnostic information to stdout\n\n");
      fprintf(stderr," --------------------------------------------------------  ^\n");
      fprintf(stderr,"|                                                      |  |\n");
      fprintf(stderr,"|                                                      |  |\n");
      fprintf(stderr,"|                                                      |  |\n");
      fprintf(stderr,"|                                                      |  |\n");
      fprintf(stderr,"|                                                      |  |\n");
      fprintf(stderr,"|           Dielectric, permittivity=Er                |  |\n");
      fprintf(stderr,"|                                                      |  |\n");
      fprintf(stderr,"|                                                      |  |\n");
      fprintf(stderr,"|                                                      |  |\n");
      fprintf(stderr,"|                                                      |  |\n");
      fprintf(stderr,"|         <------x------> ^                            |  H\n");
      fprintf(stderr,"|       *****             |                            |  |\n");
      fprintf(stderr,"|    ***********          y                            |  |\n");
      fprintf(stderr,"|   *************         |                            |  |\n");
      fprintf(stderr,"|   **************        |                            |  |\n");
      fprintf(stderr,"|   <-----d------>        v                            |  |\n");
      fprintf(stderr,"|   **************                                     |  |\n");
      fprintf(stderr,"|   *************                                      |  |\n");
      fprintf(stderr,"|    ***********                                       |  |\n");
      fprintf(stderr,"|        ***                                           |  |\n");
      fprintf(stderr,"|                                                      |  |\n");
      fprintf(stderr,"-------------------------------------------------------   v\n");
      fprintf(stderr,"<---------------------------W-------------------------->\n");
      fprintf(stderr,"                                     ***\n\n");
      fprintf(stderr,"Example: create_bmp_for_circ_in_rect 20 100 150 25 10 3.7 foo.bmp\n");
      exit_with_msg_and_exit_code("",PROGRAM_CALLED_WITH_WRONG_NUMBER_OF_ARGUMENTS);
}
