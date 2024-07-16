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

void usage_create_any_bitmap()
{
  
  fprintf(stderr,"create_any_bitmap version %s\n\n",PACKAGE_VERSION);
  fprintf(stderr,"Usage: create_any_bitmap commandfile\n\n");
  fprintf(stderr,"where 'commandfile' is a text file, which:\n");
  fprintf(stderr,"a) MUST have a FILENAME command\n");
  fprintf(stderr,"b) MUST have either a BACKGROUND or a GREEN_ENCLOSED_BACKGROUND command\n");
  fprintf(stderr,"c) Must have at least one RECTANGLE or CIRCLE command, but might have several.\n\n");
  fprintf(stderr,"The following is a typical command file, which in this case creates an bitmap\n");
  fprintf(stderr,"called twin-wire-a.bmp, consisting of a rectangle 5000 x 4500 pixels\n");
  fprintf(stderr,"which has a green (0 V) border of 5 pixels in thickness\n");
  fprintf(stderr,"Inside are placed two red (V = +1 V) circular conductors, each of diameter\n");
  fprintf(stderr,"80 pixels which have centres of 2400,2000 and 2600,2000\n\n");
  fprintf(stderr,"FILENAME twin-wire-a.bmp                # Write to file 'twin-wire-a.bmp'\n");
  fprintf(stderr,"GREEN_ENCLOSED_BACKGROUND 5000 4000 1.0 # 5000x4000 image.  Er=1.0 Green border\n");
  fprintf(stderr,"CIRCLE  80 2400 2000  RED               # Red circle, dia 80, centre (2400,2000)\n");
  fprintf(stderr,"CIRCLE  80 2600 2000  RED               # Red circle, dia 80, centre (2600,2000)\n");
}
