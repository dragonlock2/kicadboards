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

void fill_image_vector_with_data(unsigned char *image_vector, int colour_Er1, int colour_Er2, struct transmission_line_properties pcb)
{
   int i, j, red=0, green=0, blue=0, vector_original=0;
   int right_edge_of_LH_GP;
   for(j=0;j<pcb.H;++j)
   {
      for(i=0;i<pcb.W; ++i)
      {

	 red=colour_Er1/(256*256); /* Fill whole region with Er1 (normally vacuum/air)*/
	 green=colour_Er1/256;
	 blue=colour_Er1%256;

	 /* Put a small border in green. Only one pixel is needed, but
	 I'll put a few more. */
         if( (i<BORDER) || (i>pcb.W-BORDER-1) || (j<BORDER) || (j>pcb.H-BORDER-1))
	 {
	    red=0x00;
	    green=0xff;
	    blue=0x00;
         }

	 /* Put the dielectric for the PCB in */
	 if((i >= BORDER) && (i <pcb.W-BORDER ) && (j >= BORDER) && (j < pcb.h+BORDER))
	 {
	   red=colour_Er2/(256*256); /* Fill in areas with Er2 (normally PCB substrate)*/
	   green=colour_Er2/256;
	   blue=colour_Er2%256;
	 }

	 /* Put the metal top LH surface of the PCB groundplane */
	 right_edge_of_LH_GP=(pcb.W/2-pcb.s/2-pcb.w-pcb.g)-BORDER;
	 if((i >= BORDER) && (i <=right_edge_of_LH_GP ) && (j >= pcb.h+BORDER) && (j < pcb.h+pcb.t+BORDER))
	 {
	   red=0; /* Fill in left hand groundplane on top of pcb */ 
	   green=255;
	   blue=0;
	 }
	 /* Left hand coupler, could be +1 V or -1 V it does not matter, as long as right one is opposite */
	 if( (i > right_edge_of_LH_GP + pcb.g ) && (i <= right_edge_of_LH_GP + pcb.g+pcb.w) && (j >= pcb.h+BORDER) && (j < pcb.h+pcb.t+BORDER))
	 {
	   red=0xff;  /* Left hand coupler made to be +1 V */
	   green=0;
	   blue=0;
	 }
	 /* Right and coupler, set to -1 V */
	 if( (i > right_edge_of_LH_GP + pcb.g +pcb.w+pcb.s) && (i <= right_edge_of_LH_GP + pcb.g+pcb.w+pcb.s+pcb.w) && (j >= pcb.h+BORDER) && (j < pcb.h+pcb.t+BORDER))
	 {
	   red=0;  /* Right hand coupler made to be -1 V */
	   green=0;
	   blue=0xff;
         }
	 if( (i > right_edge_of_LH_GP + pcb.g+pcb.w+pcb.s+pcb.w+pcb.g) && (i <= pcb.W-BORDER) && (j >= pcb.h+BORDER) && (j < pcb.h+pcb.t+BORDER))
	 {
	   red=0;  /* Right hand ground plane in place */
	   green=0xff;
	   blue=0;
         }
	 image_vector[vector_original]=blue;
	 image_vector[vector_original+1]=green;
	 image_vector[vector_original+2]=red;
         vector_original+=3;
      }
   }
}
