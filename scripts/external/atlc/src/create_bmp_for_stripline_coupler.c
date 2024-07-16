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

/* The following calculates the odd and even mode impedances between two
zero thickness strips of width w, spaced a distance s between two
groundplanes of spacing h. */
#include "config.h"


#define RATIO 8
#include "definitions.h"
#include "exit_codes.h"

#ifdef HAVE_STDLIB_H
#include <stdlib.h>
#endif

#ifdef HAVE_STRING_H
#include <string.h>
#endif

double WW, HH, ww, Er1, Er2;
static double ss; 
int W, H, s,  w,  verbose=FALSE;

int main(int argc, char **argv)
{
  double er, return_error;
  double Zodd, Zeven, Zo;
  int bmp_size=DEFAULT_COUPLER_BMP_SIZE, q; 
  FILE *image_data_fp;
  struct transmission_line_properties optimise;
  struct transmission_line_properties not_used;

  not_used.W=1; /* keep MipsPro compiler happy on IRIX */

  while((q=get_options(argc,argv,"Cb:v")) != -1)
  switch (q) 
  {
    case 'C':
      print_copyright((char *) "2002");
      exit_with_msg_and_exit_code("",OKAY);
    break;
    case 'b':
      bmp_size=atol(my_optarg); 
    break;
    case 'v':
      verbose++;
    break;
  }
  if( bmp_size < 6 || (argc-my_optind != 5) || bmp_size>28)
  {
    usage_create_bmp_for_stripline_coupler();
    exit_with_msg_and_exit_code("",PROGRAM_CALLED_WITH_WRONG_NUMBER_OF_ARGUMENTS);
  }
  HH=atof(argv[my_optind]);
  ww=atof(argv[my_optind+1]);
  ss=atof(argv[my_optind+2]);
  if(HH<0 || ww <0 || ss<0)
  {
    fprintf(stderr,"Sorry, W, H and s must all be greater than 0\n");
    exit_with_msg_and_exit_code("",DIMENSION_LESS_THAN_ZERO);
  }
  er=atof(argv[my_optind+3]);
  Er1=er;
  Er2=er;
  if(er < 1.0)
  {
    fprintf(stderr,"Sorry, you can't have a dielectric constand Er of less than 1.0\n");
    exit_with_msg_and_exit_code("Sorry, you can't have a dielectric constand Er of less than 1.0",PERMITTIVITY_LESS_THAN_1);
  }
  if( (image_data_fp=fopen(argv[my_optind+4],"wb")) ==NULL)
    exit_with_msg_and_exit_code("Can't open binary file for writing",CANT_OPEN_FOR_WRITING);
  WW=2.0*ww+ss+RATIO*HH;
  optimise.float_values[0]=WW            ;   /* minimum width as a float*/
  optimise.float_values[1]=HH;               /* height in floats */
  optimise.float_values[2]=ww;               /* stripline width */
  optimise.float_values[3]=ss;               /* spacing between the strips */

  optimise.importance[0]=NOT_IMPORTANT;      /* W is non critical */
  optimise.importance[1]=MOST_IMPORTANT;          /* H is critical */
  optimise.importance[2]=IMPORTANT;          /* w is critical */
  optimise.importance[3]=IMPORTANT;     /* s is most critical */

  optimise.odd_or_even[0]=DONT_CARE;        /* W can be odd or even */
  optimise.odd_or_even[1]=ODD;              /* H must be even */
  optimise.odd_or_even[2]=DONT_CARE;        /* w can be odd or even */
  optimise.odd_or_even[3]=DONT_CARE;        /* s can be odd or even */

  /* We will now optimise for the 4 parameters W, H, w and s, forcing H
  to be odd, and not bothering what the width is, as long as its about
  right. */

  return_error=calculate_integer_values(&optimise, 4, bmp_size);
  if(verbose >=2)
    printf("error returned from calculate_integer_values=%g\n", return_error);
  W=optimise.best[0];
  H=optimise.best[1];
  w=optimise.best[2];
  s=optimise.best[3];
  write_bitmap(image_data_fp, not_used);
  if(verbose >= 1)
  {
    calculate_Zodd_and_Zeven(&Zodd, &Zeven, &Zo, ww, HH, ss, er);
    printf("The actual dimensions you gave have theoretical imedances of:\n");
    printf("        Zodd= %f Zeven= %f Zo= %f (Ohms) ww=%f HH=%f ss=%f er=%f\n\n", Zodd, Zeven, Zo,ww,HH,ss,er);
    calculate_Zodd_and_Zeven(&Zodd, &Zeven, &Zo, (double) w, (double) H-10, (double) s, er);
    printf("The bitmap produced (which approximates what you want) should have:\n");
    printf("   Zodd= %f Zeven= %f Zo= %f (Ohms)\n", Zodd, Zeven, Zo);
  }
  return(OKAY);
}
