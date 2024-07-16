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

Some of these memory allocation routies are hacked versions of those
from the book 'Numerical Recipes in C' by Press et al. */

#include "config.h"

#ifdef HAVE_STDLIB_H
#include <stdlib.h>
#endif

#ifdef HAVE_SYS_TYPES
#include <sys/types.h>
#endif

#include "definitions.h"
#include "exit_codes.h"

#define NR_END 1

char *string(long nl,long nh)
{
  char *v;

  v=(char *)malloc((unsigned) (nh-nl+1));
  if (!v)
    exit_with_msg_and_exit_code("Memory allocation failure in string()",MEMORY_ALLOCATION_ERROR_IN_STRING);
  
  return v-nl;
}

unsigned char *ustring(long nl,long nh)
{
  unsigned char *v;

  v=(unsigned char *)malloc((size_t) (sizeof(unsigned char)* (nh-nl+1)));
  if (!v) {
    fprintf(stderr,"Can't allocate %ld bytes\n",nh-nl+1); 
    while(1)
    {
    } 
    exit_with_msg_and_exit_code("Memory allocation failure in ustring()",MEMORY_ALLOCATION_ERROR_IN_USTRING);
  }
  return v-nl;
}

void free_string(char *v, long nl, long nh)
/* free a string allocated with string() */
{
  if(nh <= nl)
    exit_with_msg_and_exit_code("nh <= nl in free_string()",SILLY_ARGUMENTS_IN_FREE_STRING);
  free((FREE_ARG) (v+nl));
}

void free_ustring(unsigned char *v, long nl, long nh)
/* free a string allocated with ustring() */
{
  if(nh <= nl)
    exit_with_msg_and_exit_code("nh <= nl in free_ustring()",SILLY_ARGUMENTS_IN_FREE_USTRING);
  free((FREE_ARG) (v+nl));
}


/* allocate a signed char matrix with subscript range m[nrl..nrh][ncl..nch] */
signed char **scmatrix(long nrl, long nrh, long ncl, long nch)
{
	long i, nrow=nrh-nrl+1,ncol=nch-ncl+1;
	signed char **m;
	/* allocate pointers to rows */
	m=(signed char **) malloc((size_t)((nrow+NR_END)*sizeof(signed char*)));
	if (!m) 
	  exit_with_msg_and_exit_code("Memory allocation failure #1 in scmatrix()",MEMORY_ALLOCATION_ERROR_IN_SCMATRIX);
	m += NR_END;
	m -= nrl;

	/* allocate rows and set pointers to them */
	m[nrl]=(signed char *) malloc((size_t)((nrow*ncol+NR_END)*sizeof(signed char)));
	if (!m[nrl]) 
	  exit_with_msg_and_exit_code("Memory allocation failure #2 in ucmatrix()",MEMORY_ALLOCATION_ERROR_IN_UCMATRIX);

	m[nrl] += NR_END;
	m[nrl] -= ncl;

	for(i=nrl+1;i<=nrh;i++) m[i]=m[i-1]+ncol;

	/* return pointer to array of pointers to rows */
	return m;
}


/* allocate a unsigned char matrix with subscript range m[nrl..nrh][ncl..nch] */
unsigned char **ucmatrix(long nrl, long nrh, long ncl, long nch)
{
	long i, nrow=nrh-nrl+1,ncol=nch-ncl+1;
	unsigned char **m;
	/* allocate pointers to rows */
	m=(unsigned char **) malloc((size_t)((nrow+NR_END)*sizeof(unsigned char*)));
	if (!m) 
	  exit_with_msg_and_exit_code("Memory allocation failure #1 in scmatrix()",MEMORY_ALLOCATION_ERROR_IN_UCMATRIX);
	m += NR_END;
	m -= nrl;

	/* allocate rows and set pointers to them */
	m[nrl]=(unsigned char *) malloc((size_t)((nrow*ncol+NR_END)*sizeof(unsigned char)));
	if (!m[nrl]) 
	  exit_with_msg_and_exit_code("Memory allocation failure #2 in ucmatrix()",MEMORY_ALLOCATION_ERROR_IN_UCMATRIX);

	m[nrl] += NR_END;
	m[nrl] -= ncl;

	for(i=nrl+1;i<=nrh;i++) m[i]=m[i-1]+ncol;

	/* return pointer to array of pointers to rows */
	return m;
}


