#include "definitions.h"
#include "exit_codes.h"

extern double **Vij;
extern unsigned char **oddity;
extern double **Er;
extern int width, height;

double find_Ex(int i, int j) 
{
  double Ex=0.0;
  unsigned char odd;
  odd = oddity[i][j];
  if(odd > CONDUCTOR_FLOATING) {

    if (odd == TOP_LEFT_CORNER || odd == BOTTOM_LEFT_CORNER) 
      Ex=Vij[0][j]-Vij[1][j];

    else if (odd == TOP_RIGHT_CORNER || odd == BOTTOM_RIGHT_CORNER) 
      Ex=Vij[width-2][0]-Vij[width-1][0];

    else if (odd == ORDINARY_POINT_TOP_EDGE || odd == ORDINARY_POINT_BOTTOM_EDGE) 
      Ex=0.5*(Vij[i-1][j]-Vij[i+1][j]);

    else if (odd == ORDINARY_POINT_LEFT_EDGE) 
      Ex=(Vij[i][j]-Vij[i+1][j]);

    else if (odd == ORDINARY_POINT_RIGHT_EDGE) 
      Ex=(Vij[width-2][j]-Vij[width-1][j]);

    else if(odd == METAL_LEFT || odd == METAL_BELOW_AND_LEFT || odd == METAL_ABOVE_AND_LEFT)
      Ex=Vij[i][j]-Vij[i+1][j];

    else if(odd == METAL_RIGHT || odd == METAL_ABOVE_AND_RIGHT || odd ==METAL_BELOW_AND_RIGHT)
      Ex=Vij[i-1][j]-Vij[i][j];

    else if (odd == ORDINARY_INTERIOR_POINT || odd == METAL_ABOVE || odd == METAL_BELOW)
      Ex=0.5*(Vij[i-1][j]-Vij[i+1][j]);

    else if (odd >= DIFFERENT_DIELECTRIC_ABOVE_AND_RIGHT && odd < UNDEFINED_ODDITY  )
      Ex=0.5*(Vij[i-1][j]-Vij[i+1][j]);

    else{
      fprintf(stderr,"oddity[%d][%d]=%d\n",i,j,odd);
      exit_with_msg_and_exit_code("Internal error in find_Ex",INTERNAL_ERROR);
    }
  }
  return(Ex);
}

double find_Ey(int i, int j)
{
  double Ey=0.0;
  unsigned char odd;
  odd = oddity[i][j];

  if(odd > CONDUCTOR_FLOATING) {

    if (odd == TOP_LEFT_CORNER || odd == TOP_RIGHT_CORNER) 
      Ey=Vij[i][1]-Vij[i][0];

    else if (odd == BOTTOM_LEFT_CORNER || odd == BOTTOM_RIGHT_CORNER) 
      Ey=Vij[i][height-1]-Vij[i][height-2];

    else if (odd == ORDINARY_POINT_LEFT_EDGE || odd == ORDINARY_POINT_RIGHT_EDGE) 
      Ey=0.5*(Vij[i][j+1]-Vij[i][j-1]);

    else if (odd == ORDINARY_POINT_BOTTOM_EDGE) 
      Ey=Vij[i][j+1]-Vij[i][j];

    else if (odd == ORDINARY_POINT_TOP_EDGE) 
      Ey=Vij[i][j]-Vij[i][j-1];

    else if (odd == METAL_ABOVE || odd == METAL_ABOVE_AND_LEFT || odd == METAL_ABOVE_AND_RIGHT)
      Ey=Vij[i][j+1]-Vij[i][j];

    else if (odd == METAL_BELOW || odd == METAL_BELOW_AND_LEFT || odd == METAL_BELOW_AND_RIGHT)
      Ey=Vij[i][j]-Vij[i][j-1];

    else if(odd >= DIFFERENT_DIELECTRIC_LOCALLY || odd == ORDINARY_INTERIOR_POINT || odd == METAL_RIGHT || odd == METAL_LEFT)
      Ey=0.5*(Vij[i][j+1]-Vij[i][j-1]);

    else{
      fprintf(stderr,"oddity[%d][%d]=%d\n",i,j,odd);
      exit_with_msg_and_exit_code("Internal error in find_Ey",INTERNAL_ERROR);
    }
  }
  return(Ey);
}

double find_E(int w, int h)
{
  double Ex, Ey, E;
  Ex=find_Ex(w,h);
  Ey=find_Ey(w,h);
  E=sqrt(Ex*Ex+Ey*Ey);
  return(E);
}

