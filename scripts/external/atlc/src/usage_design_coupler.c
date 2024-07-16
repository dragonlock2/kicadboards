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

void usage_design_coupler()
{
  fprintf(stderr,"\nUsage: design_coupler [-d] [-e] [-q] [-s fstep] [-C] [-D] [-H height] [-L length] [-Z Zo] CF fmin fmax\n");
  fprintf(stderr,"Version %s\n",PACKAGE_VERSION);
  fprintf(stderr,"where: \n");
  fprintf(stderr,"     CF          is the coupling factor required in dB [10 log(P1/P2)]\n");
  fprintf(stderr,"     fmin        is the minimum frequency (MHz)\n");
  fprintf(stderr,"     fman        is the maximum frequency (MHz)\n");
  fprintf(stderr,"Options are:\n");
  fprintf(stderr,"      -d           Calculate physical dimensions (takes a while).\n");
  fprintf(stderr,"      -e           Give lots of examples of usage.\n");
  fprintf(stderr,"      -q           Run in quite mode, giving less output.\n");
  fprintf(stderr,"      -s fstep     Set the analysis frequency step in MHz.\n");
  fprintf(stderr,"      -C           Print Copyright, Licencing and Distribution information.\n");
  fprintf(stderr,"      -D           Calculate physical dimensions to high accuracy (takes a *very* long while).\n");
  fprintf(stderr,"      -H height    to set the height of the enclosure (defaults to 1 unit).\n");
  fprintf(stderr,"      -L length    to set the coupler length (m). Defaults to lambda/4.\n");
  fprintf(stderr,"      -Q           Run in very quite mode, giving just one line of output\n");
  fprintf(stderr,"      -Z Zo        Set the design impedance (default is 50 Ohms)\n");
  fprintf(stderr,"coupled port 2 ************************************************ reflected port 3\n\n");
  fprintf(stderr,"input port 1   ************************************************ output port 4\n");
  fprintf(stderr,"               <--------------------L------------------------->\n");
  fprintf(stderr,"Drive Port 1. The main power comes out from port 4. A fraction (set by the \n");
  printf("coupling factor) of the forward power comes from port 2. A fraction of the\n");
  printf("reflected power comes from port 3. All ports must present an impedance Zo.\n");
}
