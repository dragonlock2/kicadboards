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
#include "exit_codes.h"

#ifdef HAVE_STDLIB_H
#include <stdlib.h>
#endif

#ifdef SYS_TYPES_H
#include <sys/types.h>
#endif

#ifdef HAVE_STRINGS_H
#include <strings.h>
#endif

#ifdef HAVE_STRING_H
#include <string.h>
#endif

#ifdef HAVE_TIME_H
#include <time.h>
#endif

#ifdef HAVE_MATH_H
#include <math.h>
#endif


extern int errno;
int verbose=2;

/* desgin_coupler does two very different things in the one program
1) Given a frequency range, the required coupling factor, it calcuates
the odd and even mode impedances needed for a coupler. It does this
assuming the length of the coupler is lambda/4, although you can vary
that on the command line with the -l option. 

2) Once the optimal values for the even and odd mode impedances are
found, it itteratively looks up the odd and even mode impedances for two
think lines of various widths (w) and spacings (s), looking for the
combination that gives the best rms error between the required
impedances and those that will result with the coupler design as
presented. 

It is assumed by default that the height of the box is of one unit (1
mm, 1" etc, but this may be changed on the command line. This will scale
the parameters w and s by the same multiple.

*/

int main(int argc, char **argv) /* Read parameters from command line */
{
  int q, Hflag=FALSE;
  int calculate_physical_dimensions=FALSE;
  int calculate_physical_dimensions_to_high_accuracy=FALSE;
  double er;
  double Zo=-1, length=-1, fmin, fmax, fmean, fstep=-1, cf,  Zodd, Zeven; 
  double f, vcf, vcf_for_quarter_wave_line, w, s, error, error_max=1e30;
  double wanted_coupling_factor_in_dB, step=0.02, fq;
  double Zeven_x=-1, Zodd_x=-1, best_s=-1, best_w=-1;
  double height_of_box=1.0;
  double best_Zodd=-1, best_Zeven=-1, best_Zo=-1;

  /* SGI's MipsPro compiler is very fussy. The following line, along
  with one right at the end, forces Zo_x to be set and used,
  alhtough it serves no other userful purpose but to keep the 
  compiler happy */
  double Zo_x=1;
  while((q=get_options(argc,argv,"DeQqdCL:s:Z:H:")) != -1)
  switch (q) 
  {
    case 'd':
    calculate_physical_dimensions=TRUE;
    break;
    case 'D':
    calculate_physical_dimensions=TRUE;
    calculate_physical_dimensions_to_high_accuracy=TRUE;
    break;
    case 'e':
    give_examples_of_using_design_coupler();
    break;
    case 'C':
    print_copyright((char *) "2002");
    Hflag=TRUE;
    exit_with_msg_and_exit_code("",OKAY);
    break;
    case 'L':    
    length=atof(my_optarg); /* Sets the length of coupler */
    break;
    case 'H':
    height_of_box=atof(my_optarg); /* Set height of coupler's enclosure */
    Hflag=TRUE;
    break;
    case 's': /* Set frequncy steps in which coupling is computed */
    fstep=atof(my_optarg);
    break;
    case 'Z': /* Set the characteristic impedance - default is 50 Ohms */
    Zo=atof(my_optarg);
    break;
    case 'q': /* Run in quite mode, giving less output */
    verbose--;
    break;
    case '?':
      usage_design_coupler();
    break;
  } /* End of the switch statement */

  if(argc-my_optind != 3)  /* This should be so hopefully !! */
  {
    usage_design_coupler();
    exit_with_msg_and_exit_code("",PROGRAM_CALLED_WITH_WRONG_NUMBER_OF_ARGUMENTS);
  }
  wanted_coupling_factor_in_dB=atof(argv[my_optind]);
  fmin=atof(argv[my_optind+1]);
  fmax=atof(argv[my_optind+2]);
  fmean=(fmin+fmax)/2.0;
  if(fstep <0 )
    fstep=(fmax-fmin)/4.0;
  
  if (wanted_coupling_factor_in_dB <= 0.0 ) /* Only 0 can happen */
  {
    /* I don't think this can happen unless the user enter 0 as the
    first parameter, as a negative number entered will be taken as a
    command line option */
    fprintf(stderr,"\nThe coupled power must be less than the input power.");
    fprintf(stderr," But please enter a\n*positive* number in dB for the");
    fprintf(stderr," first command line parameter. If you want a \ncoupler");
    fprintf(stderr," with a coupled port that is 12 dB down on the input");
    fprintf(stderr," power, covering\n144-146 MHz, enter this as:\n\n");
    fprintf(stderr,"design_coupler 12 144 146\n\n");
    fprintf(stderr,"If you want the physical dimensions of the coupler");
    fprintf(stderr," designed for you, add the\n-d option on the command");
    fprintf(stderr," line, like this:\n\ndesign_coupler -q -12 144 146\n\n");
    fprintf(stderr,"If you run design_coupler with no command line");
    fprintf(stderr," arguments, like this:\n\ndesign_coupler\n\n");
    fprintf(stderr,"then design_coupler will print some information,");
    fprintf(stderr,"  showing *all* the options. \nIf you run design_coupler");
    fprintf(stderr," with the -e option like this:\n\n");
    fprintf(stderr,"design_coupler -e\n\n");
    fprintf(stderr,"lots of examples will be shown of the correct usage.\n");
    exit_with_msg_and_exit_code("",IMPOSSIBLE_COUPLING_COEFFICIENT);
  } 
  if (fmax <= fmin)
  {
    fprintf(stderr,"The second command line argumentent you gave, which");
    fprintf(stderr," is for the *minimum*\noperating frequenncy in MHz,");
    fprintf(stderr," is less than the third argument, which is the\n");
    fprintf(stderr,"*maximum* operating frequency in MHz.\n\n");
    fprintf(stderr,"If you want a coupler");
    fprintf(stderr," with a coupled port that is 12 dB down on the input\n");
    fprintf(stderr,"power, covering 144-146 MHz, enter this as:\n\n");
    fprintf(stderr,"design_coupler 12 144 146\n\n");
    fprintf(stderr,"If you want the physical dimensions of the coupler");
    fprintf(stderr," designed for you, add the\n-d option on the command");
    fprintf(stderr," line, like this:\n\ndesign_coupler -d 12 144 146\n\n");
    fprintf(stderr,"If you run design_coupler with no command line arguments,");
    fprintf(stderr," then design_coupler\nwill print some information,");
    fprintf(stderr," showing *all* the options. If you run\ndesign_coupler");
    fprintf(stderr," with the -e option like this:\n\n");
    fprintf(stderr,"design_coupler -e\n\n");
    fprintf(stderr,"lots of examples will be shown of the correct usage.\n");
    fprintf(stderr,"Exiting ...\n");
    exit_with_msg_and_exit_code("",FMAX_NOT_ABOVE_FMIN);
  }
  if (Zo < 0.0)
    Zo=50.0; 
  if(length<0.0)
    length=75.0/fmean;  /* By default, make it a quarter wave long */
  /* The following sent in an email by Paul AA1L, sums the theory up 
  You make Zo=50=sqrt(Zoo*Zoe) and
  c=(Zoe-Zoo)/(Zoe+Zoo), c being the voltage coupling coefficient.
  I.e., for a 20dB coupler c=0.1 is the midband
  coupling.  
  Coupling varies as sin^2(f/fq), fq being frequency where the coupled
  length is a quarter wave.  

  HOWEVER, the above is not quite the full story, as that says coupling
  peaks at sin(1), when in fact its sin(Pi/2)
  */
  
  /* vfc stands for 'voltage coupling factor' */

  /* I need to find values for Zodd and Zeven to use, but first convert
  the coupling factor on the command line into the voltage coupling
  factor c */
  
  /* vfc stands for 'voltage coupling factor' */

  /* When the line is a quarter wave, one can get any amount of coupling
  you want, including a vfc of 1, in which case all the power transfers
  to the coupled port. Normally, the vcf will be less than 1.0. for a 20
  dB couplier is it 0.1 */

  vcf_for_quarter_wave_line=1.0/pow(10.0,wanted_coupling_factor_in_dB/20.0); 

  fq=75/length; /* frequency at which line is a quarter wave long */

  /* If the line is less than a quarter wave long, then less power is
  coupled, so to compensate we need to increase the voltage coupling
  factor 'vcf above that of the value for a quarter wave line.
  Since the 'vcf' varies as sin(0.5 *PI * f/fq)^2, where 
  fq is the frequency at which the line is a quarter-wave long, we must
  divide the vcf_for_quarter_wave_line by sin(0.5 *PI*f/fq)^2 to get
  the required vcf. */
  vcf=vcf_for_quarter_wave_line*(1.0/sin(0.5*M_PI*fmean/fq));
  /* Check that the voltage coupling factor does not exceed one */
  if ( vcf > 1.0 )
  {
    fprintf(stderr,"\n*****ERROR****\n");
    fprintf(stderr,"Sorry, you can't make a %6.3f dB coupler with a coupled line of %7.4f m long.\n",wanted_coupling_factor_in_dB, length);
    fprintf(stderr,"Either couple off a smaller fraction of the main power to the coupled port,\n");
    fprintf(stderr,"or make the line closer to an odd multiple of a quarter wave.\n");
    fprintf(stderr,"Odd mulitples of a quarter wave are: %.4f, %.4f, %.4f, %.4f .. m\n", 75/fmean, 3*75/fmean, 5*75/fmean, 7*75/fmean);
    exit_with_msg_and_exit_code("",IMPOSSIBLE_TO_MAKE_COUPLER_THAT_LENGTH);
  }

  /* After mucking around with Mathematica a bit, I found it was
  possible to invert the equations */
  
  Zodd = sqrt(1-vcf)*Zo/sqrt(1+vcf);
  Zeven=Zo*Zo/Zodd;

  printf("\nFor a %.3f dB %.3f Ohm coupler with a length of %.4f m,\n",wanted_coupling_factor_in_dB, Zo, length);
  printf("you need to have an odd-mode impedance Zodd of %.3f Ohms and\n",Zodd);
  printf("an even mode impedance Zeven of %.3f Ohms\n\n",Zeven);
  if(verbose >=1) /* Only print if user does not specifiy and -qq options */
  {
    printf("%.3f dB down <-- ************************** ---> %3.3f Ohm termination\n\n",wanted_coupling_factor_in_dB,Zo);
    printf("Drive this port --> ************************** ---> %3.3f Ohm termination\n",Zo);
    printf("                    <------- %8.4f m ----->\n",length);
    printf("\nDrive Port 1, coupler out of port 2 and terminate the other ports in Zo\n");
    printf("Such a coupler will have the response indicated below.\n\n");
  /*printf("length =%.4f mean=%.3f vcf=%.3f vcf_for_quarter_wave_line=%.3f \n",length, fmean, vcf, vcf_for_quarter_wave_line);*/
  }
  for(f=fmin; f<=fmax; f+=fstep)
  {
    cf=20*log10(vcf*sin(0.5*M_PI*f/fq)); /* This is what is now needed for some given length (and so fq) */
    if(verbose == 2)
      printf("f = %7.3f MHz   coupling is %.3f dB down on the main arm\n",f,cf);
  }
  printf("\nYou may force the length to be any value you want using the -L option - it does\nnot have to be %.4f metres long\n",length);
  if(calculate_physical_dimensions==FALSE)
  {
    printf("You may try to find a coupler with these dimensions using the -d option\n\n");
    printf("Currently the -d option is not that fast, as it uses a brain-dead algorithm\n");
    printf("Hopefully one day the algorithm will be speeded up.\n");
  }
  if(calculate_physical_dimensions==TRUE)
  {
    er=1.0;
    printf("Please be patient - this will take a few minutes or so\n");
    for(s = 0.02; s<=100; s+=step)
    {
      for(w = 0.02; w<= 11.0; w += step)
      {
	/* Results are calculated assuming the box is one unit (mm, inch
	etc) high and later scaled */

        calculate_Zodd_and_Zeven(&Zodd_x, &Zeven_x, &Zo_x, w, 1.0, s, er);
	error=pow(Zodd-Zodd_x,2.0) + pow(Zeven-Zeven_x,2.0);
	if( error < error_max )
	{
	  best_s=s; 
	  best_w=w; 
	  best_Zo=sqrt(best_Zo * best_Zeven);
	  best_Zodd=Zodd;
	  best_Zeven=Zeven;
	  error_max=error;
        }
      }
    }
    printf("w = %.4f s = %.4f which gives Zo = %.4f Zodd = %.4f Zeven = %.4f\n",best_w, best_s, best_Zo, best_Zodd, best_Zeven);
    /* Now try to get closer, if -D option given */
    if (calculate_physical_dimensions_to_high_accuracy == TRUE)
    {
      for(s = best_s-step; s<=best_s+step; s+=step/1000)
      {
        for(w = best_w-step; w<= best_w+step; w += step/1000)
        {
          calculate_Zodd_and_Zeven(&Zodd_x, &Zeven_x, &Zo_x, w, 1.0, s, er);
	  error=fabs(Zodd-Zodd_x) + fabs(Zeven-Zeven_x);
	  if( error < error_max )
          {    
            best_s=s; 
	    best_w=w; 
	    best_Zodd=Zodd;
	    best_Zeven=Zeven;
	    error_max=error;
          }
        }
      }
    }
    best_Zo=sqrt(best_Zodd * best_Zeven);
    if(verbose <= 0)
    {
      printf("|-----------^------------------------------------------------------------------|\n");
      printf("|           |                                                                  |\n");
      printf("|           |              <---w---><-----s----><---w-->                       |\n");
      printf("|           H              ---------            --------                       |\n");
      printf("|           |                                                                  |\n");
      printf("|           |   Er=1.0 (air)                                                   |\n");
      printf("------------v------------------------------------------------------------------\n");
      printf("<-----------------------------------------W----------------------------------->\n");
    }
    printf("H =%.4f w = %.4f s = %.4f\n",height_of_box, height_of_box*best_w, height_of_box*best_s);
    printf("W must be *at least* %.4f, but larger does not matter.\n",5*height_of_box+ 2*best_w*height_of_box + height_of_box*best_s);
    printf("These dimensions give Zo = %.4f Zodd = %.4f Zeven = %.4f Ohms\n", best_Zo, best_Zodd, best_Zeven);
    if(Hflag==FALSE)
    {
      printf("****NOTE ****\n");
      printf("Although H is shown as 1.0, it can be 1 mm, 1 cm or even 1 m. It is important\n");
      printf("that w is %.4f times whatever H is, and that s is %.4f times whatever H is, but the absolute numbers are irrelavant.\n",best_w, best_s);
      printf("If you know the height H of your enclosure, use the -H option to indicate\n");
      printf("its value. This will ensure all the dimensions are scaled automatically for you.\n"); 
    }
    printf("****NOTE 2****\n");
    printf("The length *must* be %.4f m if you use these dimensions for W, H, w and s.\n",length); 
    printf("If %.4f m is inconvenient, change it with the -L option and recalculate\n to get new values of W, H, w and s\n",length);
    printf("See: http://atlc.sourceforge.net\n");
    printf("See: http://atlc.sourceforge.net/couplers.html\n");
  }
  return(OKAY);
}
