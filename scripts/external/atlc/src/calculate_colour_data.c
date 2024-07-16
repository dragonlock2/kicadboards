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

#ifdef HAVE_STDLIB_h
#include <stdlib.h>
#endif

#ifdef HAVE_MATH_H
#include <math.h>
#endif

#include "definitions.h"

extern double **Vij;
extern double **Er;
extern unsigned char **oddity;

void calculate_colour_data(double x, double xmax, int w, int h, int offset, unsigned char *image_dat, int image_type,
unsigned char *red, unsigned char *green, unsigned char *blue, double image_fiddle_factor)
{
  if(image_type==COLOUR) /*Ex, Ey, V */
  {
    if(fabs(x) < 1e-9) /* This is a bit of a fiddle I admit, but */
    {                  /* Is needed to prevent problems at 'small' values */
      *red=0;
      *green=0;
      *blue=0;
    }
    else if(x > 0.0)
    {
      *red=255*pow(x/xmax,1.0/image_fiddle_factor);
      *green=0; 
      *blue=0; 
    }
    else 
    {
      *red=0; 
      *green=0; 
      *blue=255*pow(-x/xmax,1.0/image_fiddle_factor); 
    }
  }
  else if (image_type==MONOCHROME) /* E, energy, permittivity */
  {
    if(x > xmax)
    {
      *red=0; *green=0; *blue=0;
    }
    else
    {
      *red=255*pow(fabs(x/xmax),1.0/image_fiddle_factor);
      *green=255*pow(fabs(x/xmax),1.0/image_fiddle_factor);
      *blue=255*pow(fabs(x/xmax),1.0/image_fiddle_factor);
     }
  }
  else if (image_type==MIXED) /* Only for permittivity*/
  {
    if(oddity[w][h]==CONDUCTOR_ZERO_V)
    {
      *red=0; *green=255; *blue=0;
    }
    else if(oddity[w][h]==CONDUCTOR_PLUS_ONE_V)
    {
      *red=255; *green=0; *blue=0;
    }
    else if(oddity[w][h]==CONDUCTOR_MINUS_ONE_V)
    {
      *red=0; *green=0; *blue=255;
    }
    else
    {
      *red=255*pow(fabs(x/xmax),1.0/image_fiddle_factor);
      *green=255*pow(fabs(x/xmax),1.0/image_fiddle_factor);
      *blue=255*pow(fabs(x/xmax),1.0/image_fiddle_factor);
     }
  }
  image_dat[offset]=*blue; 
  image_dat[offset+1]=*green; 
  image_dat[offset+2]=*red; 
}
