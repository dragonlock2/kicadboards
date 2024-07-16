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

void usage_create_bmp_for_rect_in_circ(void)
{
      fprintf(stderr,"Usage: rect_in_circ [-b bmp_size] [-f outfile] [-v] D w h x y Er\n\n");
      fprintf(stderr,"Version %s\n",PACKAGE_VERSION);
      fprintf(stderr,"Where \n");
      fprintf(stderr,"  D  is the internal diameter of the outer conductor \n");
      fprintf(stderr,"  w  is the width of the inner conductor\n");
      fprintf(stderr,"  h  is the height of the inner conductor\n");
      fprintf(stderr,"  x  is the horizontal offset between centres of the conductors\n");
      fprintf(stderr,"  y  is the vertical offset between centres of the conductors\n");
      fprintf(stderr,"  Er is the relative permettivity of the dielectric.\n");
      fprintf(stderr,"  D, w, h, x, and y are either all in mm or all in inches (but not a mixture!!)\n\n");   
      fprintf(stderr,"options are:\n");
      fprintf(stderr,"  -b bmp_size\n     Sets the size of the bitmap, in the range 1 to 15 (default %d).\n",DEFAULT_BMP_SIZE);
      fprintf(stderr,"  -f outfile \n     Write output to 'outfile' instead of stdout\n");
      fprintf(stderr,"  -v         \n     Write diagnostic information to stderr\n\n");
      fprintf(stderr,"                                     ***\n");
      fprintf(stderr,"                              *****************\n"); 
      fprintf(stderr,"                          ****                 ****\n");                        
      fprintf(stderr,"                       ****                       ****\n");                     
      fprintf(stderr,"                     ***                             ***\n");                   
      fprintf(stderr,"                   ***    *************  ^             ***\n");                 
      fprintf(stderr,"                 ***      *************  |               ***\n");               
      fprintf(stderr,"                ***       *************  |                ***\n");              
      fprintf(stderr,"               ***      ^ *************  h                 ***\n");             
      fprintf(stderr,"              ***       | *************  |                  ***\n");            
      fprintf(stderr,"             ***        | *************  |                   ***\n");           
      fprintf(stderr,"             **         y *************  v                   **\n");           
      fprintf(stderr,"            ***         | <-----w----->                        ***\n");          
      fprintf(stderr,"            **          |                                      **\n");          
      fprintf(stderr,"            *<----------v-------------D------------------------>*\n");          
      fprintf(stderr,"            **                                                 **\n");          
      fprintf(stderr,"            **                                                 **\n");          
      fprintf(stderr,"            **                   <--x->                        **\n");          
      fprintf(stderr,"            ***                                               ***\n");          
      fprintf(stderr,"             **                                               **\n");           
      fprintf(stderr,"             ***                                             ***\n");           
      fprintf(stderr,"              **                                             **\n");            
      fprintf(stderr,"               **                                           **\n");             
      fprintf(stderr,"                **                                         **\n");              
      fprintf(stderr,"                 ***                                     ***\n");               
      fprintf(stderr,"                  ****                                 ****\n");                
      fprintf(stderr,"                    ****                             ****\n");                  
      fprintf(stderr,"                      *****                       *****\n");                    
      fprintf(stderr,"                         ******               ******\n");                       
      fprintf(stderr,"                             *******************\n");                           
      fprintf(stderr,"                                     ***\n\n");
      fprintf(stderr,"***WARNING*** Since the output from rect_in_circ is binary data (the bitmap) it\n");
      fprintf(stderr,"will screw up your terminal unless you redirect the ouptut to a file.\n");
      fprintf(stderr,"The '-f' option can be used to send the output to 'outfile' \n");
      fprintf(stderr,"or you can use rect_in_circ D d h Er > filename.bmp \n");
      exit_with_msg_and_exit_code("",PROGRAM_CALLED_WITH_WRONG_NUMBER_OF_ARGUMENTS); 
}
