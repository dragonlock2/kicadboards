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

#ifdef HAVE_STRING_H
#include <string.h>
#endif

#ifdef HAVE_STRINGS_H
#include <strings.h>
#endif

#ifdef HAVE_STDLIB_H
#include <stdlib.h>
#endif

#include "definitions.h"

extern int d, W, H, x, y;

void fill_image_vector_with_data(unsigned char *image_vector, int colour_Er1, int colour_Er2, struct transmission_line_properties not_used) 
{
   int i, j, vector_original=0;
   unsigned char red, green, blue;
   for(j=0;j<H;++j)
   {
      for(i=0;i<W; ++i)
      {
	 if( (i<BORDER) || (i>=W-BORDER) || (j<BORDER) || (j>=H-BORDER))
	 {
	    red=0x00;
	    green=0xff;
	    blue=0x00;
         }
         else if( pow((double)i-(double)W/2.0-(double) x,2.0) + pow((double)j-(double)H/2.0-(double)y,2.0)<=((double)d*(double)d)/4.0)
	 {
	    red=0xff;
	    green=0x0;
	    blue=0x0;
         }
	 else
	 {
	    red=colour_Er1/(256*256); /* Fill in areas with Er1 */
	    green=colour_Er1/256;
	    blue=colour_Er1%256;
         }
	 image_vector[vector_original]=blue;
	 image_vector[vector_original+1]=green;
	 image_vector[vector_original+2]=red;
         vector_original+=3;
      }
   }
}
