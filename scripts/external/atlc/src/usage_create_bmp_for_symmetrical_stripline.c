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

void usage_create_bmp_for_symmetrical_stripline(void)
{
  fprintf(stderr,"create_bmp_for_symmetrical_stripline produces a bitmap for a wide stripline and \ncan calculate Zo ASSUMING IT IT INFINITELY WIDE (which it is not of course) if the -v option is added.\n\n");
  fprintf(stderr,"Version %s\n",PACKAGE_VERSION);
  fprintf(stderr,"Usage: usage_create_bmp_for_symmetrical_stripline [-C][-v] W H w filename\n\n");
  fprintf(stderr,"---------^-----------------------------------------------------\n");
  fprintf(stderr,"         |                                     \n");
  fprintf(stderr,"         |         <----------w----------->\n");
  fprintf(stderr,"         H         ------------------------\n");
  fprintf(stderr,"         |                              \n");
  fprintf(stderr,"         |                              \n");
  fprintf(stderr,"---------v-----------------------------------------------------\n");
  fprintf(stderr,"<-----------------------------W-------------------------------->\n\n");
  fprintf(stderr,"Option:\n");
  fprintf(stderr,"     -C      Print copyright, licensing and distribution information.\n");
  fprintf(stderr,"     -i      Force the width W to be effectively infinite.\n");
  fprintf(stderr,"     -v      Compute the theoretical impedance and print to stdout.\n\n");
  fprintf(stderr,"WARNING create_bmp_for_symmetrical_stripline  does *NOT* take floating points for W, H and w. You must\n");
  fprintf(stderr,"enter only integers. The program was put together quickly, so does NOT\n");
  fprintf(stderr,"automatically convert floating point values to integers like create_bmp_for_rect_in_rect,\n");
  fprintf(stderr,"create_bmp_for_circ_in_circ, create_bmp_for_circ_in_rect, create_bmp_for_rect_cen_in_rect\n");
  fprintf(stderr,"create_bmp_for_microstrip_coupler and create_bmp_for_stripline_coupler\n");
}
