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

/* The program widestrip is a pre-processor for atlc. It produces bitmaps 
of a thin strip, between two wide plates */
#include "config.h"

#define RATIO 4           /* W = H*RATIO+w */

#ifdef HAVE_STDLIB_H
#include <stdlib.h>
#endif  

#ifdef HAVE_STRING_H
#include <string.h>
#endif  
#include "definitions.h"
#include "exit_codes.h"

#ifdef WINDOWS
#pragma hrdstop
#include <condefs.h>
#endif

int verbose=0;

extern int main(int argc, char **argv) /* Read parameters from command line here   */
{
  int W, H, w, size_of_image, q;
  int user_requires_effectively_infinite_width=FALSE;
  double Zo;
  unsigned char *unaligned_image_vector, *aligned_image_vector;
  FILE *fp;
#ifndef HAVE_MEMSET
  int memory_location;
#endif

  while((q=get_options(argc,argv,"Cvi")) != -1)
  switch (q) 
  {
    case 'C':
      print_copyright((char *) "2002");
      exit_with_msg_and_exit_code("",OKAY);
    break;
    case 'i':
      user_requires_effectively_infinite_width=TRUE;
    break;
    case 'v':
      verbose++;
    break;
    case '?':
      usage_create_bmp_for_symmetrical_stripline();
    break;
  } /* End of the switch statement */
  if(argc-my_optind !=4)
  {
    usage_create_bmp_for_symmetrical_stripline();    
    exit_with_msg_and_exit_code("",PROGRAM_CALLED_WITH_WRONG_NUMBER_OF_ARGUMENTS);
  }
  W=atoi(argv[my_optind]);
  H=atoi(argv[my_optind+1])+2*BORDER;
  if(H%2==0) /* make it odd, so that the inner can sit in the middle */
  {
    H++;
    printf("H needs to be odd, so the inner conductor (1 pixel high) will fit\
    centrally. Hence H has been increased to %d pixels\n",H);
  }
  w=atoi(argv[my_optind+2]);
  if ((W < RATIO*H + w) && user_requires_effectively_infinite_width==TRUE)
  {
    fprintf(stderr,"For this to be a valid test of atlc, the width should be\n");
    fprintf(stderr,"infinite. Since you used the -i option (indicationg you\n");
    fprintf(stderr,"want the width W to effectively infinite, W must exceed w + %dxH.\n",RATIO);
    fprintf(stderr,"Therefore W has been is set to %d\n",RATIO*H+w );
    W=RATIO*H+w;
  }
  if(W <= 5 || H <= 5)
    exit_with_msg_and_exit_code("W or H is under 6, which is stupid (remember these are pixels !! in this program)",W_OR_H_TOO_SMALL);
  aligned_image_vector=ustring(0,(W+3)*3*H+100);
  unaligned_image_vector=ustring(0,(W+3)*3*H+100);

  if((fp=fopen(argv[my_optind+3],"wb")) == NULL)
  {
    exit_with_msg_and_exit_code("Error in opening file in create_bmp_for_symmetrical_stripline",CANT_OPEN_FOR_WRITING);
  }
  aligned_image_vector=ustring(0,(W+3)*3*H);
  unaligned_image_vector=ustring(0,(W+3)*3*H);

#ifdef HAVE_MEMSET
  (void) memset((void *) (aligned_image_vector),0x00,(size_t) W*H*3);
#else
  for(memory_location=0; memory_location < W*H*3; memory_location++)
    aligned_image_vector[memory_location]=0;
#endif

  /* Fill a vector with */
  fill_image_vector_for_thin_strip(W,H,w,unaligned_image_vector);
  size_of_image=align_bitmap_image(W, H, unaligned_image_vector,aligned_image_vector);

  write_bitmap_out(aligned_image_vector, fp, size_of_image, W, H);
  /* write_bitmap_out closes the file pointer */
  Zo=calculate_symmetrical_stripline_impedance(H-2*BORDER,w);
  if(verbose >=1 && W >= RATIO*H + w )
    printf("Zo is theoretically %f Ohms (assuming W is infinite)\n",Zo);
  else if (verbose >=1 && W < RATIO*H + w){
    exit_with_msg_and_exit_code("A theoretical value for Zo can't be computed as the width W is too small",1);
  }
  return(OKAY); /* This does not get executed, but keeps the compiler
  happier, as otherwise it gives a warning about control reaching the
  end of a non-void function */
}
