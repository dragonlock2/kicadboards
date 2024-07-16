/* The function 'setup_arrays sets the cell_type[i][j] to be DIELECTRIC
if the material is non-metal. This function expands on that, checking if
the adjactent cells are dielectrics, or metals, and if dielectric,
whether or nor there is a boundary vertically, or horizontally between
two different dielectrics. Doing this once, is much faster than doing it
inside a loop, checking for all possibilities each time one needs to
know. */

#include "definitions.h"

extern int width, height;
extern unsigned char **oddity, **cell_type; 
extern double **Er;

void check_for_boundaries(void) 
{
}

