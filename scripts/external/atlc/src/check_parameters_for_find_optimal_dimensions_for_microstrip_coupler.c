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


#include "definitions.h"
#include "exit_codes.h"

void check_parameters_for_find_optimal_dimensions_for_microstrip_coupler\
(double h,double t,double Er1,double Er2,double ideal_Zodd,double ideal_Zeven) 
{
  if(h <= 0)
    exit_with_msg_and_exit_code("h <= 0",ARGUMENT_h_OUT_OF_RANGE);
  if (t <= 0) 
    exit_with_msg_and_exit_code("t <= 0",ARGUMENT_t_OUT_OF_RANGE);
  if ( Er1 < 1.00) 
    exit_with_msg_and_exit_code("Er1 < 1",ARGUMENT_Er1_OUT_OF_RANGE);
  if ( Er2 < 1.00) 
    exit_with_msg_and_exit_code("Er2 < 1",ARGUMENT_Er2_OUT_OF_RANGE);
  if ( ideal_Zodd < 0) 
    exit_with_msg_and_exit_code("Ideal_zodd",ARGUMENT_ideal_Zodd_OUT_OF_RANGE);
  if ( ideal_Zeven < 0) 
    exit_with_msg_and_exit_code("Ideal_zodd",ARGUMENT_ideal_Zodd_OUT_OF_RANGE);
  if ( ideal_Zeven <= ideal_Zodd ) 
    exit_with_msg_and_exit_code("Zodd must be less than Zeven",IDEAL_Zodd_NOT_LESS_THAN_IDEAL_Zeven);
}
