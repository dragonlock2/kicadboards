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

void usage_create_bmp_for_circ_in_circ(void)
{
      fprintf(stderr,"Usage: circ_in_circ [-b bmp_size] [-f outfile] [-v] D d O Er filename\n\n");
      fprintf(stderr,"Version %s\n", PACKAGE_VERSION);
      fprintf(stderr,"Where \n");
      fprintf(stderr,"  D  is the internal diameter of the outer conductor \n");
      fprintf(stderr,"  d  is the outside diameter of the inner conductor\n");
      fprintf(stderr,"  O  is the offset between centres (zero in the case of coax cable)\n");
      fprintf(stderr,"  Er is the relative permettivity of the dielectric.\n");
      fprintf(stderr,"  D, d and O are either all in mm or all in inches (but not a mixture!!)\n\n");   
      fprintf(stderr,"options are:\n");
      fprintf(stderr,"  -C         \n     Print copyright, licencing and distribution information\n");
      fprintf(stderr,"  -b bmp_size\n     Sets the size of the bitmap, in the range 1 to 15 (default %d).\n",DEFAULT_BMP_SIZE);
      fprintf(stderr,"  -v         \n     Write diagnostic information to stderr\n\n");

      fprintf(stderr,"                              *****************\n"); 
      fprintf(stderr,"                          ****                 ****\n");                        
      fprintf(stderr,"                       ****    <-----d------>     ****\n");                     
      fprintf(stderr,"                     ***            *****            ***\n");                   
      fprintf(stderr,"                   ***           ***********           ***\n");                 
      fprintf(stderr,"                 ***            *************            ***\n");               
      fprintf(stderr,"                ***            ***************            ***\n");              
      fprintf(stderr,"               ***      ^      ***************             ***\n");             
      fprintf(stderr,"              ***       |      ***************              ***\n");            
      fprintf(stderr,"             ***        |       *************                ***\n");           
      fprintf(stderr,"             **         O        ***********                  **\n");           
      fprintf(stderr,"            ***         |            ***                      ***\n");          
      fprintf(stderr,"            **          |                                      **\n");          
      fprintf(stderr,"            *<------------------------D------------------------>*\n");          
      fprintf(stderr,"            **                                                 **\n");          
      fprintf(stderr,"            **                                                 **\n");          
      fprintf(stderr,"            **                                                 **\n");          
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
      exit_with_msg_and_exit_code("",PROGRAM_CALLED_WITH_WRONG_NUMBER_OF_ARGUMENTS);
}
