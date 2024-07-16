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

#include "definitions.h"
#include "exit_codes.h"

#ifdef WINDOWS
#pragma hrdstop
#include <condefs.h>
#endif

int main(int argc, char **argv)
{
  FILE *fp;
  double *data, x;
  int q;
  int one=0, zero=0, minusone=0, other=0, length=0, i, reverse=0;
  int metal_er=0;
  while((q=get_options(argc,argv,"Cr")) != -1)
  switch (q)
  {
    case 'C':
      print_copyright("2002");
      exit_with_msg_and_exit_code("",OKAY);
    break;
    case 'r':
      reverse=1;
    break;
    case '?':
      usage_readbin();
  }
  if(argc-my_optind == 1)
  {
    fp=fopen(argv[my_optind],"rb");
    if (fp==NULL)
    {
      fprintf(stderr,"Can't open %s for reading\n",argv[my_optind]);
      exit_with_msg_and_exit_code("Can't open file for reading",CANT_OPEN_FILE_FOR_READING);
    }
    if (fseek(fp,0,SEEK_END) != 0)
      exit_with_msg_and_exit_code("failed to fseek in readbin.c #1", FSEEK_FAILURE);
    length=ftell(fp);
    printf("file length=%d bytes. There are %ld pixels\n", length, (long)
    length/sizeof(double));
    data=dvector(0,length);
    if( fseek(fp,0,SEEK_SET) != 0)
      exit_with_msg_and_exit_code("failed to fseek in readbin.c #2", FSEEK_FAILURE);

    if (fread(&(data[0]), (size_t) length, (size_t) 1,fp) != 1)
      exit_with_msg_and_exit_code("can't read all fo the file in readbin.c", CANT_READ_ALL_OF_FILE);
    for(i=0;i<length/sizeof(double);++i)
    {
       x=data[i];
       if(reverse==1)
	 byteswap_doubles(&x);
       if (fabs(x) <= 1e-15)
         zero++;
       else if ( x > 0.9999999999 && x < 1.000000000000001)
         one++;
       else if (x < -0.9999999999 && x > -1.000000000000001)
         minusone++;
       else if (x == METAL_ER)
	 metal_er++;
       else 
         other++;
    }
    free_dvector(data,0L,(long) length);
    fclose(fp);
  }
  else
    usage_readbin();
  return(OKAY);
}
