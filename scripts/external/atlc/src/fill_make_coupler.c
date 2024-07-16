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

extern int W, H, w,  s, verbose;

void fill_image_vector_with_data(unsigned char *image_vector, int colour_Er1, int colour_Er2, struct transmission_line_properties data) 
{
   int i, j, vector_original=0;
   unsigned char red, green, blue;
   int left_edge_blue;
   int left_edge_red;
   left_edge_red=W/2 - w -s/2;
   left_edge_blue=(W+s)/2;
   if(verbose >=2)
     printf("\nw=%d s=%d W=%d H=%d Er1=%x Er2=%x in fill..data for couplers\n", w, s, W, H,colour_Er1, colour_Er2);
   for(j=0;j<H;++j)
   {
      for(i=0;i<W; ++i)
      {
         red=colour_Er1/(256*256); /* Fill in areas with Er1 */
         green=colour_Er1/256;
         blue=colour_Er1%256;

	 /* Put a small border in green. Only one pixel is needed, but
	 I'll put a few more. */

         if( (j<BORDER) || (j>=H-BORDER))
	 {
	    red=0x00;
	    green=0xff;
	    blue=0x00;
         }
	 if( (i>=left_edge_blue) && (i<left_edge_blue+w) && j==(H/2)) /* conductor */
	 {
	    red=0x00;
	    green=0x00;
	    blue=0xff;
         }
	 if( (i>=left_edge_red) && (i<left_edge_red+w) && j==(H/2)) /* conductor */
	 {
	    red=0xff;
	    green=0x00;
	    blue=0x00;
         }
	 image_vector[vector_original]=blue;
	 image_vector[vector_original+1]=green;
	 image_vector[vector_original+2]=red;
         vector_original+=3;
      }
   }
}
