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

#ifdef HAVE_STRING_H
#include <string.h>
#endif

#ifdef HAVE_STRINGS_H
#include <strings.h>
#endif

#ifdef HAVE_STDLIB_H
#include <stdlib.h>
#endif

#include "definitions.h"
#include "exit_codes.h"

unsigned char *bmp_buff;

/* We make the bitmap header public, as we write it back 
later, when saving bmp files. It saves a lot of hassle,
just writing what we read back, rather than correctly 
calculating all the data in the header correctly */

#define BITMAP_HEADER_SIZE 0x36 /* 54 */

void read_bitmap_file_headers(char *filename, int *offset, size_t *size, int *width, int *height)
{
   FILE *fp;

   struct Bitmap_File_Head_Struct Bitmap_File_Head;
   struct Bitmap_Head_Struct Bitmap_Head;
   int ColormapSize, Maps;
   int length_of_file; /* Appently Photoshop versions < 7.01
		       don't write this into Bitmap_Head.biSizeIm
		       so it causes a problem. So we will work out
		       the length by seeking to the end of the file
		       and finding the position of the file 
		       pointer */

   bmp_buff=ustring(0,BITMAP_HEADER_SIZE);
   if(strcmp(filename,"-")==0)
   {
      fp=stdin;   
   }
   else  
      fp=fopen(filename,"rb");

   if(fp==NULL)
   {
      fprintf(stderr,"cannot open %s\n", filename);
      exit_with_msg_and_exit_code("",CANT_OPEN_FILE_FOR_READING);
   }

   /* deternine the length of the file, as its not always 
   written into the bitmap. I thought it needed to be, but
   apparently it does not and photoshop versions < 7.01 
   don't do it. */
   if( fseek(fp, 0, SEEK_END)  == -1)
   {
     fprintf(stderr," Can't seek to the end of the file in read_bitmap_file_headers.c\n");
     exit(FSEEK_FAILURE);
   }
   if( (length_of_file=ftell(fp))  == -1)
     exit_with_msg_and_exit_code("Can't find length of file in read_bitmap_file_headers.c",FTELL_FAILURE);

   if( (fseek(fp, 0, SEEK_SET) ) == -1)
   {
     fprintf(stderr," Can't seek to the beggining of the file in read_bitmap_file_headers.c\n");
     exit(FSEEK_FAILURE);
   }
   /* Read the .bmp file header into a bmp_buff */
   if (!(fread(bmp_buff, 1,BITMAP_HEADER_SIZE,fp))||(strncmp((char *) bmp_buff,"BM",2)))
   {
      fprintf(stderr,"%s is not a valid BMP file\n", filename);
      exit_with_msg_and_exit_code("",NOT_A_VALID_BITMAP_FILE);
   }

/* On most machines, sizeof(short)==2 and sizeof(int)==4. This is so no matter
if the machine is 32 or 64 bis. An exception is the Cray Y-MP, which has  
sizeof(short)=8
sizeof(int)=8
sizeof(long)=8.

In this case, it is much more difficult to write the header for the bitmap. But in
the aid of portability, this is done. So these is a section of code that will work
even if sizeof(short)=8 and sizeof(int)=8. See below for that. */


   /* Read the bmp_buff into the two structures we want */

   Bitmap_File_Head.zzMagic[0x0] = bmp_buff[0];
   Bitmap_File_Head.zzMagic[0x1] = bmp_buff[1];
   Bitmap_File_Head.bfSize = bmp_buff[0x2] + ((bmp_buff[3] + ((bmp_buff[4] + (bmp_buff[5] << 8)) << 8)) <<8);
   Bitmap_File_Head.zzHotX = bmp_buff[0x6] + (bmp_buff[7] << 8);
   Bitmap_File_Head.zzHotY = bmp_buff[0x8] + (bmp_buff[0x09] << 8);
   Bitmap_File_Head.bfOffs = bmp_buff[0x0a] + ((bmp_buff[0xb] + ((bmp_buff[0xc] + (bmp_buff[0x0d] << 8)) << 8)) <<8);
   Bitmap_File_Head.biSize = bmp_buff[0x0E] + ((bmp_buff[0x0f] + ((bmp_buff[0x10] + (bmp_buff[0x11] << 8)) << 8)) <<8);
   Bitmap_Head.biWidth=bmp_buff[0x12] + ((bmp_buff[0x13] + ((bmp_buff[0x14] + (bmp_buff[0x15] << 8)) << 8)) <<8);
   Bitmap_Head.biHeight=bmp_buff[0x16] + ((bmp_buff[0x17] + ((bmp_buff[0x18] + (bmp_buff[0x19] << 8)) << 8)) <<8);
   Bitmap_Head.biPlanes = bmp_buff[0x1A] + (bmp_buff[0x1b] << 8);
   Bitmap_Head.biBitCnt = bmp_buff[0x1C] + (bmp_buff[0x1d] << 8);
   Bitmap_Head.biCompr= bmp_buff[0x1E] + ((bmp_buff[0x1f] + ((bmp_buff[0x20] + (bmp_buff[0x21] << 8)) << 8)) <<8);
   Bitmap_Head.biSizeIm=bmp_buff[0x22] + ((bmp_buff[0x23] + ((bmp_buff[0x24] + (bmp_buff[0x25] << 8)) << 8)) <<8);
   /* I thought the length of the image was always stored in Bitmap_Head.biSizeIm, but 
   this appears not to be so. Hence it is now calculated from the length of the file
   */ 
   Bitmap_Head.biSizeIm=length_of_file-BITMAP_HEADER_SIZE;
   Bitmap_Head.biXPels  = bmp_buff[0x26] + ((bmp_buff[0x27] + ((bmp_buff[0x28] + (bmp_buff[0x29] << 8)) << 8)) <<8);
   Bitmap_Head.biYPels= bmp_buff[0x2A] + ((bmp_buff[0x2b] + ((bmp_buff[0x2c] + (bmp_buff[0x2d] << 8)) << 8)) <<8);
   Bitmap_Head.biClrUsed = bmp_buff[0x2E] + ((bmp_buff[0x2f] + ((bmp_buff[0x30] + (bmp_buff[0x31] << 8)) << 8)) <<8);
   Bitmap_Head.biClrImp  = bmp_buff[0x32] + ((bmp_buff[0x33] + ((bmp_buff[0x34] + (bmp_buff[0x35] << 8)) << 8)) <<8);

   Maps=4;
   if(Bitmap_Head.biBitCnt!=24)
   {
      fprintf(stderr,"Sorry, the .bmp bitmap must have 24 bits per colour,\n");
      fprintf(stderr,"but it has %d bits. Resave the \n",Bitmap_Head.biBitCnt);
      fprintf(stderr,"image using 24-bit colour\n");
      exit_with_msg_and_exit_code("mage using 24-bit colour",BITMAP_NOT_24_BIT);
   }
   ColormapSize = (Bitmap_File_Head.bfOffs - Bitmap_File_Head.biSize - 14) / Maps;

   if ((Bitmap_Head.biClrUsed == 0) && (Bitmap_Head.biBitCnt <= 8))
	   Bitmap_Head.biClrUsed = ColormapSize;

   /* Sanity checks */

   if (Bitmap_Head.biHeight == 0 || Bitmap_Head.biWidth == 0) 
   {
      fprintf(stderr,"error reading BMP file header of %s - width or height is zero\n",filename);
      exit_with_msg_and_exit_code("",WIDTH_OR_HEIGHT_ZERO_IN_BITMAP);
   } 
   if (Bitmap_Head.biPlanes != 1) 
   {
      fprintf(stderr,"error reading BMP file header of %s - bitplanes not equal to 1\n",filename);
      exit_with_msg_and_exit_code("",BITPLANES_NOT_1_IN_BITMAP);
   }
   if (ColormapSize > 256 || Bitmap_Head.biClrUsed > 256)
   {
      fprintf(stderr,"error reading BMP file header of %s - colourmap size error\n",filename);
      exit_with_msg_and_exit_code("",COLOURMAP_GREATER_THAN_256);
   }
   /* Windows and OS/2 declare filler so that rows are a multiple of
      word length (32 bits == 4 bytes)
   */

   fclose(fp);
   *width=Bitmap_Head.biWidth;
   *height=Bitmap_Head.biHeight;
   *offset=Bitmap_File_Head.bfOffs;
   *size=Bitmap_Head.biSizeIm;
   if( *size < 3 * (*width) * (*height) )
   {
     fprintf(stderr,"Internal error in read_bitmap_file_headers.c\n"); 
     exit(1);
   }
}
