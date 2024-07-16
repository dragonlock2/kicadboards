/* atlc - arbitrary transmission line calculator, for the analysis of
extern int number_of_workers;
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

#include "definitions.h"

extern int append_flag;
extern int dielectrics_to_consider_just_now, coupler;
extern int num_pes;
extern double **Vij;
extern int height;
extern int number_of_workers;

void do_fd_calculation(struct transmission_line_properties *data, size_t size, FILE *where_to_print_fp, char *inputfile_filename)
{
  double capacitance_old, capacitance;
  double velocity_of_light_in_vacuum;
  int count=0;
  /*
  if (data->dielectrics_in_bitmap > 1) {
    fprintf(stderr,"\nSorry, but on the 15th October 2003 I was advised there is an\n");
    fprintf(stderr,"error in atlc when computing systems with multiple dielectrics.\n");
    fprintf(stderr,"So until this problem is fixed, the facility has been disabled.\n\n");
    fprintf(stderr,"I hope to release a new version shortly without this problem.\n");
    exit(1);
  }
  */
  /* The line of best fit of non_metalic_pixels vs iterations required
  is y=0.0011 * non_metallic_pixels  + 283. 

  I'll ensure finite_difference is called about 10x by using 
  0.00011 * the number of non-metallic elements  +28 as the number 
  of times finite_difference is called each time */



  /* The following 10 lines are for a single dielectric 2 conductor line */
  if (data->couplerQ==FALSE)
  {
    if(data->verbose_level >= 2)
      printf("Solving assuming a vacuum dielectric\n");
    capacitance=VERY_LARGE; /* Can be anything large */
	dielectrics_to_consider_just_now=1;
	data->dielectrics_to_consider_just_now=1;

    do /* Start a finite calculation */
    {
      capacitance_old=capacitance;

#ifdef ENABLE_POSIX_THREADS
      if (number_of_workers == 0)
        capacitance=finite_difference_single_threaded();
      else
        capacitance=finite_difference_multi_threaded();
#else  
      capacitance=finite_difference_single_threaded();
#endif

      data->C_vacuum=capacitance;
      data->C=capacitance;
      data->L_vacuum=MU_0*EPSILON_0/capacitance; /* Same as L in *ALL* cases */
      data->Zo_vacuum=sqrt(data->L_vacuum/data->C_vacuum);  /* Standard formaul for Zo */
      data->C=capacitance; 
      if (data->dielectrics_in_bitmap == 1) /* Just get C by simple scaling of Er */
      {
        data->C=capacitance*data->found_this_dielectric;  /* Scaled by the single dielectric constant */
		data->Er=data->found_this_dielectric;
      }
      else
		data->Er=1.0;
      data->Zo=sqrt(data->L_vacuum/data->C);  /* Standard formula for Zo */
      data->Zodd=sqrt(data->L_vacuum/data->C);  /* Standard formula for Zo */
      velocity_of_light_in_vacuum=1.0/(sqrt(MU_0 * EPSILON_0)); /* around 3x10^8 m/s */
      data->velocity=1.0/pow(data->L_vacuum*data->C,0.5);
      data->velocity_factor=data->velocity/velocity_of_light_in_vacuum;
      data->relative_permittivity=sqrt(data->velocity_factor); /* ??? XXXXXX */
      if(data->verbose_level > 0 ) /* Only needed if intermediate results wanted.  */
        print_data_for_two_conductor_lines(*data, where_to_print_fp, inputfile_filename);
      count++;
    } while (fabs((capacitance_old-capacitance)/capacitance_old) > data->cutoff); /* end of FD loop */
    if(data->verbose_level >=4)
      printf("Total of %d iterations ( %d calls to finite_difference() )\n",ITERATIONS*count,count);

    if((data->write_binary_field_imagesQ == TRUE || data->write_bitmap_field_imagesQ == TRUE) && data->dielectrics_in_bitmap==1 )
      write_fields_for_two_conductor_lines(inputfile_filename, *data, size);
    if(data->verbose_level == 0 && data->dielectrics_in_bitmap==1 )
      print_data_for_two_conductor_lines(*data, where_to_print_fp, inputfile_filename);

    if ( data->dielectrics_in_bitmap >1)
    {
      /* We know the capacitance and inductance for the air spaced line
      as we calculated it above. Howerver, whilst the inductance
      is independant of the dielectric, the capacitance is not, so this
      has to be recalculated, taking care not to alter the inductance
      at all */
      if(data->verbose_level >= 2)
        printf("Now taking into account the permittivities of the different dielectrics for 2 conductors.\n");

      dielectrics_to_consider_just_now=3; /* Any number > 1 */
      data->dielectrics_to_consider_just_now=2; /* Any number > 1 */

      capacitance=VERY_LARGE; /* Can be anything large */

      do /* Start a finite calculation */
      {
        capacitance_old=capacitance;
#ifdef ENABLE_POSIX_THREADS
      if (number_of_workers == 0)
         capacitance=finite_difference_single_threaded();
      else
        capacitance=finite_difference_multi_threaded();
#else  
      capacitance=finite_difference_single_threaded();
#endif
        data->C=capacitance;
        data->C_non_vacuum=capacitance;
        data->Zo=sqrt(data->L_vacuum/data->C_non_vacuum);  /* Standard formula for Zo */
        data->velocity=1.0/pow(data->L_vacuum*data->C_non_vacuum,0.5);
        data->velocity_factor=data->velocity/velocity_of_light_in_vacuum;
        data->relative_permittivity=sqrt(data->velocity_factor); /* ??? XXXXXX */
		data->Er=data->C/data->C_vacuum;
        if(data->verbose_level > 0 ) /* Only needed if intermediate results wanted. */
          print_data_for_two_conductor_lines(*data, where_to_print_fp, inputfile_filename);
      } while (fabs((capacitance_old-capacitance)/capacitance_old) > data->cutoff); /* end of FD loop */

      /* We must print the results now, but only bother if the verbose level was 
      not not incremented on the command line, otherwide there will be two duplicate
      lines */

      if (data->verbose_level == 0)
        print_data_for_two_conductor_lines(*data, where_to_print_fp, inputfile_filename);
      if(data->write_binary_field_imagesQ == TRUE || data->write_bitmap_field_imagesQ == TRUE)
        write_fields_for_two_conductor_lines(inputfile_filename, *data, size);
    }
  }
  else if (data->couplerQ==TRUE)
  {
    /* The properties of a couplers will be computed in 2 or 4 stages
    1) Compute the odd-mode impedance, assuming a vacuum dielectric, or
    if there is just one dielectric, that one.

    2) Compute the odd-mode impedance, taking into account the effect of
    multiple dielectrics, IF NECESSARY

    at this point, the negative voltages will be turned into positive ones. 

    3) Compute the even-mode impedance, assuming a vacuum dielectric, or
    if there is just one dielectric, that one.

    4) Compute the even-mode impedance, taking into account the effect of
    multiple dielectrics, IF NECESSARY  */

    /* Stage 1 - compute the odd mode impedance assuming single dielectric */
    data->display = Z_ODD_SINGLE_DIELECTRIC;
    dielectrics_to_consider_just_now=1;
    data->dielectrics_to_consider_just_now=1;

    capacitance=VERY_LARGE; /* Can be anything large */
    if(data->verbose_level >= 2)
      printf("Solving assuming a vacuum dielectric to compute the odd-mode impedance\n");

    do /* Start a finite difference calculation */
    {
      capacitance_old=capacitance;
#ifdef ENABLE_POSIX_THREADS
      if (number_of_workers == 0)
         capacitance=finite_difference_single_threaded();
      else
        capacitance=finite_difference_multi_threaded();
#else  
      capacitance=finite_difference_single_threaded();
#endif
      data->Codd_vacuum=capacitance;
      data->Codd=capacitance;
      data->Lodd_vacuum=MU_0*EPSILON_0/capacitance; /* Same as L in *ALL* cases */

      data->Zodd_vacuum=sqrt(data->Lodd_vacuum/data->Codd_vacuum);  /* Standard formaul for Zodd */

      if (data->dielectrics_in_bitmap == 1) /* Just get C by simple scaling of Er */
        data->Codd*=data->found_this_dielectric;  /* Scaled by the single dielectric constant */
      else
		data->Er=1.0;
      data->Zodd=sqrt(data->Lodd_vacuum/data->Codd);  /* Standard formula for Zo */
      velocity_of_light_in_vacuum=1.0/(sqrt(MU_0 * EPSILON_0)); /* around 3x10^8 m/s */
      /* FPE trapdata->velocity_odd=1.0/pow(data->L_vacuum*data->Codd,0.5); */
      data->velocity_odd=1.0/pow(data->Lodd_vacuum*data->Codd,0.5);
      data->velocity_factor_odd=data->velocity_odd/velocity_of_light_in_vacuum;
      data->relative_permittivity_odd=sqrt(data->velocity_factor_odd); /* ??? XXXXXX */
      data->Er_odd=data->Codd/data->Codd_vacuum;
      data->Zdiff=2.0*data->Zodd;
      /* Print text if uses wants it */
      if(data->verbose_level>=1)
        print_data_for_directional_couplers(*data, where_to_print_fp, inputfile_filename);
    } while (fabs((capacitance_old-capacitance)/capacitance_old) > data->cutoff); /* end of FD loop */

#ifdef ENABLE_MPI
	mpi_receive_updated_vij_strips();
#endif /* ENABLE_MPI */

    /* display bitpamps/binary files if this is the last odd-mode computation */
    if((data->write_binary_field_imagesQ == TRUE || data->write_bitmap_field_imagesQ == TRUE) && data->dielectrics_in_bitmap==1 )
      write_fields_for_directional_couplers(inputfile_filename, *data, size, ODD);

    /* Stage 2 - compute the odd-mode impedance taking into account other dielectrics IF NECESSARY */

    if ( data->dielectrics_in_bitmap >1)
    {
      if(data->verbose_level >= 2)
        printf("Now taking into account the permittivities of the different dielectrics to compute Zodd.\n");
      data->display = Z_ODD_SINGLE_DIELECTRIC;
      capacitance=VERY_LARGE; /* Can be anything large */

      dielectrics_to_consider_just_now=2;
      data->dielectrics_to_consider_just_now=2;

#ifdef ENABLE_MPI
	  mpi_send_current_data();
#endif /* ENABLE_MPI */

      do /* Start a finite calculation */
      {
        capacitance_old=capacitance;
#ifdef ENABLE_POSIX_THREADS
      if (number_of_workers == 0)
         capacitance=finite_difference_single_threaded();
      else
        capacitance=finite_difference_multi_threaded();
#else  
      capacitance=finite_difference_single_threaded();
#endif
        data->Codd=capacitance;
        data->Zodd=sqrt(data->Lodd_vacuum/data->Codd);  /* Standard formula for Zo */
        velocity_of_light_in_vacuum=1.0/(sqrt(MU_0 * EPSILON_0)); /* around 3x10^8 m/s */
        data->velocity_odd=1.0/pow(data->L_vacuum*data->C,0.5);
        data->velocity_factor_odd=data->velocity/velocity_of_light_in_vacuum;
        data->relative_permittivity_odd=sqrt(data->velocity_factor); /* ??? XXXXXX */
		data->Er_odd=data->Codd/data->Codd_vacuum;
		data->Zdiff=2.0*data->Zodd;
		if(data->verbose_level>=1)
          print_data_for_directional_couplers(*data, where_to_print_fp, inputfile_filename);
      } while (fabs((capacitance_old-capacitance)/capacitance_old) > data->cutoff); /* end of FD loop */

#ifdef ENABLE_MPI
	  mpi_receive_updated_vij_strips();
#endif /* ENABLE_MPI */

      if((data->write_binary_field_imagesQ == TRUE || data->write_bitmap_field_imagesQ == TRUE) && data->dielectrics_in_bitmap!=1 )
        write_fields_for_directional_couplers(inputfile_filename, *data, size, ODD);
    } /* end of stage 2 for couplers */

    /* Stage 3 - compute the even-mode impedance assuming single dielectric */

    /* Since we want the even mode impedance now, we swap all the -1V
    metallic conductors for +1V */

    swap_conductor_voltages();

    data->display = Z_EVEN_SINGLE_DIELECTRIC;
    dielectrics_to_consider_just_now=1;
    data->dielectrics_to_consider_just_now=1;
    if(data->verbose_level >= 2)
        printf("Now assuming a vacuum dielectric to compute Zeven\n");

    capacitance=VERY_LARGE; /* Can be anything large */

#ifdef ENABLE_MPI
	mpi_send_current_data();
#endif /* ENABLE_MPI */

    do /* Start a finite difference calculation */
    {
      capacitance_old=capacitance;
#ifdef ENABLE_POSIX_THREADS
      if (number_of_workers == 0)
         capacitance=finite_difference_single_threaded();
      else
        capacitance=finite_difference_multi_threaded();
#else  
      capacitance=finite_difference_single_threaded();
#endif

      data->Ceven_vacuum=capacitance;
      data->Ceven=capacitance;
      data->Leven_vacuum=MU_0*EPSILON_0/capacitance; /* Same as L in *ALL* cases */

      data->Zeven_vacuum=sqrt(data->Leven_vacuum/data->Ceven_vacuum);  /* Standard formaul for Zodd */

      if (data->dielectrics_in_bitmap == 1) /* Just get C by simple scaling of Er */
        data->Ceven*=data->found_this_dielectric;  /* Scaled by the single dielectric constant */
      else
		data->Er_even=1.0;
      data->Zeven=sqrt(data->Leven_vacuum/data->Ceven);  /* Standard formula for Zo */
      velocity_of_light_in_vacuum=1.0/(sqrt(MU_0 * EPSILON_0)); /* around 3x10^8 m/s */
      data->velocity_even=1.0/pow(data->Leven_vacuum*data->Ceven,0.5);
      data->velocity_factor_even=data->velocity_even/velocity_of_light_in_vacuum;
      data->relative_permittivity_even=sqrt(data->velocity_factor_even); /* ??? XXXXXX */
      data->Er_even=data->Ceven/data->Ceven_vacuum;
      data->Zcomm=data->Zeven/2.0;
      data->Zo=sqrt(data->Zodd * data->Zeven);
	  if(data->verbose_level>=1)
		print_data_for_directional_couplers(*data, where_to_print_fp, inputfile_filename);
      /* display bitpamps/binary files if this is the last even-mode computation */
    } while (fabs((capacitance_old-capacitance)/capacitance_old) > data->cutoff); /* end of FD loop */

    if((data->write_binary_field_imagesQ == TRUE || data->write_bitmap_field_imagesQ == TRUE) && data->dielectrics_in_bitmap==1)
      write_fields_for_directional_couplers(inputfile_filename, *data, size, EVEN);

    capacitance=VERY_LARGE; /* Can be anything large */
    /* Stage 4 - compute the even-mode impedance assuming multiple dielectrics IF NECESSARY */
    if ( data->dielectrics_in_bitmap >1)
    {
      dielectrics_to_consider_just_now=2;
      data->dielectrics_to_consider_just_now=2;
      if(data->verbose_level >= 2)
        printf("Now taking into account the permittivities of the different dielectrics to compute Zeven\n");

#ifdef ENABLE_MPI
	  mpi_send_current_data();
#endif /* ENABLE_MPI */

      do /* Start a finite calculation */
      {
        capacitance_old=capacitance;
#ifdef ENABLE_POSIX_THREADS
        if (number_of_workers == 0)
           capacitance=finite_difference_single_threaded();
        else
          capacitance=finite_difference_multi_threaded();
#else  
        capacitance=finite_difference_single_threaded();
#endif
        data->Ceven=capacitance;
        data->Zeven=sqrt(data->Leven_vacuum/data->Ceven);  /* Standard formula for Zo */
        velocity_of_light_in_vacuum=1.0/(sqrt(MU_0 * EPSILON_0)); /* around 3x10^8 m/s */
        data->velocity_even=1.0/pow(data->L_vacuum*data->C,0.5);
        data->velocity_factor_even=data->velocity/velocity_of_light_in_vacuum;
        data->relative_permittivity_even=sqrt(data->velocity_factor); /* ??? XXXXXX */
		data->Er_even=data->Ceven/data->Ceven_vacuum;
		data->Zdiff=2.0*data->Zodd;
        data->Zcomm=data->Zeven/2.0; 
		data->Zo=sqrt(data->Zeven*data->Zodd);
		if(data->verbose_level>=1)
          print_data_for_directional_couplers(*data, where_to_print_fp, inputfile_filename);
      } while (fabs((capacitance_old-capacitance)/capacitance_old) > data->cutoff); /* end of FD loop */

      if(data->write_binary_field_imagesQ == TRUE || data->write_bitmap_field_imagesQ == TRUE)
        write_fields_for_directional_couplers(inputfile_filename, *data, size, EVEN);
    } /* end of stage 4 */
    /* Print the results if the verbose level was 0 (no -v flag(s) ). */
    if (data->verbose_level == 0)
    {
      /* We need to print the data. The next function will only print if 
      the verbose_level is 1 or more, so I'll fix it at one. Then we print
      the final results and exit. */
      data->verbose_level=1;
      data->display = Z_EVEN_SINGLE_DIELECTRIC;
      print_data_for_directional_couplers(*data, where_to_print_fp, inputfile_filename);
    }
  } /* end of if couplers */
}
