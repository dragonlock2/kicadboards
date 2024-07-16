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
#include "exit_codes.h"

/* names, colours and Ers are all arrays of 10. It would be better they were 
in a structure as they are all linked closely, but they are not and I
can't be bothered to change it */



/* This function checks to see if the errors on the grid are too large.
A problem occurs if a number was zero, so this needs to be carefullly
controlled. */

void check_error(double user, int create_bmp_for_rect_in_rect, double gridsize, const char *name)
{
   double fractional_error;
   fractional_error=fabs((user-(create_bmp_for_rect_in_rect*gridsize))/user);
   if(user > 0)
   {
      if(fractional_error > UNACCEPTABLE_ERROR)
      {
         fprintf(stderr,"Error #14. Unacceptable %f%% error in representing %s on the grid\n", fractional_error*100.0, name);
	 fprintf(stderr,"Try increasing the bitmap size with the -b option\n");
	 exit_with_msg_and_exit_code("exiting ...",UNACCEPTABLE_ERROR_WHEN_CONVERTING_TO_INTEGERS);
      }
      else if(fractional_error > ACCEPTABLE_ERROR)
         fprintf(stderr,"*WARNING*  %f%% error in representing %s on the grid\n", fractional_error*100.0, name);
   }
}
