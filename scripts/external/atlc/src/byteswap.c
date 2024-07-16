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

#include "definitions.h"

extern int errno;

/* This routine swaps data from the little-endian format to the big-endian 
format or visa-versa. */

void byteswap_doubles(double *a)
{
	unsigned char b[8],c[8];
	(void) memcpy(b,a,8); 
	c[0]=b[7]; /* swap data around */
	c[1]=b[6];
	c[2]=b[5];
	c[3]=b[4];
	c[4]=b[3];
	c[5]=b[2];
	c[6]=b[1];
	c[7]=b[0];
	(void) memcpy(a,c,8);
}
