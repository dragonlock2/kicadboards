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

void usage_atlc(void)
{
#ifdef ENABLE_POSIX_THREADS
  fprintf(stderr,"Usage: atlc [options ...] bitmap\n\n");
#endif
  fprintf(stderr,"atlc %s: options are:\n",PACKAGE_VERSION);
  fprintf(stderr,"  -C       \n      Print Licence and copying information\n");
  fprintf(stderr,"  -s       \n      Skip writing the Ex, Ey, E, V, U and Er files bitmap (.bmp) files\n");
  fprintf(stderr,"  -S       \n      Skip writing the Ex, Ey, E, V, U and Er files binary (.bin) files\n");
  fprintf(stderr,"  -v       \n      Be verbose (-vv -vvv or -vvvv gives progressively more information)\n");
  fprintf(stderr,"  -c cutoff\n      where 'cutoff' sets the cutoff criteria - see html docs or man page.\n");
  fprintf(stderr,"  -d rrggbb=Er\n      where the colour rrggbb (in hex) is a (d)ielectric of permittivity Er.\n");
  fprintf(stderr,"  -i factor\n      which lightens (factor>%.1f) or darkens (1.0 <factor<%.1f) output bitmaps.\n",
  IMAGE_FIDDLE_FACTOR,IMAGE_FIDDLE_FACTOR);
  fprintf(stderr,"  -p prefix\n      where 'prefix' is a name (normally a directory) added in front of output files\n");
  fprintf(stderr,"  -r rate_multiplier\n      where 'rate_multiplier' sets the rate multipler (1 <= r < 2)\n");  
#ifdef ENABLE_POSIX_THREADS
  fprintf(stderr,"  -t THREADs. \n      Where THREADs is the number of threads to use (normally best set to \n      the number of cpus). The default is %d. Set to 0 for single threaded algorithm.\n",MAX_THREADS);
#endif
#ifdef ENABLE_MPI
  fprintf(stderr,"  -w weights\n     where weights is a colon-separated list of weights to use when dividing up the work amongst the processors.\n"); 
#endif
/*
#ifndef ENABLE_POSIX_THREADS
  fprintf(stderr,"****************NOTE******************************\n");
  fprintf(stderr,"The -t option setting the number of threads to use is disabled since\n");
  fprintf(stderr,"since this was not configured with multi-processor support.\n");
  fprintf(stderr,"To add support for multiple threads (for an MP machine), \"make clean\" then \nre-run the configure script with the option --with-threads\n");
#endif
*/
#ifndef ENABLE_MPI
  fprintf(stderr," ");
/*
  fprintf(stderr,"****************NOTE******************************\n");
  fprintf(stderr,"The -w option setting the weights to use when dividing up the work for\n");
  fprintf(stderr,"multiple CPUs on distributed processors is disabled since this was not\n");
  fprintf(stderr,"for distributed processing. To add such support, \"make clean\" then re-run\n");
  fprintf(stderr,"the configure script with the option --with-mpi\n");
  */
#endif
#ifdef WINDOWS
  fprintf(stderr,"****************NOTE******************************\n");
  fprintf(stderr,"The -t and -w options are disabled disabled since\n");
  fprintf(stderr,"this is a Windoze executable.\n");
  fprintf(stderr,"There are no plans to add multi-processor or distributed\n");
  fprintf(stderr,"processing to Windoze.\n");

#endif
}
