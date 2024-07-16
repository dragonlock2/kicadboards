/*
atlc - arbitrary transmission line calculator, for the analysis of
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

Dr. David Kirkby, e-mail drkirkby@gmail.com 

*/
#include "config.h"

#ifdef HAVE_STRING_H
#include <string.h>
#endif

#ifdef HAVE_STRINGS_H
#include <strings.h>
#endif

#ifdef HAVE_STDLIB_H
#include <stdlib.h>
#endif  

#ifdef HAVE_ERRNO_H
#include <errno.h>
#endif

#ifdef HAVE_LIMITS_H
#include <limits.h>
#endif

#include "definitions.h"
#include "exit_codes.h"

#ifdef ENABLE_POSIX_THREADS
#include <pthread.h>
#endif

#ifdef ENABLE_MPI
#include <mpi.h>
#endif


#ifdef WINDOWS
#pragma hrdstop
#include <condefs.h>
#endif



struct pixels Er_on_command_line[MAX_DIFFERENT_PERMITTIVITIES];
struct pixels Er_in_bitmap[MAX_DIFFERENT_PERMITTIVITIES];

double **Vij;
double **Er;
unsigned char **oddity; 
unsigned char **cell_type; 
unsigned char *image_data;
int width=-1, height=-1;
extern int errno;
int number_of_workers=MAX_THREADS; 
int non_vacuum_found=FALSE;
int dielectrics_to_consider_just_now;
int coupler=FALSE;
double r=1.90;

char *inputfile_name;