/* free a signed char matrix allocated by cmatrix() */
void free_scmatrix(signed char **m, long nrl, long nrh, long ncl, long nch)
{
  if(nrh <= nrl)
      exit_with_msg_and_exit_code("nrh <= nrl in free_scmatrix()",SILLY_ARGUMENTS_IN_FREE_SCMATRIX);
  if(nch <= ncl)
      exit_with_msg_and_exit_code("nch <= ncl in free_scmatrix()",SILLY_ARGUMENTS_IN_FREE_SCMATRIX);
  free((FREE_ARG) (m[nrl]+ncl-NR_END));
  free((FREE_ARG) (m+nrl-NR_END));
}


/* free a unsigned char matrix allocated by ucmatrix() */
void free_ucmatrix(unsigned char **m, long nrl, long nrh, long ncl, long nch)
{
  if(nrh <= nrl)
      exit_with_msg_and_exit_code("nrh <= nrl in free_ucmatrix()",SILLY_ARGUMENTS_IN_FREE_UCMATRIX);
  if(nch <= ncl)
      exit_with_msg_and_exit_code("nch <= ncl in free_ucmatrix()",SILLY_ARGUMENTS_IN_FREE_UCMATRIX);
  free((FREE_ARG) (m[nrl]+ncl-NR_END));
  free((FREE_ARG) (m+nrl-NR_END));
}

double **dmatrix(long nrl, long nrh, long ncl, long nch)
/* allocate a double matrix with subscript range m[nrl..nrh][ncl..nch] */
{
	long i, nrow=nrh-nrl+1,ncol=nch-ncl+1;
	double **m;

	/* allocate pointers to rows */
	m=(double **) malloc((size_t)((nrow+NR_END)*sizeof(double*)));
	if (!m) 
	  exit_with_msg_and_exit_code("Memory allocation error #1 in dmatrix()",MEMORY_ALLOCATION_ERROR_IN_DMATRIX);
	m += NR_END;
	m -= nrl;

	/* allocate rows and set pointers to them */
	m[nrl]=(double *) malloc((size_t)((nrow*ncol+NR_END)*sizeof(double)));
	if (!m[nrl]) 
	  exit_with_msg_and_exit_code("Memory allocation error #2 in dmatrix()",MEMORY_ALLOCATION_ERROR_IN_DMATRIX);
	m[nrl] += NR_END;
	m[nrl] -= ncl;

	for(i=nrl+1;i<=nrh;i++) m[i]=m[i-1]+ncol;

	/* return pointer to array of pointers to rows */
	return m;
}


void free_dvector(double *v, long nl, long nh)
/* free a double vector allocated with dvector() */
{
  if(nh <= nl)
    exit_with_msg_and_exit_code("nh is <= nl in call to free_dvector",SILLY_ARGUMENTS_IN_FREE_DVECTOR);
  free((FREE_ARG) (v+nl-NR_END));
}

void free_dmatrix(double **m, long nrl, long nrh, long ncl, long nch)
/* free a double matrix allocated by dmatrix() */
{
  if(nrh <= nrl)
    exit_with_msg_and_exit_code("nhh is <= nl in call to free_dmatrix",SILLY_ARGUMENTS_IN_FREE_DMATRIX);
  if(nch <= ncl)
    exit_with_msg_and_exit_code("nch is <= nl in call to free_dmatrix",SILLY_ARGUMENTS_IN_FREE_DMATRIX);
  free((FREE_ARG) (m[nrl]+ncl-NR_END));
  free((FREE_ARG) (m+nrl-NR_END));
}

void free_cx(char **m, long nrl, long nrh, long ncl, long nch)
/* free a char matrix allocated by cmatrix() */
{
  if(nrh <= nrl)
    exit_with_msg_and_exit_code("nrh is <= nrl in call to free_charmatrix",SILLY_ARGUMENTS_IN_FREE_CMATRIX);
  if(nch <= ncl)
    exit_with_msg_and_exit_code("nch is <= ncl in call to free_charmatrix",SILLY_ARGUMENTS_IN_FREE_CMATRIX);
  free((FREE_ARG) (m[nrl]+ncl-NR_END));
  free((FREE_ARG) (m+nrl-NR_END));
}

double *dvector(long nl, long nh)
/* allocate a double vector with subscript range v[nl..nh] */
{
	double *v;
	v=(double *)malloc((size_t) ((nh-nl+1+NR_END)*sizeof(double)));
	if (!v)
	  exit_with_msg_and_exit_code("Memory allocation error in dvector()",MEMORY_ALLOCATION_ERROR_IN_DVECTOR);
	return v-nl+NR_END;
}

