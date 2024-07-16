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

/* Note, the number of dilectrics defined must be set by the parameter 
#define NUMBER_OF_ORDINARY_INTERIOR_POINTS_DEFINED ?? in definitions.h. There needs
ot be a better way of setting this, but for now it will do */

char *names[]={"Vacuum","Air","PTFE", "duroid_5880","Polyethelene", "Polystyrene", "PVC","Epoxy_resin", "FR4 PCB", "Fibreglass_PCB", "duroid_6006","duroid_6010","one_hundred"};
double Ers[]={1.0,1.0006, 2.1,2.2,2.33,2.5,3.3,3.335,3.7,4.8,6.15,10.2,100.0};
int colours[]={0xffffff,0xffcaca, 0x8235ef,0x8e8e8e,0xff00ff,0xffff00, 0xefcc1a,0xbc7f60,0xdff788,0x1aefb3,0x696969,0xdcdcdc, 0xd5a04d};

