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

extern int width, height;
extern unsigned char **oddity;
extern double **Er, **Vij;

void find_maximum_values(struct max_values *maximum_values, int zero_elementsQ)
{
  double U, V, Ex, Ey, E, permittivity;
  int i, j;

  /* It makes sense to draw the even and odd mode images on the same
  scale, so if its a coupler, they elements are not zeroed if the
  function is called when doing the even mode, which is done
  after the odd mode */

  if(zero_elementsQ==ZERO_ELEMENTS_FIRST)
  {
    maximum_values->E_max=0.0;
    maximum_values->Ex_or_Ey_max=0.0;
    maximum_values->V_max=0.0;
    maximum_values->U_max=0.0;
    maximum_values->permittivity_max=0.0;
  }
  for(i=0;i<width;++i)
  {
    for(j=0;j<height;++j)
    {
      V=Vij[i][j];
      U=find_energy_per_metre(i,j);
      if(1)
      {
	if(i==0)       
	  Ex=2*Er[i+1][j]*(Vij[i][j]-Vij[i+1][j])/(Er[i+1][j]+Er[i][j]);
        else if (i==width-1) 
    	  Ex=2*Er[i-1][j]*(Vij[i-1][j]-Vij[i][j])/(Er[i-1][j]+Er[i][j]);
        else /* This is the best estimate, but can't be done on boundary */
	{
    	  Ex=Er[i-1][j]*(Vij[i-1][j]-Vij[i][j])/(Er[i-1][j]+Er[i][j]);
	  Ex+=Er[i+1][j]*(Vij[i][j]-Vij[i+1][j])/(Er[i+1][j]+Er[i][j]);
        }
	if(j==0)
	  Ey=2*Er[i][j+1]*(Vij[i][j]-Vij[i][j+1])/(Er[i][j+1]+Er[i][j]);
	else if (j==height-1)
	  Ey=2*Er[i][j-1]*(Vij[i][j-1]-Vij[i][j])/(Er[i][j-1]+Er[i][j]);
	else
	{
	  Ey=Er[i][j-1]*(Vij[i][j-1]-Vij[i][j])/(Er[i][j-1]+Er[i][j]);
	  Ey+=Er[i][j+1]*(Vij[i][j]-Vij[i][j+1])/(Er[i][j+1]+Er[i][j]);
        }
        E=sqrt(Ex*Ex+Ey*Ey);
        permittivity=Er[i][j];
      }
      else
      {
        Ex=0.0;
	Ey=0.0;
	E=0.0;
	permittivity=0.0;
      }
      if(U> 1.0)             
        printf("U=%f v=%f Er=%f at %d %d\n",U,V,Er[i][j],i, j);

      if(E>maximum_values->E_max) 
        maximum_values->E_max=E;


      if(fabs(Ex)>maximum_values->Ex_or_Ey_max)
        maximum_values->Ex_or_Ey_max=fabs(Ex);

      if(fabs(Ey)>maximum_values->Ex_or_Ey_max)
        maximum_values->Ex_or_Ey_max=fabs(Ey);

      if(fabs(E)>maximum_values->E_max)
        maximum_values->E_max=fabs(E);

      if(fabs(V) > maximum_values->V_max)
        maximum_values->V_max=fabs(V); 

      if(U > maximum_values->U_max)
        maximum_values->U_max=U; 

      if(permittivity >maximum_values->permittivity_max )
        maximum_values->permittivity_max=permittivity; 
        /* printf("Ex_or_Ey_max=%g E_max=%g V_max=%g U_max=%g Er_max=%g\n",maximum_values->Ex_or_Ey_max, maximum_values->E_max, maximum_values->V_max, maximum_values->U_max, maximum_values->permittivity_max);  */
    }
  }
}
