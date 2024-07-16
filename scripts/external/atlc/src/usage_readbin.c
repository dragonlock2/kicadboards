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

#include "definitions.h"
#include "exit_codes.h"

void usage_readbin(void)
{
  fprintf(stderr,"Usage: readbin [-r] binaryfile.V.bin\n\n");
  fprintf(stderr,"Version %s\n",PACKAGE_VERSION);
  fprintf(stderr,"options are:\n");
  fprintf(stderr,"  -C        Print copyright, licencing and distribution information\n");
  fprintf(stderr,"  -r        Used when analysing binary files created on\
  the other byte-ordering\n            (ie a big-endian example.V.bin file\
  on a small endian machine - or\n            the reverse)\n");
  exit_with_msg_and_exit_code("",PROGRAM_CALLED_WITH_WRONG_NUMBER_OF_ARGUMENTS);
}
