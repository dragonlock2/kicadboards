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

#ifdef HAVE_STDIO_H
#include <stdio.h>
#endif

#include "definitions.h"
#include "exit_codes.h"

/* names, colours and Ers are all arrays of 10. It would be better they were 
in a structure as they are all linked closely, but they are not and I
can't be bothered to change it */


extern int W, H;

/* This function can be used on any routines that writes .bmp files */

void write_bitmap_out(unsigned char *byte_aligned_image_data, FILE *image_data_fp,int sizeof_image, int W, int H)
{
   unsigned char *buff;

   struct Bitmap_File_Head_Struct Bitmap_File_Head;
   struct Bitmap_Head_Struct Bitmap_Head;

#ifdef DEBUG
   printf("sizeof_image = %d in write_bitmap_out\n", sizeof_image);
#endif

   buff=ustring(0,0x36);

   /* fprintf(stderr,"file size=%ld\n",temp_long); */

   Bitmap_File_Head.zzMagic[0]='B';
   Bitmap_File_Head.zzMagic[1]='M';
   Bitmap_File_Head.bfSize=sizeof_image+0x36;
   Bitmap_File_Head.zzHotX=0; 
   Bitmap_File_Head.zzHotY=0; 
   Bitmap_File_Head.bfOffs=54; 
   Bitmap_File_Head.biSize=0x28;


   Bitmap_Head.biWidth=W;
   Bitmap_Head.biHeight=H;
   Bitmap_Head.biPlanes=1;
   Bitmap_Head.biBitCnt=24;
   Bitmap_Head.biCompr=0;
   Bitmap_Head.biSizeIm=sizeof_image;
   Bitmap_Head.biXPels=W*10;  /* Why ??? XXX */
   Bitmap_Head.biYPels=H*10;  /* Why ??? XXX */
   Bitmap_Head.biClrUsed=0;
   Bitmap_Head.biClrImp=0;

   buff[0x00] = (unsigned char) (Bitmap_File_Head.zzMagic[0]);
   buff[0x01] = (unsigned char) (Bitmap_File_Head.zzMagic[1]);
/*
   buff[0x02] = Bitmap_File_Head.bfSize);
   buff[0x03] = Bitmap_File_Head.bfSize >> 8);
   buff[0x04] = Bitmap_File_Head.bfSize >> 16);
   buff[0x05] = Bitmap_File_Head.bfSize >> 24);
   */

   buff[0x02] =  (unsigned char) (Bitmap_File_Head.bfSize);
   buff[0x03] =  (unsigned char) (Bitmap_File_Head.bfSize >> 8);
   buff[0x04] =  (unsigned char) (Bitmap_File_Head.bfSize >> 16);
   buff[0x05] =  (unsigned char) (Bitmap_File_Head.bfSize >> 24);


   buff[0x06] = (unsigned char) (Bitmap_File_Head.zzHotX);
   buff[0x07] = (unsigned char) (Bitmap_File_Head.zzHotX >> 8);

   buff[0x08] = (unsigned char) (Bitmap_File_Head.zzHotY);
   buff[0x09] = (unsigned char) (Bitmap_File_Head.zzHotY >> 8);

   buff[0x0a] = (unsigned char) (Bitmap_File_Head.bfOffs);
   buff[0x0b] = (unsigned char) (Bitmap_File_Head.bfOffs>> 8);
   buff[0x0c] = (unsigned char) (Bitmap_File_Head.bfOffs>> 16);
   buff[0x0d] = (unsigned char) (Bitmap_File_Head.bfOffs>> 24);

   buff[0x0e] = (unsigned char) (Bitmap_File_Head.biSize);
   buff[0x0f] = (unsigned char) (Bitmap_File_Head.biSize>> 8);
   buff[0x10] = (unsigned char) (Bitmap_File_Head.biSize>> 16);
   buff[0x11] = (unsigned char) (Bitmap_File_Head.biSize>> 24);

   /* Write contents of Bitmap_Head_Struct */

   buff[0x12] = (unsigned char) (Bitmap_Head.biWidth);
   buff[0x13] = (unsigned char) (Bitmap_Head.biWidth>> 8);
   buff[0x14] = (unsigned char) (Bitmap_Head.biWidth>> 16);
   buff[0x15] = (unsigned char) (Bitmap_Head.biWidth>> 24);

   buff[0x16] = (unsigned char) (Bitmap_Head.biHeight);
   buff[0x17] = (unsigned char) (Bitmap_Head.biHeight>> 8);
   buff[0x18] = (unsigned char) (Bitmap_Head.biHeight>> 16);
   buff[0x19] = (unsigned char) (Bitmap_Head.biHeight>> 24);

   buff[0x1a] = (unsigned char) (Bitmap_Head.biPlanes);
   buff[0x1b] = (unsigned char) (Bitmap_Head.biPlanes>> 8);

   buff[0x1c] = (unsigned char) (Bitmap_Head.biBitCnt);
   buff[0x1d] = (unsigned char) (Bitmap_Head.biBitCnt>> 8);

   buff[0x1e] = (unsigned char) (Bitmap_Head.biCompr);
   buff[0x1f] = (unsigned char) (Bitmap_Head.biCompr>> 8);
   buff[0x20] = (unsigned char) (Bitmap_Head.biCompr>> 16);
   buff[0x21] = (unsigned char) (Bitmap_Head.biCompr>> 24);

   buff[0x22] = (unsigned char) (Bitmap_Head.biSizeIm);
   buff[0x23] = (unsigned char) (Bitmap_Head.biSizeIm>> 8);
   buff[0x24] = (unsigned char) (Bitmap_Head.biSizeIm>> 16);
   buff[0x25] = (unsigned char) (Bitmap_Head.biSizeIm>> 24);

   buff[0x26] = (unsigned char) (Bitmap_Head.biXPels);
   buff[0x27] = (unsigned char) (Bitmap_Head.biXPels>> 8);
   buff[0x28] = (unsigned char) (Bitmap_Head.biXPels>> 16);
   buff[0x29] = (unsigned char) (Bitmap_Head.biXPels>> 24);

   buff[0x2a] = (unsigned char) (Bitmap_Head.biYPels);
   buff[0x2b] = (unsigned char) (Bitmap_Head.biYPels>> 8);
   buff[0x2c] = (unsigned char) (Bitmap_Head.biYPels>> 16);
   buff[0x2d] = (unsigned char) (Bitmap_Head.biYPels>> 24);

   buff[0x2e] = (unsigned char) (Bitmap_Head.biClrUsed);
   buff[0x2f] = (unsigned char) (Bitmap_Head.biClrUsed>> 8);
   buff[0x30] = (unsigned char) (Bitmap_Head.biClrUsed>> 16);
   buff[0x31] = (unsigned char) (Bitmap_Head.biClrUsed>> 24);

   buff[0x32] = (unsigned char) (Bitmap_Head.biClrImp);
   buff[0x33] = (unsigned char) (Bitmap_Head.biClrImp>> 8);
   buff[0x34] = (unsigned char) (Bitmap_Head.biClrImp>> 16);
   buff[0x35] = (unsigned char) (Bitmap_Head.biClrImp>> 24);

   if( fwrite((void *) buff, 0x36, 1, image_data_fp) != 1)
    exit_with_msg_and_exit_code("Error#1: Failed to write bitmap file in write_bitmap_out.c",WRITE_FAILURE);


   /* Now the reader is written, finally write the image */
   if( fwrite(byte_aligned_image_data,(size_t) sizeof_image,1,image_data_fp) != 1)
    exit_with_msg_and_exit_code("Error#1: Failed to write bitmap file in write_bitmap_out.c",WRITE_FAILURE);
   if( fclose(image_data_fp) != 0)
     exit_with_msg_and_exit_code("failed to close file in write_bitmap_out.c",CANT_CLOSE_FILE);
}
