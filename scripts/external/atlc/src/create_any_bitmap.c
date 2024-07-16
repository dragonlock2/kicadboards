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

/* The program widestrip is a pre-processor for atlc. It produces bitmaps 
of a thin strip, between two wide plates */
#include "config.h"

#ifdef HAVE_STDLIB_H
#include <stdlib.h>
#endif  

#ifdef HAVE_STRING_H
#include <string.h>
#endif  
#include "definitions.h"
#include "exit_codes.h"

#ifdef WINDOWS
#pragma hrdstop
#include <condefs.h>
#endif

int verbose=0;

extern int main(int argc, char **argv) /* Read parameters from command line here   */
{
  fprintf(stderr,"Sorry, create_any_bitmap is under construction and not finished\n");
  exit(1);
  if(argc !=2){
    usage_create_any_bitmap();    
    exit_with_msg_and_exit_code("",PROGRAM_CALLED_WITH_WRONG_NUMBER_OF_ARGUMENTS);
  }
  return(OKAY);
}
