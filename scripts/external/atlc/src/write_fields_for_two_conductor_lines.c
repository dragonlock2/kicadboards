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

#ifdef HAVE_STRING_H
#include <string.h>
#endif

#ifdef HAVE_STRINGS_H
#include <strings.h>
#endif

#ifdef HAVE_STDLIB_H
#include <stdlib.h>
#endif

#ifdef HAVE_STDIO_H
#include <stdio.h>
#endif

#include "exit_codes.h"

extern double **Vij;
extern double **Er;
extern unsigned char *bmp_buff;
extern int width, height, errno;
#ifdef WRITE_ODDITY_DATA
extern unsigned char **oddity;
#endif

/* Write the following files, assuming an input of example.bmp 
where example.bmp is a 2 conductor transmission lines. For
3 conductor transmission lines (couplers) the function


example.E.bmp   Grayscale Bitmap of |E-field|, normallised to 1,
but corrected for Gamma
example.Ex.bmp  Colour Bitmap of x-directed E-field, normallised to 1, 
but corrected for Gamma
example.Ey.bmp  Colour Bitmap of y-directed E-field, normallised to 1, 
but corrected for Gamma
example.V.bmp   Colour Bitmap of Voltage field, normallised to 1, but 
corrected for Gamma
eexample.U.bmp  Grayscale bitmap, with just the energy (U=CV^2).

example.Ex.bin  binary file, with just the x-directed E-field 
(in volts/pixel) as doubles 
example.Ey.bin  binary file, with just the y-directed E-field 
(in volts/pixel) as doubles 
example.E.bin   binary file, with just the E-field {sqrt(Ex^2+Ey^2)} 
(in volts/pixel) as doubles 
example.V.bin   binary file, with just the Voltage as doubles 
eexample.U.bin  binary file, with just the energy (U=CV^2).

*/

extern double image_fiddle_factor;


