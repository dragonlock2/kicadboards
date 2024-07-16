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

struct Bitmap_File_Head_Struct
{
  char   zzMagic[2];	/* 00 "BM" */
  long   bfSize;      /* 02 */
  short  zzHotX;	/* 06 */
  short  zzHotY;	/* 08 */
  long   bfOffs;      /* 0A */
  long   biSize;      /* 0E */
} Bitmap_File_Head;

struct Bitmap_Head_Struct
{
  long   biWidth;     /* 12 */
  long   biHeight;    /* 16 */
  short  biPlanes;    /* 1A */
  short  biBitCnt;    /* 1C */
  long   biCompr;     /* 1E */
  long   biSizeIm;    /* 22 */
  long   biXPels;     /* 26 */
  long   biYPels;     /* 2A */
  long   biClrUsed;   /* 2E */
  long   biClrImp;    /* 32 */
                        /* 36 */
} Bitmap_Head;
