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

/* The function setup_arrays sets the type of a pixel to be dielectric, 
or metal. This routines refines that, setting the type of a pixel to be
some number between 1 and 28 according to where it is located, and what 
is around it. See Green paper to understand what they mean */

#include "config.h"
#include "definitions.h"
#include "exit_codes.h"

extern int width, height;
extern unsigned char **cell_type, **oddity;
extern double **Er;

#ifdef HAVE_STDLIB_H
#include <stdlib.h>
#endif

void set_oddity_value(void) 
{
  int i, j;
  double er, ERa, ERb, ERl, ERr;
  int cl, cr, ca, cb;
  unsigned char c; 

  /* Its easier to set the endge values first, as it
  reduces the amount of checking needed in the main body.
  There are only 11 cases here - 3 types of metal, 
  the four corners, and the four sides */

  for(i=0;i<width; ++i) {
    for(j=0;j<height;++j) {  

      oddity[i][j]=UNDEFINED_ODDITY;  /* Stick it to some underfined status  */

      c=cell_type[i][j];   /* Cell type at point (i,j) */


      /* The 3 metal cases can be quickly checked and the 
      oddity value assigned to a fixed value depending on
      whether it's -1, 0 or +1 V */

      if(c <= CONDUCTOR_PLUS_ONE_V ) /* a metal */
	oddity[i][j]=c;    


      /* Now do the 4 courners */
      else if( (i == 0) && (j ==  height-1)  ) 
	oddity[i][j]=BOTTOM_LEFT_CORNER;

      else if ( (i == width-1) && (j == height-1)  )  
	oddity[i][j]=BOTTOM_RIGHT_CORNER;

      else if( (i == 0) && (j == 0) ) 
	oddity[i][j]=TOP_LEFT_CORNER;

      else if( (i == width-1) && (j == 0)  )
	oddity[i][j]=TOP_RIGHT_CORNER;

      /* Now the four edges */ 
      else if ( i == 0 )
	oddity[i][j]=ORDINARY_POINT_LEFT_EDGE;

      else if ( j == 0 ) 
	oddity[i][j]=ORDINARY_POINT_TOP_EDGE;

      else if ( j == height-1) 
	oddity[i][j]=ORDINARY_POINT_BOTTOM_EDGE;

      else if ( i == width-1 ) 
	oddity[i][j]=ORDINARY_POINT_RIGHT_EDGE;


      else if ( (i == 0 || i == width-1 || j == 0 || j == height-1 ) && (oddity[i][j]==UNDEFINED_ODDITY)) {
	fprintf(stderr,"Internal error: one of the edge points (%d,%d) is still undefined\n",i,j);
	fprintf(stderr, "ZZZZZZZZZZZZZ width=%d height=%d\n", width, height);
	fprintf(stderr,"Error set_oddity_value.c\n");
	exit(INTERNAL_ERROR);
      }
    } /* end of for(j=0;j<height-0;++j) { */
  } /* end of for(i=0;i<width-0; ++i) { */
  /* With the oddity values of all the edges now know, the centre
  values can be attempted */

  for(i=1;i<width-1; ++i) {
    for(j=1;j<height-1;++j) {  

      c=cell_type[i][j];   /* Cell type at point (i,j) */
      cl=cell_type[i-1][j];  /* Cell type to left of point (i,j) */
      cr=cell_type[i+1][j];  /* Cell type to right of point (i,j) */
      ca=cell_type[i][j-1];  /* Cell type above point (i,j) */
      cb=cell_type[i][j+1];  /* Cell type below point (i,j) */

      ERa=Er[i][j-1];
      ERb=Er[i][j+1];
      ERl=Er[i-1][j];
      ERr=Er[i+1][j];
      er=Er[i][j];


      /* If the conductor is at a fixed voltage, it must stay there
      so there is nothing to do with it */

      if(c == CONDUCTOR_ZERO_V )
        oddity[i][j] = CONDUCTOR_ZERO_V;

      else if(c== CONDUCTOR_PLUS_ONE_V)
        oddity[i][j] = CONDUCTOR_PLUS_ONE_V;

      else if(c == CONDUCTOR_MINUS_ONE_V )
        oddity[i][j] = CONDUCTOR_MINUS_ONE_V; 

      else if ( cr <= CONDUCTOR_PLUS_ONE_V && cb<= CONDUCTOR_PLUS_ONE_V)
        oddity[i][j]= METAL_BELOW_AND_RIGHT;

      else if ( cr <= CONDUCTOR_PLUS_ONE_V && ca<= CONDUCTOR_PLUS_ONE_V)
        oddity[i][j]= METAL_ABOVE_AND_RIGHT;

      else if ( cl <= CONDUCTOR_PLUS_ONE_V && cb<= CONDUCTOR_PLUS_ONE_V)
        oddity[i][j]= METAL_BELOW_AND_LEFT;

      else if ( cl <= CONDUCTOR_PLUS_ONE_V && ca<= CONDUCTOR_PLUS_ONE_V)
        oddity[i][j]= METAL_ABOVE_AND_LEFT;

      else if ( ca <= CONDUCTOR_PLUS_ONE_V )
	oddity[i][j]= METAL_ABOVE;

      else if ( cb <= CONDUCTOR_PLUS_ONE_V )
	oddity[i][j]= METAL_BELOW;

      else if ( cl <= CONDUCTOR_PLUS_ONE_V )
	oddity[i][j]= METAL_LEFT;

      else if ( cr <= CONDUCTOR_PLUS_ONE_V )
	oddity[i][j]= METAL_RIGHT;

      else if ( ERb != ERa)
	oddity[i][j]= DIFFERENT_DIELECTRIC_VERTICALLY; 
 
      else if ( ERl != ERr )
	oddity[i][j]= DIFFERENT_DIELECTRIC_HORIZONTALLY;      
/*
      else if ( ERa != er  && ERr != er)
	oddity[i][j]= DIFFERENT_DIELECTRIC_ABOVE_AND_RIGHT; 

      else if ( ERa != er  && ERl != er)
	oddity[i][j]= DIFFERENT_DIELECTRIC_ABOVE_AND_LEFT; 

      else if ( ERb != er  && ERl != er)
	oddity[i][j]= DIFFERENT_DIELECTRIC_BELOW_AND_LEFT; 

      else if ( ERa != er )
	oddity[i][j]= DIFFERENT_DIELECTRIC_ABOVE; 

      else if ( ERb != er )
	oddity[i][j]= DIFFERENT_DIELECTRIC_BELOW; 
      else if ( ERl != er )
	oddity[i][j]= DIFFERENT_DIELECTRIC_LEFT; 

      else if ( ERr != er )
	oddity[i][j]= DIFFERENT_DIELECTRIC_RIGHT; 
*/
      else
	oddity[i][j]= ORDINARY_INTERIOR_POINT;
    }/* end of for i=0 to width-1 */
  } /* end of for j= 0 to height-1 */
}

