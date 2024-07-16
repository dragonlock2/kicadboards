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

void usage_create_bmp_for_stripline_coupler(void)
{
  fprintf(stderr,"Usage: create_bmp_for_stripline_coupler [-C] [-b bitmapsize] [-v] H w s Er filename\n\n");
  fprintf(stderr,"Version %s\n",PACKAGE_VERSION);
  fprintf(stderr,"Options:\n");
  fprintf(stderr,"         -C\n");
  fprintf(stderr,"            Print copyright, licencing and distribution information\n");
  fprintf(stderr,"         -b  bitmapsize\n");
  fprintf(stderr,"            Set the size of the bitmap to about 2^bitmapsize bytes\n");
  fprintf(stderr,"         -v\n");
  fprintf(stderr,"            Prints the theoretical impedances too - good for verifying atlc\n");
  fprintf(stderr,"------------^------------------------------------------------------------------\n");
  fprintf(stderr,"            |                                               \n");
  fprintf(stderr,"            |              <---w---><-----s----><---w-->\n");
  fprintf(stderr,"            H              ---------            --------\n");
  fprintf(stderr,"            |                                      \n");
  fprintf(stderr,"            |   Er                          \n");
  fprintf(stderr,"------------v------------------------------------------------------------------\n");
  fprintf(stderr,"e.g. create_bmp_for_stripline_coupler  1.23 0.7 1.2 1.0 coupler.bmp\n");
  fprintf(stderr,"e.g. create_bmp_for_stripline_coupler -b 8 1.23 0.7 1.0 1.0 smaller.bmp\n");
  fprintf(stderr,"e.g. create_bmp_for_stripline_coupler -v 12 1.23 0.7 1.006  air.bmp\n");
  fprintf(stderr,"\nThe default bitmap_bitmap size b is %d. Files will be between 2^(b-1)\n", DEFAULT_COUPLER_BMP_SIZE);
  fprintf(stderr,"and 2^(b+1) bytes in length\n");
}
