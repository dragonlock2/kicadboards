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

#ifdef HAVE_STDLIB_H
#include <stdlib.h>
#endif  

#ifdef HAVE_STRING_H
#include <string.h>
#endif

#include "definitions.h"
#include "exit_codes.h"

extern char *my_optarg;
int main(int argc, char **argv)
{
  double g, gmin=0.5, gmax=5, gstep=0.5;  
  double s, smin=0.5, smax=5, sstep=0.5;
  double w, wmin=0.5, wmax=5, wstep=0.5;
  double Er1=1, Er2=1, h=1, t=1; /* keep the compiler from issuing warnings */   
  double Zcomm, Zdiff, Zodd, Zeven;  
  double Er_odd, Er_even, Zo;
  double error_min=1e100, error; 
  double ideal_Zodd=0, ideal_Zeven=0; 
  char *outfile_name, *temporary_bmp_file, *temporary_txt_file;
  int x, q, exit_code;
  char *cmd, *null;
  FILE *fp, *fp_best;
  outfile_name = string(0,4000);
  cmd = string(0,4000);
  null = string(0,4000);
  temporary_bmp_file = string(0,4000);
  temporary_txt_file = string(0,4000);
  while((q=get_options(argc,argv,"g:b:G:w:W:s:S:")) != -1)
  switch (q) 
  {
    case 'C':
      print_copyright( (char *) "1996-2002");
      exit_with_msg_and_exit_code("",OKAY);
    break;
    case 'g':
      gmin=atof(my_optarg);
    break;
    /*
    case 'b':
      bmp_size=atoi(my_optarg);
    break;
    */
    case 'G':
      gmax=atof(my_optarg);
    break;
    case 'h':
      gstep=atof(my_optarg);
    break;
    case 's':
      smin=atof(my_optarg);
    break;
    case 'S':
      smax=atof(my_optarg);
    break;
    case 't':
      sstep=atof(my_optarg);
    break;
    case 'w':
      wmin=atof(my_optarg);
    break;
    case 'W':
      wmax=atof(my_optarg);
    break;
    case 'x':
      wstep=atof(my_optarg);
    break;
    case '?':
      usage_find_optimal_dimensions_for_microstrip_coupler();
    break;
  }
  if(argc-my_optind == 7)
  {
    h=atof(argv[my_optind]);
    t=atof(argv[my_optind+1]);
    Er1=atof(argv[my_optind+2]);
    Er2=atof(argv[my_optind+3]);
    ideal_Zodd=atof(argv[my_optind+4]);
    ideal_Zeven=atof(argv[my_optind+5]);
    check_parameters_for_find_optimal_dimensions_for_microstrip_coupler(h,t,Er1,Er2,ideal_Zodd,ideal_Zeven);
    (void) strcpy(outfile_name, argv[my_optind+6]);
  }
  else
   usage_find_optimal_dimensions_for_microstrip_coupler(); 
  (void) strcpy(temporary_bmp_file,"1.bmp");
  (void) strcpy(temporary_txt_file,"1.txt");
  if( (exit_code=pclose(popen("rm 1.txt 1.bmp","w"))) != 0)
  {
    fprintf(stderr,"rm 1.txt 1.bmp did not returned an exit code of %d\n",exit_code);
    exit(exit_code);
  }
  for(g=gmin; g <=gmax; g+=gstep)
  {
    for(w=wmin; w<=wmax; w+=wstep)
    {
      for(s=smin; s<=smax; s+=sstep)
      {
	sprintf(cmd,"create_bmp_for_microstrip_coupler %f %f %f %f %f %f %f %s\n",w, s, g, h, t, Er1, Er2,temporary_bmp_file);
	if( (exit_code=pclose(popen(cmd,"w"))) != 0)
        {
          fprintf(stderr,"pclose(popen(%s,\"w\"))) returned with an exit code of %d\n",cmd, exit_code);
          exit(exit_code);
        }
	sprintf(cmd,"atlc -S -s %s > %s\n", temporary_bmp_file, temporary_txt_file);
	exit_code=pclose(popen(cmd,"w"));
	if( (exit_code=pclose(popen(cmd,"w"))) != 0)
        {
          fprintf(stderr,"pclose(popen(%s,\"w\"))) returned with an exit code of %d\n",cmd,exit_code);
          exit(exit_code);
        }
	if ((fp=fopen(temporary_txt_file,"r")) ==NULL)
	  exit_with_msg_and_exit_code("Error #1 cant't open file in find_optimal_dimensions_for_microstrip_coupler.c", CANT_OPEN_FILE_FOR_READING);
	fscanf(fp,"%s %d %s %lf %s %lf %s %lf %s %lf %s %lf %s %lf %s %lf",null,&x,null,&Er_odd,null,&Er_even, null, &Zodd,null,&Zeven,null,&Zo, null, &Zdiff,null,&Zcomm);
	if (fclose(fp) !=0)
	  exit_with_msg_and_exit_code("Error #2 Unable to close file in ind_optimal_dimensions_for_microstrip_coupler.c",CANT_CLOSE_FILE);
	printf("x=%d Er_odd=%f Er_even=%f Zodd=%f Zeven=%f Zo=%f Zdiff=%f Zcomm=%f\n",x, Er_odd,Er_even,Zodd, Zeven,Zo, Zdiff, Zcomm);
	error=fabs(Zodd-ideal_Zodd)/ideal_Zodd+fabs(Zeven-ideal_Zeven)/ideal_Zeven;
	/* By forcing the error to be a be not just bettter, but better by at 
	least TINY, it means the results will be the same on differerent computers,
	with no difference due to rouunding errors */
	if(error< error_min+TINY)
	{
	  error_min=error;
	  printf("best so far = s=%f w=%f g=%f Zodd=%f Zeven=%f Zdiff=%f Zcomm=%f error=%f\n",s,w,g, Zodd, Zeven,Zdiff, Zcomm,error);
	  if ((fp_best=fopen(outfile_name,"a")) == NULL)
	    exit_with_msg_and_exit_code("Error #3 Can't open file output file update",CANT_OPEN_FILE_FOR_APPENDING);
	  fprintf(fp_best,"best so far = s=%f w=%f g=%f Zodd=%f Zeven=%f Zdiff=%f Zcomm=%f\n",s,w,g, Zdiff, Zcomm,Zodd, Zeven);
	  if (fclose(fp_best)  != 0)
	    exit_with_msg_and_exit_code("Error #4 Unable to close file in optimal_dimensions_for_microstrip_coupler.c",CANT_CLOSE_FILE);
        } /* end of if */
      } /* end of for s */
    } /* end of for w */
  } /* end of for g */
  return(0);
}
	
    
