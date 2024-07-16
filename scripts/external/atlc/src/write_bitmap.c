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
#include "Erdata.h" 

/* names, colours and Ers are all arrays of 10. It would be better they were 
in a structure as they are all linked closely, but they are not and I
can't be bothered to change it */

extern int W, H;

void write_bitmap(FILE *image_data_fp, struct transmission_line_properties xyz)
{
   int colour_Er1=-1, colour_Er2=-1, vector_aligned;
#ifndef HAVE_MEMSET
   int memory_location;
#endif
   unsigned char *image_data, *unaligned_image_vector;

   get_Er1_and_Er2_colours(&colour_Er1, &colour_Er2);
   W+=2*BORDER;
   H+=2*BORDER;
   xyz.W+=2*BORDER;
   xyz.H+=2*BORDER;
   /* We create an vector big enough for the image. Since rows are 
   aligned on 4-byte boundaries, we need to allow suffient space for
   (W+2)*(H-1) bytes. */

   /* when aligning data on 4-byte boundaries, the 
   padding must be filled with 0's, to meet the 
   .bmp standard */

   image_data=ustring(0,(W+3)*3*H);
   unaligned_image_vector=ustring(0,(W+3)*3*H);

#ifdef HAVE_MEMSET
   (void) memset((void *) (image_data),0x0,(size_t) ((W+3)*3*H));
#else
   for(memory_location=0; memory_location < (W+3)*3*H; ++ memory_location)
     image_data[memory_location]=0;
#endif /* end of #ifdef HAVE_MEMSET */


   /* Fill a vector with the initial (original) data on the 
   tline. This is not aligned in any way */
   /* The following function 'fill_image_vector_with_data' is *not* in the file
   fill_image_vector_with_data.c, but instead different versions of it are 
   located in files fill_rect_with_rect.c, fill_circ_with_circ.c, 
   fill_rect_with_circ.c and fill_circ_with_rect.c */
   fill_image_vector_with_data(unaligned_image_vector, colour_Er1, colour_Er2, xyz);
   
   /* put into the vector, in reverse order - i.e. from bottom to top and 
   align each row on 4-byte boundaries */
   vector_aligned=align_bitmap_image(W, H, unaligned_image_vector,image_data);
   write_bitmap_out(image_data, image_data_fp,vector_aligned, W, H);
}
