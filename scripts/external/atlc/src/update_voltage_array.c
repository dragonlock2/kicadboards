/*
The code below for calculating the voltage at a point i,j, given the
voltages and permittivities at the four adjacent points (i,j+1),
(i,j-1), (i-1,j), and (i+1,j), although I am not convinced it is 
100% correct in the case of mulitple dielectrics, the errors are 
still very small. 
*/


#include "config.h"

#ifdef HAVE_STDLIB_H
#include <stdlib.h>
#endif 

#ifdef HAVE_STDIO_H
#include <stdio.h>
#endif 

#include "definitions.h"


extern int width, height;
extern double **Er;
extern unsigned char  **oddity;
extern int dielectrics_to_consider_just_now;
extern double r; 
extern int coupler;

#include "exit_codes.h"

/* The following function updates the voltage on the matrix V_to given data about the 
oddity of the location i,j and the voltages in the matrix V_from. It does this for n interations
between rows jmin and jmax inclusive and between columns imain and imax inclusive */

void update_voltage_array(int nmax, int imin, int imax, int jmin, int jmax, double **V_from, double **V_to)
{
  int k, i, j, n;  
  unsigned char oddity_value;
  double Va, Vb, Vl, Vr, ERa, ERb, ERl, ERr;
  double Vnew, g;

  if (dielectrics_to_consider_just_now==1)
    g=r;
  else 
    g=1; 
  for(n=0; n  < nmax; ++n)
    for(k=0; k < 4; ++k)
      for (i = k&1 ? imax : imin;   k&1 ? i >=imin : i <= imax ;  k&1 ? i-- : i++)
        for (j = (k==0 || k ==3) ? jmin : jmax; (k ==0 || k == 3)  ? j <= jmax : j >= jmin ; (k == 0 || k ==3) ?  j++ : j--){
          oddity_value=oddity[i][j];

          if( oddity_value == CONDUCTOR_ZERO_V ){  
            V_to[i][j]=0.0;
          }

          else if( oddity_value == CONDUCTOR_PLUS_ONE_V ){  
            V_to[i][j]=1.0;
          }

          else if( oddity_value == CONDUCTOR_MINUS_ONE_V ){  
            V_to[i][j]=-1.0;
          }

          else if( oddity_value == TOP_LEFT_CORNER ) {  /* top left */
            Vnew=0.5*(V_from[1][0]+V_from[0][1]);               
            V_to[i][j]=g*Vnew+(1-g)*V_from[i][j];
          }
          else if( oddity_value == TOP_RIGHT_CORNER ) {
            Vnew=0.5*(V_from[width-2][0]+V_from[width-1][1]);         /* top right */
            V_to[i][j]=g*Vnew+(1-g)*V_from[i][j];
          }

          else if(oddity_value == BOTTOM_LEFT_CORNER) {
            Vnew=0.5*(V_from[0][height-2]+V_from[1][height-1]);       /* bottom left */
            V_to[i][j]=g*Vnew+(1-g)*V_from[i][j];
          }

          else if( oddity_value == BOTTOM_RIGHT_CORNER) {   
            Vnew=0.5*(V_from[width-2][height-1]+V_from[width-1][height-2]); /* bottom right */
            V_to[i][j]=g*Vnew+(1-g)*V_from[i][j];
          }

          /* Now the sides */

          else if( oddity_value == ORDINARY_POINT_LEFT_EDGE ){  /* left hand side  */
            Vnew=0.25*(V_from[0][j-1]+V_from[0][j+1] + 2*V_from[1][j]);
            V_to[i][j]=g*Vnew+(1-g)*V_from[i][j];
          }

          else if( oddity_value == ORDINARY_POINT_RIGHT_EDGE){   /* right hand side */
            Vnew=0.25*(V_from[width-1][j+1]+V_from[width-1][j-1]+2*V_from[width-2][j]);
            V_to[i][j]=g*Vnew+(1-g)*V_from[i][j];
          }
        
          else if( oddity_value == ORDINARY_POINT_TOP_EDGE ){ /* top row */ 
            Vnew=0.25*(V_from[i-1][0]+V_from[i+1][0]+2*V_from[i][1]);
            V_to[i][j]=g*Vnew+(1-g)*V_from[i][j];
          }

          else if( oddity_value == ORDINARY_POINT_BOTTOM_EDGE ){   /* bottom row */ 
            Vnew=0.25*(V_from[i-1][height-1]+V_from[i+1][height-1]+2*V_from[i][height-2]);
            V_to[i][j]=g*Vnew+(1-g)*V_from[i][j];
          }

          else if ( oddity_value == ORDINARY_INTERIOR_POINT || (oddity_value>=DIFFERENT_DIELECTRIC_ABOVE_AND_RIGHT && oddity_value < UNDEFINED_ODDITY && dielectrics_to_consider_just_now == 1) ) {
            Va=V_from[i][j-1]; 
            Vb=V_from[i][j+1];
            Vl=V_from[i-1][j];
            Vr=V_from[i+1][j];

            Vnew=(Va+Vb+Vl+Vr)/4.0;
            V_to[i][j]=g*Vnew+(1-g)*V_from[i][j];
	  }

	  /* I'm not sure the following equations, which compute the voltage  
	  where there is a metal around are okay. One line of thought would 
	  say that the same equations as normal  i.e.
          v_new=(v(i+1,j_+v(i-1,j)+v(i,j-1)+v(i,j+1))/4 should be used
	  but then since the electric field across the metal surface is zero,
	  the equation that was used to derrive  that equation is not valid.

	  Another thought of mine is that voltage near a metal will be more affected
	  by the metal than the dielectric, since the nearest part of the metal is at
	  at the same voltage as the node, whereas for a dielectric is less so. Hence
	  the following seems a sensible solution. Since the metal will have twice 
	  the effect of a dielectric, the voltage at i,j should be weighted such
	  that its effect is more strongly affected by the metal. This seems to 
	  produce reasonably accurate results, but whether this is chance or not
	  I don't know. */

          else if( oddity_value == METAL_ABOVE ){  
            Va=V_from[i][j-1]; 
            Vb=V_from[i][j+1];
            Vl=V_from[i-1][j];
            Vr=V_from[i+1][j];

            Vnew=0.25*(4*Va/3+2*Vb/3+Vl+Vr);
            V_to[i][j]=g*Vnew+(1-g)*V_from[i][j];
          }

          else if( oddity_value == METAL_BELOW ){   
            Va=V_from[i][j-1]; 
            Vb=V_from[i][j+1];
            Vl=V_from[i-1][j];
            Vr=V_from[i+1][j];

            Vnew=0.25*(4*Vb/3+2*Va/3+Vl+Vr);
            V_to[i][j]=g*Vnew+(1-g)*V_from[i][j];
          }

          else if( oddity_value == METAL_LEFT ){   
            Va=V_from[i][j-1]; 
            Vb=V_from[i][j+1];
            Vl=V_from[i-1][j];
            Vr=V_from[i+1][j];

            Vnew=0.25*(4*Vl/3+2*Vr/3+Va+Vb);
            V_to[i][j]=g*Vnew+(1-g)*V_from[i][j];
          }

          else if( oddity_value == METAL_RIGHT ){   
            Va=V_from[i][j-1]; 
            Vb=V_from[i][j+1];
            Vl=V_from[i-1][j];
            Vr=V_from[i+1][j];

            Vnew=0.25*(4*Vr/3+2*Vl/3+Va+Vb);
            V_to[i][j]=g*Vnew+(1-g)*V_from[i][j];
          }

          else if( oddity_value == METAL_ABOVE_AND_RIGHT ){   
            Va=V_from[i][j-1]; 
            Vb=V_from[i][j+1];
            Vl=V_from[i-1][j];
            Vr=V_from[i+1][j];

            Vnew=0.25*(4*Vr/3+4*Va/3 +2*Vl/3 + 2*Vb/3);
            V_to[i][j]=g*Vnew+(1-g)*V_from[i][j];
          }

          else if( oddity_value == METAL_ABOVE_AND_LEFT ){   
            Va=V_from[i][j-1]; 
            Vb=V_from[i][j+1];
            Vl=V_from[i-1][j];
            Vr=V_from[i+1][j];

            Vnew=0.25*(4*Vl/3+4*Va/3+2*Vr/3+2*Vb/3);
            V_to[i][j]=g*Vnew+(1-g)*V_from[i][j];
          }

          else if( oddity_value == METAL_BELOW_AND_LEFT ){   
            Va=V_from[i][j-1]; 
            Vb=V_from[i][j+1];
            Vl=V_from[i-1][j];
            Vr=V_from[i+1][j];

            Vnew=0.25*(4*Vl/3+4*Vb/3+2*Vr/3+2*Va/3);
            V_to[i][j]=g*Vnew+(1-g)*V_from[i][j];
          }

          else if( oddity_value == METAL_BELOW_AND_RIGHT ){   
            Va=V_from[i][j-1]; 
            Vb=V_from[i][j+1];
            Vl=V_from[i-1][j];
            Vr=V_from[i+1][j];

            Vnew=0.25*(4*Vb/3+4*Vr/3+2*Va/3+2*Vl/3);
            V_to[i][j]=g*Vnew+(1-g)*V_from[i][j];
          }

	  /* Again, when there is a change of permittivity, my equations may
	  (probably are wrong). My logic is that if there's and RF field,
	  the impedance is inversly proportional to Er. So if the material
	  above a node is of a higher permittivity, then the 
	  voltage will be closer to that of the node above, becuase of this.
	  The same applies for other directions of change in Er. */


          else if(dielectrics_to_consider_just_now > 1){

            Va=V_from[i][j-1]; 
            Vb=V_from[i][j+1];
            Vl=V_from[i-1][j];
            Vr=V_from[i+1][j];

            ERa=Er[i][j-1]; 
            ERb=Er[i][j+1];
            ERl=Er[i-1][j];
            ERr=Er[i+1][j];

            Vnew=(Va * ERa + Vb * ERb + Vl * ERl + Vr * ERr)/(ERa + ERb + ERl + ERr);
            V_to[i][j]=g*Vnew+(1-g)*V_from[i][j];

	  }
	  else if ( (dielectrics_to_consider_just_now == 1 && oddity_value == UNDEFINED_ODDITY) || (dielectrics_to_consider_just_now > 1)) {
            fprintf(stderr,"Internal error in update_voltage_array.c\n");
            fprintf(stderr,"i=%d j=%d oddity[%d][%d]=%d\n",i,j,i,j,oddity[i][j]);
            exit(INTERNAL_ERROR);
          } /* end if if an internal error */

        } /* end of j loop */
} 
