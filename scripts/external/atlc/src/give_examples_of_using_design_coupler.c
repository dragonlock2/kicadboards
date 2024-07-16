#include "config.h"

#ifdef HAVE_STDIO_H
#include <stdio.h>
#endif

#ifdef HAVE_STDLIB_H
#include <stdlib.h>
#endif

#include "definitions.h"
#include "exit_codes.h"

void give_examples_of_using_design_coupler(void)
{
  printf("Here are a examples of how to use 'design_coupler'\n");
  printf("In the examples, the %c sign is used in front of anything you must type\n",'%');
  printf("which is what you will probably see when using the csh or tcsh as a shell. It\n");
  printf("would probably be a $ sign if using the sh or bash shell. \n\n");
  printf("To find the odd and even mode impedances and frequency response of a 50 Ohm\n"); 
  printf("coupler, covering 130 to 170 MHz, with a coupling coefficient of 30 dB:\n\n");
  printf("%c design_coupler 30 130 170\n\n",'%');
  printf("Note the frequency response is symmetrical about the centre frequency at 0.192 dB\n");
  printf("below that wanted. You may wish to redesign this for a coupling coefficient of \n");
  printf("about 29.9 dB, so the maximum deviation from the ideal 30.0 dB never exceeds 0.1 dB\n");
  printf("Note the length suggested is 0.5 m (nearly 20\") is a quarter wave at\n");
  printf("the centre frequency of 150 MHz. You might find this a bit too long, so\n");
  printf("let's specify a length of 0.25 m.\n\n");
  printf("%c design_coupler -L 0.25 30 130 170\n\n",'%');
  printf("What you may notice is that while the coupling to the coupled port is exactly\n");
  printf("30 dB below the input power at the centre frequency (150 MHz) it is \n");
  printf("no longer symmetrical about the centre frequency. Also, deviations from the\n");
  printf("ideal 30 dB are now much larger, with a maximum error of 1.012 dB\n");
  printf("Unlike the case when the length is the default quarter wave, there is not much\n");
  printf("you can do about this, since the deviations occur in both directions.\n\n");
  printf("Now assume you are reasonably happy with the response when the length is 250 mm\n");
  printf("but would like to see the response at every 2.5 MHz. This can be done using the\n");
  printf("-s option to design_coupler.\n\n");
  printf("%c design_coupler -L 0.25 -s 2.5 30 130 170\n\n",'%');
  printf("Assuming the performance is acceptable, the dimensions of the coupler can\n"); 
  printf("be determined by adding the -d option. This will design a coupler that must look\n");
  printf("like the structure below. The two inner conductors, which are spaced equally\n");
  printf("between the top and bottom edges of the outer conductor, must be very thin.\n");
  printf("These are placed along the length of a box of width W, height H and of\n");
  printf("a length L determined by the user, which in this case is 250 mm.\n");
  printf("|-----------^------------------------------------------------------------------|\n");
  printf("|           |                                                                  |\n");
  printf("|           |              <---w---><-----s----><---w-->                       |\n");
  printf("|           H              ---------            --------                       |\n");
  printf("|           |                                                                  |\n");
  printf("|           |   Er=1.0 (air)                                                   |\n");
  printf("------------v------------------------------------------------------------------\n");
  printf("<-----------------------------------------W----------------------------------->\n");
  printf("The program reports: H = 1.0, ; w = 1.44 ; s = 0.44\n");

  printf("The height of the box H must be small compared to the length L, (perhaps no\n");
  printf("more than 7%c of the length), or 17.5 mm in this case, with a length of 250 mm,\n",'%');
  printf("otherwise fringing effects will be significant. The width of the structure W\n");
  printf("should be as large as possible. The program suggests making this 5*H+2*w+s. The\n");
  printf("7%c and 5*H+2*w+s are educated guesses, rather than exact figures. There is\n",'%');
  printf("no problem in making the width  larger than 5*H+2*w+s. The length L must be\n");
  printf("kept at 250 mm. The RATIO of the dimensions H, w and s (but not L or W\n");
  printf("must be kept constant. W just needs to be sufficiently large - it is\n");
  printf("uncritical.  \n\n");
  printf("If you happened to have some 15 mm square brass available, then using that\n");
  printf("for the side-walls would require that H becomes 15*1.0 = 15 mm,\n");
  printf("w = 15*1.44 = 21.6 mm  and s = 15*0.44 = 6.6 mm\n\n");
  printf("There is no need to compute the above scaling with a calculator, as using\n");
  printf("The -H option allows one to specify the height H. The program then reports the\n");
  printf("exact dimensions for the length L, height H, w, s and suggests a minimum width\n");
  printf("for W.\n\n");
  printf("In summary we have:\n");
  printf("                   30 dB coupler +1.02 dB / -0.78 dB for 130 to 170 MHz\n");
  printf("                   Length L = 250 mm, height H = 15 mm, stripline spacing s\n");
  printf("                   = 6.6 mm, stripline width w = 21.6 mm, width W >= 124 mm\n");
  printf("By default, design_coupler prints a lot of information to the screen.\n");
  printf("This can be reduced by the -q option or reduced to only one line with -Q\n");
  printf("Other options include -Z to change the impedance from the default 50 Ohms\n");
  printf("and -C to see the fully copyright, Licensing and distribution information\n");
  exit_with_msg_and_exit_code("",OKAY);
}