int main(int argc, char **argv) /* Read parameters from command line */
{
  FILE *where_to_print_fp=stdout, *image_data_fp;
  char *outputfile_name, *appendfile_name, *output_prefix;
  long i;
  size_t size;
  int offset;
  int q;
  char *end;
  struct transmission_line_properties data;
  errno=0; 
  set_data_to_sensible_starting_values(&data);
  inputfile_name=string(0,1024);
  outputfile_name=string(0,1024);
  appendfile_name=string(0,1024);
  output_prefix=string(0,1024);
  /* only use this if we have both a multi-threaded application and that 
  with have the function */
  (void) strcpy(output_prefix,"");
  while((q=get_options(argc,argv,"Cr:vsSc:d:p:i:t:w:")) != -1)
  switch (q) 
  {
    case 'C':
      print_copyright( (char *) "1996-2002");
      exit_with_msg_and_exit_code("",1);
    break;
    case 'b':
      data.should_binary_data_be_written_tooQ=TRUE;
    break;
    case 'd':
      /* Read a colour from the command line */
      Er_on_command_line[data.dielectrics_on_command_line].other_colour=\
      strtol(my_optarg, &end, 16);
      /* Sepparte it into the Red, Green and Blue components */
      Er_on_command_line[data.dielectrics_on_command_line].blue=\
      Er_on_command_line[data.dielectrics_on_command_line].other_colour%256;
      Er_on_command_line[data.dielectrics_on_command_line].green=\
      Er_on_command_line[data.dielectrics_on_command_line].other_colour/(256);
      Er_on_command_line[data.dielectrics_on_command_line].red=\
      Er_on_command_line[data.dielectrics_on_command_line].other_colour/(256*256);
      end++; /* Gets rid of '=' sign which we put on the command line */
      Er_on_command_line[data.dielectrics_on_command_line].epsilon=atof(end);
      if (data.verbose_level > 1)
        printf("r=%x g=%x b=%x col=%x Er=%f\n",\
      Er_on_command_line[data.dielectrics_on_command_line].red,\
      Er_on_command_line[data.dielectrics_on_command_line].green, \
      Er_on_command_line[data.dielectrics_on_command_line].blue, \
      Er_on_command_line[data.dielectrics_on_command_line].other_colour, \
      Er_on_command_line[data.dielectrics_on_command_line].epsilon);
      data.dielectrics_on_command_line++;
    break;
    case 'c':
      data.cutoff=atof(my_optarg);
    break;
    case 'p':
      (void) strcpy(output_prefix,my_optarg);
    break;
    case 'r':
      data.r=atof(my_optarg);
      r=data.r;
    break;
    case 's':
      data.write_bitmap_field_imagesQ=FALSE;
    break;
    case 'S':
      data.write_binary_field_imagesQ=FALSE;
    break;
    case 't':
      number_of_workers=atol(my_optarg);
      if(number_of_workers > MAXIMUM_PROCESSING_DEVICES)
      {
         fprintf(stderr,"You are exceeded the %d limit set in the file definitions.h\n",MAXIMUM_PROCESSING_DEVICES);
	 fprintf(stderr,"If you really do want this many, you will need to recompile\n");    
         exit_with_msg_and_exit_code("",USER_REQUESTED_TOO_MANY_THREADS);
      }
#ifndef ENABLE_POSIX_THREADS
      if(number_of_workers != 0)
         exit_with_msg_and_exit_code("Error #1. The -t option can not be \
used, (except to  set t=0, which is an \nexception made to allow a \
benchmark to run), on a version of atlc that was \nnot configured with the \
--with-threads option, and hence built without the \nthreads library.\n",1);
#endif
    break;
    case 'w':
#ifndef ENABLE_MPI
      exit_with_msg_and_exit_code("Error #1a. The -w option can not be used on \
a version of atlc that was not\nconfigured with the --with-mpi option, \
hence built without the mpi\nlibrary.\n",1);
#endif
          break;
    case 'i': /* Lighten or darken images of E-field */
	  data.image_fiddle_factor=atof(my_optarg);
	  break;
    case 'v':
      data.verbose_level++;
    break;
    case '?':
      usage_atlc();
  } /* End of the switch statement */

  /* There should only be one argument to atlc, the bitmapfile name.
  There can be a few options though. We now check that there is only
  one argument */

  if(argc-my_optind == 1)  /* This should be so hopefully !! */
  {
#ifdef DEBUG
  if (errno != 0)
    fprintf(stderr,"errno=%d in atlc.c #2\n",errno);
#endif
    (void) strcpy(inputfile_name, argv[my_optind]);
    (void) strcpy(outputfile_name, output_prefix);
    (void) strcat(output_prefix,inputfile_name);
    (void) strcpy(outputfile_name,output_prefix);
    free_string(output_prefix,0,1024);
    read_bitmap_file_headers(inputfile_name, &offset, &size, &width, &height);

    /* Allocate all ram now, so atlc is sure to have it. There is no point
    in getting some now, starting work then finding atlc can't get the 
    rest of what is needed. */
    image_data=ustring(0L,(long)size);
    oddity=ucmatrix(0,width-1,0,height-1);
    cell_type=ucmatrix(0,width-1,0,height-1);
    Vij=dmatrix(0,width-1,0,height-1);
    Er=dmatrix(0,width-1,0,height-1);
    /* On Solaris systems, if the following is not executed, only one 
    thread will run at any one time, which rather defeats the object of 
    running multi-threaded. */

#ifdef ENABLE_POSIX_THREADS
#ifdef HAVE_PTHREAD_SETCONCURRENCY     
    pthread_setconcurrency(number_of_workers);
#endif 
#endif 
    
    /* Each thread solves the equations for a part of the voltage
    matrix. If there were more threads than columms we would have a
    problem. I'm not sure exactly how many can be got away with, but
    one is unlikly to have more cpus that matrix columns */

    /* In theory, it would be sensible to get atlc to be able to read
    from stdin. This is a test, that checks if the filename is '-', and
    if so assumes its reading from stdin. So far, the program is
    unable to read from stdin, so this code is not really doing
    anything useful, but might be expanded at a later date. */
#ifdef DEBUG
  if (errno != 0)
    fprintf(stderr,"errno=%d in atlc.c #3\n",errno);
#endif
    if( strcmp(argv[my_optind],"-") != 0)
    {
      if( (image_data_fp=fopen(inputfile_name, "rb")) == NULL)
      {
        fprintf(stderr,"Error #3. Can't open %s!!!!!\n", argv[my_optind]);
        exit_with_msg_and_exit_code("",3);
      }
      if(fseek(image_data_fp, offset, SEEK_SET)!=0)
      {   
        fprintf(stderr,"Error #4. Sorry, unable to seek to the correct part \
	(offset=%d) of the bmp image\n", offset);
	exit_with_msg_and_exit_code("",4);
      }
    } /* end of if( strcmp(argv[my_optind],"-") != 0) */
    else
      image_data_fp=stdin;
    /* For some unknown reason Microsoft's Visual C++ was unhappy to read
    the bitmap image using an fread() call. Instead, the following two 
    stupid lines fixed that issue. This will only get compiled under 
    Windoze, the more sensible fread call being used on other operating 
    systems. */

#ifdef WINDOWS
    for(i=0; (i < (long)size ) && (feof(image_data_fp)==0); i++)
      image_data[i]=(unsigned char)fgetc(image_data_fp);
#else
	i = fread(image_data,  size, 1, image_data_fp);
#endif
    if((ferror(image_data_fp) || (i != 1 )))
    {
      fprintf(stderr,"Error #5. Unable to read all of the image data properly\n");
      exit_with_msg_and_exit_code("",5);
    }
    /* declare matrix's to indicate what pixels are fixed and variable */
    /* We now fill the following 3 arrays with the correct data, based on the 
    contents of the bitmap image */

    setup_arrays(&data);
    set_oddity_value();

    /* If there are multiple dielectrics, the impedance calculations
    needs to be done twice. We start by doing them once, for an vacuum
    dielectric. If necessary, they will be done again */
    do_fd_calculation(&data, size, where_to_print_fp,outputfile_name);
  }
  else
  {
    usage_atlc();
    return(PROGRAM_CALLED_WITH_WRONG_NUMBER_OF_ARGUMENTS); 
  }
  free_string(inputfile_name,0,1024);
  free_string(outputfile_name,0,1024);
  free_string(appendfile_name,0,1024);
  free_ustring(image_data,0L,(long) size);
  free_ucmatrix(oddity,0,width-1,0,height-1);
  free_ucmatrix(cell_type,0,width-1,0,height-1);
  free_dmatrix(Vij, 0,width-1,0,height-1);
  free_dmatrix(Er,0,width-1,0,height-1);
  fclose(image_data_fp);
  return(OKAY); 
}