void write_fields_for_two_conductor_lines(char * filename, struct transmission_line_properties data, size_t size)
{
  FILE *Ex_bin_fp=NULL, *Ey_bin_fp=NULL;
  FILE *E_bin_fp=NULL, *V_bin_fp, *U_bin_fp=NULL;
  FILE *Ex_bmp_fp=NULL, *Ey_bmp_fp=NULL;
  FILE *E_bmp_fp=NULL, *V_bmp_fp=NULL, *U_bmp_fp=NULL;
#ifdef WRITE_ODDITY_DATA
  FILE *oddity_bmp_fp=NULL;
  double odd;
#endif
  unsigned char r, g, b;
  FILE *permittivity_bin_fp=NULL, *permittivity_bmp_fp=NULL;
  struct max_values maximum_values;
  int offset=-3, w, h;
  double V, E, Ex, Ey, U;

  unsigned char *image_data_Ex=NULL; 
  unsigned char *image_data_Ey=NULL;
  unsigned char *image_data_E=NULL;
  unsigned char *image_data_U=NULL; 
  unsigned char *image_data_V=NULL;
  unsigned char *image_data_Er=NULL;
#ifdef WRITE_ODDITY_DATA
  unsigned char *image_data_oddity=NULL;
#endif 


  if(data.write_binary_field_imagesQ==TRUE)
  {
    Ex_bin_fp=get_file_pointer_with_right_filename(filename,".Ex.bin");
    Ey_bin_fp=get_file_pointer_with_right_filename(filename,".Ey.bin");
    E_bin_fp=get_file_pointer_with_right_filename(filename,".E.bin");
    V_bin_fp=get_file_pointer_with_right_filename(filename,".V.bin");
    U_bin_fp=get_file_pointer_with_right_filename(filename,".U.bin");
    permittivity_bin_fp=get_file_pointer_with_right_filename(filename,".Er.bin");
    for(h=height-1;h>=0;h--)
    {
      for(w=0;w<width;++w)
      {
	V=Vij[w][h];
        Ex=find_Ex(w,h);
        Ey=find_Ey(w,h);
        E=find_E(w,h); 
        U=find_energy_per_metre(w,h);
        if( fwrite((void *) &Ex,sizeof(double), 1, Ex_bin_fp) != 1)
          exit_with_msg_and_exit_code("Error#1: Failed to write binary file in write_fields_for_two_conductor_lines.c",WRITE_FAILURE);

        if( fwrite((void *) &Ey,sizeof(double), 1, Ey_bin_fp) != 1)
          exit_with_msg_and_exit_code("Error#2: Failed to write binary file in write_fields_for_two_conductor_lines.c",WRITE_FAILURE);

        if( fwrite((void *) &E,sizeof(double), 1, E_bin_fp) != 1)
          exit_with_msg_and_exit_code("Error#3: Failed to write binary file in write_fields_for_two_conductor_lines.c",WRITE_FAILURE);

        if( fwrite((void *) &V,sizeof(double), 1, V_bin_fp) != 1)
          exit_with_msg_and_exit_code("Error#4: Failed to write binary file in write_fields_for_two_conductor_lines.c",WRITE_FAILURE);

        if( fwrite((void *) &U,sizeof(double), 1, U_bin_fp) != 1)
          exit_with_msg_and_exit_code("Error#5: Failed to write binary file in write_fields_for_two_conductor_lines.c",WRITE_FAILURE);

        if( fwrite((void *) &Er[w][h],sizeof(double), 1, permittivity_bin_fp) != 1)
          exit_with_msg_and_exit_code("Error#6: Failed to write binary file in write_fields_for_two_conductor_lines.c",WRITE_FAILURE);
      }
    }
  } /* end of writing binary files for 2 conductor lines */

  if(data.write_bitmap_field_imagesQ==TRUE)
  {
    find_maximum_values(&(maximum_values), ZERO_ELEMENTS_FIRST); /* sets stucture maximum_values */

    /* Allocate ram to store the bitmaps before they are written to disk */
    image_data_Ex=ustring(0L,(long) size);
    image_data_Ey=ustring(0L,(long) size);
    image_data_E=ustring(0L,(long) size);
    image_data_V=ustring(0L,(long) size);
    image_data_Er=ustring(0L,(long) size);
    image_data_U=ustring(0L,(long) size);
#ifdef WRITE_ODDITY_DATA
    image_data_oddity=ustring(0L,(long) size);
#endif

    Ex_bmp_fp=get_file_pointer_with_right_filename(filename,".Ex.bmp");
    Ey_bmp_fp=get_file_pointer_with_right_filename(filename,".Ey.bmp");
    E_bmp_fp=get_file_pointer_with_right_filename(filename,".E.bmp");
    V_bmp_fp=get_file_pointer_with_right_filename(filename,".V.bmp");
    U_bmp_fp=get_file_pointer_with_right_filename(filename,".U.bmp");
    permittivity_bmp_fp=get_file_pointer_with_right_filename(filename,".Er.bmp");
#ifdef WRITE_ODDITY_DATA
    oddity_bmp_fp=get_file_pointer_with_right_filename(filename,".oddity.bmp");
#endif

    if( fwrite(bmp_buff,0x36,1,Ex_bmp_fp) != 1)
      exit_with_msg_and_exit_code("failed to write file with the pointer Ex_bmp_fp in write_fields_for_two_conductor_lines.c",WRITE_FAILURE);
    if( fwrite(bmp_buff,0x36,1,Ey_bmp_fp) != 1)
      exit_with_msg_and_exit_code("failed to write file with the pointer Ey_bmp_fp in write_fields_for_two_conductor_lines.c",WRITE_FAILURE);
    if( fwrite(bmp_buff,0x36,1,E_bmp_fp) != 1)
      exit_with_msg_and_exit_code("failed to write file with the pointer E_bmp_fp in write_fields_for_two_conductor_lines.c",WRITE_FAILURE);
    if( fwrite(bmp_buff,0x36,1,V_bmp_fp) != 1)
      exit_with_msg_and_exit_code("failed to write file with the pointer V_bmp_fp in write_fields_for_two_conductor_lines.c",WRITE_FAILURE);
    if( fwrite(bmp_buff,0x36,1,U_bmp_fp) != 1)
      exit_with_msg_and_exit_code("failed to write file with the pointer U_bmp_fp in write_fields_for_two_conductor_lines.c",WRITE_FAILURE);
    if( fwrite(bmp_buff,0x36,1,permittivity_bmp_fp) != 1)
      exit_with_msg_and_exit_code("failed to write file with the pointer permittivity_bmp_fp in write_fields_for_two_conductor_lines.c",WRITE_FAILURE);

#ifdef WRITE_ODDITY_DATA
    if( fwrite(bmp_buff,0x36,1,oddity_bmp_fp) != 1)
      exit_with_msg_and_exit_code("failed to write file with the pointer oddity_bmp_fp in write_fields_for_two_conductor_lines.c",WRITE_FAILURE);
#endif 

    offset=-3;
    for(h=height-1;h>=0;h--)
    {
      for(w=0;w<width;++w)
      {
	offset+=3;
	if((w==0) && (offset%4!=0) && (h!=0)) 
	  offset+=(4-offset%4);
        Ex=find_Ex(w,h);
        Ey=find_Ey(w,h);
        E=find_E(w,h); 
        U=find_energy_per_metre(w,h);
        calculate_colour_data(Ex, maximum_values.Ex_or_Ey_max, w, h, offset,image_data_Ex, COLOUR,&r,&g,&b,IMAGE_FIDDLE_FACTOR);
        calculate_colour_data(Ey, maximum_values.Ex_or_Ey_max, w, h, offset,image_data_Ey, COLOUR,&r,&g,&b,IMAGE_FIDDLE_FACTOR);
        calculate_colour_data(E, maximum_values.E_max, w, h, offset,image_data_E, MONOCHROME,&r,&g,&b,IMAGE_FIDDLE_FACTOR);
        calculate_colour_data(U, maximum_values.U_max, w, h, offset,image_data_U, MONOCHROME,&r,&g,&b,IMAGE_FIDDLE_FACTOR);
        calculate_colour_data(Vij[w][h], maximum_values.V_max, w, h, offset,image_data_V, COLOUR,&r,&g,&b,IMAGE_FIDDLE_FACTOR);
        calculate_colour_data(Er[w][h], MAX_ER, w, h, offset,image_data_Er, MIXED,&r,&g,&b,IMAGE_FIDDLE_FACTOR);
#ifdef WRITE_ODDITY_DATA
	odd=(double) oddity[w][h];
        calculate_colour_data(odd, 255 , w, h, offset,image_data_oddity, MONOCHROME,&r,&g,&b,1.0);
#endif

      }
    }

    /* if( fwrite((void *) &(image_data_Ex[0]),size, 1, Ex_bmp_fp) != 1) */
    if( fwrite((void *) image_data_Ex,size, 1, Ex_bmp_fp) != 1)
      exit_with_msg_and_exit_code("Error#7: Failed to write bitmap file in write_fields_for_two_conductor_lines.c",WRITE_FAILURE);
    if( fclose(Ex_bmp_fp) != 0)
      exit_with_msg_and_exit_code("Error#8: Unable to close file in write_fields_for_two_conductor_lines.c",CANT_CLOSE_FILE);

    /* if( fwrite((void *) &(image_data_Ey[0]),size, 1, Ey_bmp_fp) != 1) */
    if( fwrite((void *) image_data_Ey,size, 1, Ey_bmp_fp) != 1)
      exit_with_msg_and_exit_code("Error#9: Failed to write bitmap file in write_fields_for_two_conductor_lines.c",WRITE_FAILURE);
    if( fclose(Ey_bmp_fp) != 0)
      exit_with_msg_and_exit_code("Error#10: Unable to close file in write_fields_for_two_conductor_lines.c",CANT_CLOSE_FILE);

    if( fwrite((void *) &(image_data_E[0]),size, 1, E_bmp_fp) != 1)
      exit_with_msg_and_exit_code("Error#11: Failed to write bitmap file in write_fields_for_two_conductor_lines.c",WRITE_FAILURE);
    if( fclose(E_bmp_fp) != 0)
      exit_with_msg_and_exit_code("Error#12: Unable to close file in write_fields_for_two_conductor_lines.c",CANT_CLOSE_FILE);

    if( fwrite((void *) &(image_data_U[0]),size, 1, U_bmp_fp) != 1)
      exit_with_msg_and_exit_code("Error#13: Failed to write bitmap file in write_fields_for_two_conductor_lines.c",WRITE_FAILURE);
    if( fclose(U_bmp_fp) != 0)
      exit_with_msg_and_exit_code("Error#14: Unable to close file in write_fields_for_two_conductor_lines.c",CANT_CLOSE_FILE);

    if( fwrite((void *) &(image_data_V[0]),size, 1, V_bmp_fp) != 1)
      exit_with_msg_and_exit_code("Error#15: Failed to write bitmap file in write_fields_for_two_conductor_lines.c",WRITE_FAILURE);
    if( fclose(V_bmp_fp) != 0)
      exit_with_msg_and_exit_code("Error#16: Unable to close file in write_fields_for_two_conductor_lines.c",CANT_CLOSE_FILE);

    if( fwrite((void *) &(image_data_Er[0]),size, 1, permittivity_bmp_fp) != 1)
      exit_with_msg_and_exit_code("Error#17: Failed to write bitmap file in write_fields_for_two_conductor_lines.c",WRITE_FAILURE);
    if( fclose(permittivity_bmp_fp) != 0)
      exit_with_msg_and_exit_code("Error#18: Unable to close file in write_fields_for_two_conductor_lines.c",CANT_CLOSE_FILE);

#ifdef WRITE_ODDITY_DATA
    if( fwrite((void *) &(image_data_oddity[0]),size, 1, oddity_bmp_fp) != 1)
      exit_with_msg_and_exit_code("Error#19: Failed to write bitmap file in write_fields_for_two_conductor_lines.c",WRITE_FAILURE);
    if( fclose(oddity_bmp_fp) != 0)
      exit_with_msg_and_exit_code("Error#20: Unable to close file in write_fields_for_two_conductor_lines.c",CANT_CLOSE_FILE);
#endif

    free_ustring(image_data_Ex,0L,(long)size);
    free_ustring(image_data_Ey,0L,(long)size);
    free_ustring(image_data_E,0L,(long)size);
    free_ustring(image_data_V,0L,(long)size);
    free_ustring(image_data_U,0L,(long)size);
    free_ustring(image_data_Er,0L,(long)size);
#ifdef WRITE_ODDITY_DATA
    free_ustring(image_data_oddity,0L,(long)size);
#endif
  }
}
