#ifndef ENABLE_MP

#include "config.h"

#ifdef HAVE_STDLIB_H
#include <stdlib.h>
#endif 

#ifdef HAVE_STDIO_H
#include <stdio.h>
#endif 

#include "definitions.h"


extern int width, height;
extern double **Vij, **Er;
extern unsigned char  **oddity;
extern int dielectrics_to_consider_just_now;
extern double r; 
extern int coupler;

#include "exit_codes.h"

double finite_difference_single_threaded()
{
  int i, j;
  int number_of_iterations=25;
  double capacitance_per_metre, energy_per_metre;

  /* The following might not look very neat, with a whole load of code being 
  written twice, when it would be posible to make it easier to read if the 
  'if(dielectrics_in_bitmap > 1)' was in an inner loop. However, the 
  following is almost certainly more efficient. It is not a good idea to 
  have any more than necessary in the inner loop. 

  The option to avoid the faster convergence algorithm has been didtched
  too, as this was in an inner loop. The faster covergence method seems
  to work fine, so there is no need to avoid using it */
 

  /* Note, that while the number of intterations requested is set in the first
  parameter to update_voltage_array, the actual number done is 4x higher, as 
  each computation id done in 4 directions */

  update_voltage_array(number_of_iterations, 0, width-1, 0, height-1, Vij, Vij);

  /* Once the voltage distribution is found, the energy in the field may be 
  found. This can be shown to be Energy = 0.5 * integral(E.D) dV, when 
  integrated over a volume V, and D.E is the vector dot product of E and
  D. 
  
  Energy per metre is 0.5 * D.E or (0.5*Epsilon)* E.E. Now E.E is given
  by Ex^2 + Ey^2 (by definition of a dot product. */

  energy_per_metre=0.0;
  for(i=0;i<width;++i)
    for(j=0;j<height;++j)
    { 
      energy_per_metre+=find_energy_per_metre(i,j);
    }
  if(coupler==FALSE)
    capacitance_per_metre=2*energy_per_metre;
  else
    capacitance_per_metre=energy_per_metre;
  return(capacitance_per_metre);
}
#endif /* #endif to #ifndef ENABLE_MP */

