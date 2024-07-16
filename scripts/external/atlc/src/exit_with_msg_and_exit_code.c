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

#ifdef ENABLE_MPI
#include <mpi.h>
#endif

#include "definitions.h"


void exit_with_msg_and_exit_code(const char *s, int exitnumber)
{
  if ((NULL != s) && (s[0] != '\0')) {
	fprintf(stderr,"%s\n",s);
  }

#ifdef ENABLE_MPI 
#ifdef NEED_MPI_CODE
  MPI_Finalize();
#endif
#endif

  exit(exitnumber);
}
