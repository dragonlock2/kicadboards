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

void usage_create_bmp_for_microstrip_coupler(void)
{
      fprintf(stderr,"Usage: create_bmp_for_microstrip_coupler [-b bmp_size] [-v] w s g h t Er1 Er2 filename\n\n");
      fprintf(stderr,"Version %s\n",PACKAGE_VERSION);
      fprintf(stderr,"where h, t, g1 and g2 are all ,in mm, all in inches or all in ..\n");      
      fprintf(stderr,"(they *must* use the same units. Non-integers allowed for all parameters)\n");
      fprintf(stderr,"Options are:\n");
      fprintf(stderr,"  -C              Print copyright, licencing and distribution information.\n");
      fprintf(stderr,"  -b bmp_size     Sets the size of the bitmap, in the range 1 to 15 (default %d).\n",DEFAULT_BMP_SIZE);
      fprintf(stderr,"  -H height       Sets the height 'H' of the box. Normally 15x(h+t)\n");
      fprintf(stderr,"  -W width        Sets the height 'H' of the box. Normally 6h+2g+s+2w)\n");
      fprintf(stderr,"GGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGG  ^\n");
      fprintf(stderr,"G                                                                       G  |\n");
      fprintf(stderr,"G                                                                       G  |\n");
      fprintf(stderr,"G        Dielectric, permittivity=Er1 (usually 1.0)                     G  |\n");
      fprintf(stderr,"G                                                                       G  |\n");
      fprintf(stderr,"G    c's denonte the copuled transmission lines of width w.             G  |\n");
      fprintf(stderr,"G    t   is the thickness of the copper of the PCB (typically 0.035 mm) G  |\n");
      fprintf(stderr,"G    h   is the thickness of the dielectric ( ~1.593 mm for 1.6 mm PCB) G  |\n");
      fprintf(stderr,"G |  g   is the gap between the coupled lines and the groundplane.      G  |\n");
      fprintf(stderr,"G |  s   is the spacing between the two coupled lines.                  G  |\n");
      fprintf(stderr,"G |  This is NOT drawn to scale (W and H are shown far too small )      G  H\n");
      fprintf(stderr,"G |                                                                     G  |\n");
      fprintf(stderr,"G v                <--g--><--w--><----s----><--w--><--g-->              G  |\n");
      fprintf(stderr,"GGGGGGGGGGGGGGGGGGG       ccccccc           ccccccc       GGGGGGGGGGGGGGG  |\n");
      fprintf(stderr,"GGGGGGGGGGGGGGGGGGG.......ccccccc...........ccccccc.......GGGGGGGGGGGGGGG  |\n");
      fprintf(stderr,"G.^................................................^....................G  |\n");
      fprintf(stderr,"G.|................................................|....................G  |\n");
      fprintf(stderr,"G.|t........Dielectric, permittivity=Er2...........h....................G  |\n");
      fprintf(stderr,"G.|............(3.7 for FR4 PCB)...................|....................G  |\n");
      fprintf(stderr,"G..................................................V....................G  |\n");
      fprintf(stderr,"GGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGG  |\n");
      fprintf(stderr,"GGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGG. v\n");
      fprintf(stderr,"<-----------------------------------W----------------------------------->\n\n");
      fprintf(stderr,"E.g. \ncreate_bmp_for_microstrip_coupler 1.5 2.0 1 1.593 0.035 1 3.7 foo.bmp\n");
      fprintf(stderr,"In this example, the conductor thickness t was small, but the width w is\n");
      fprintf(stderr,"large, so a fine grid (large bitmap) was needed. Hence the bitmap size\n");
      fprintf(stderr,"was increassed with the -b optoin. Without it, an error would result\n");
      exit_with_msg_and_exit_code("",PROGRAM_CALLED_WITH_WRONG_NUMBER_OF_ARGUMENTS);
}
