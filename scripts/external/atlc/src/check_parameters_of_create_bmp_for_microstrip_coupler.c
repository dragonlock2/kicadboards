

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

#ifdef ENABLE_POSIX_THREADS
#include <pthread.h>
#endif

#include "exit_codes.h"

void check_parameters_of_create_bmp_for_microstrip_coupler(struct transmission_line_properties pcb) 
{
      if ( pcb.ww <= 0)
	exit_with_msg_and_exit_code("w <= 0",ARGUMENT_w_OUT_OF_RANGE);
      if ( pcb.ss <= 0)
	exit_with_msg_and_exit_code("s <= 0",ARGUMENT_s_OUT_OF_RANGE);
      if ( pcb.gg <= 0)
	exit_with_msg_and_exit_code("g <= 0",ARGUMENT_g_OUT_OF_RANGE);
      if ( pcb.hh <= 0)
	exit_with_msg_and_exit_code("h <= 0",ARGUMENT_h_OUT_OF_RANGE);
      if ( pcb.tt <= 0)
	exit_with_msg_and_exit_code("0 <= 0",ARGUMENT_t_OUT_OF_RANGE);
      if ( pcb.Er1 < 1)
	exit_with_msg_and_exit_code("0 <= 0",ARGUMENT_Er1_OUT_OF_RANGE);
      if ( pcb.Er2 < 1)
	exit_with_msg_and_exit_code("0 <= 0",ARGUMENT_Er2_OUT_OF_RANGE);
}
