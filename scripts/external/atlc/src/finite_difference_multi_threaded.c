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

#define SLOW

#ifndef ENABLE_POSIX_THREADS 

/* If we are not comiling for multi-threaded use, a function
is defined, but it is not used. This keeps the linker happy */

double finite_difference_multi_threaded()
{
  return(0.0);
}
#endif


#ifdef ENABLE_POSIX_THREADS 

#ifdef HAVE_SYS_TYPES_H
#include <sys/types.h>
#endif

#ifdef HAVE_STDLIB_H
#include <stdlib.h>
#endif

#include <pthread.h>

#ifdef HAVE_SCHED_H
#include <sched.h>
#endif

#ifdef HAVE_STRING_H
#include <string.h>
#endif

#include "definitions.h"
#include "exit_codes.h"

extern int coupler;
extern int width, height;
extern double **Vij, **Er;
extern signed char **oddity;
extern int number_of_workers; 


/* The algorithm for this is based on one in the book 'Foundations of Multithraded, 
Parallel and Distributed Programming' by G. A. Andrews, (2000). Especially 
chapter 11, Fig 11.6, "Red/Black Gauss-Seidel using shared vairables'. 

Basically the array is a considered a chess board. Since we only use in the computation the
values above, below, to the left and the right of the current pixel, these will all be the
same colour on the chess board (black or white). So we compute all the white squares, which
can all be done in parallel, since they don't depend on each other. Once the white squares
are done, the black ones can be done. Again, these don't depend on the white squares, but
only the black ones. So the algorithm does

1) Covers the array with a large chess board with black and white squares. 


B W B W B W B W B W B W B W B W B W B W B W B W B W B W
W B W B W B W B W B W B W B W B W B W B W B W B W B W B
B W B W B W B W B W B W B W B W B W B W B W B W B W B W 
W B W B W B W B W B W B W B W B W B W B W B W B W B W B 
B W B W B W B W B W B W B W B W B W B W B W B W B W B W 
W B W B W B W B W B W B W B W B W B W B W B W B W B W B 
B W B W B W B W B W B W B W B W B W B W B W B W B W B W 
W B W B W B W B W B W B W B W B W B W B W B W B W B W B 
B W B W B W B W B W B W B W B W B W B W B W B W B W B W 
W B W B W B W B W B W B W B W B W B W B W B W B W B W B
B W B W B W B W B W B W B W B W B W B W B W B W B W B W 
W B W B W B W B W B W B W B W B W B W B W B W B W B W B


2) Split the array into a number of columns, one for each CPU.

B W B W B W B   W B W B W B W   B W B W B W B   W B W B W B W
W B W B W B W   B W B W B W B   W B W B W B W   B W B W B W B
B W B W B W B   W B W B W B W   B W B W B W B   W B W B W B W 
W B W B W B W   B W B W B W B   W B W B W B W   B W B W B W B 
B W B W B W B   W B W B W B W   B W B W B W B   W B W B W B W 
W B W B W B W   B W B W B W B   W B W B W B W   B W B W B W B 
B W B W B W B   W B W B W B W   B W B W B W B   W B W B W B W 
W B W B W B W   B W B W B W B   W B W B W B W   B W B W B W B 
B W B W B W B   W B W B W B W   B W B W B W B   W B W B W B W 
W B W B W B W   B W B W B W B   W B W B W B W   B W B W B W B
B W B W B W B   W B W B W B W   B W B W B W B   W B W B W B W 
W B W B W B W   B W B W B W B   W B W B W B W   B W B W B W B

3) Do all columns in parallel on the black squares. 

B   B   B   B     B   B   B     B   B   B   B     B   B   B  
  B   B   B     B   B   B   B     B   B   B     B   B   B   B
B   B   B   B     B   B   B     B   B   B   B     B   B   B   
  B   B   B     B   B   B   B     B   B   B     B   B   B   B 
B   B   B   B     B   B   B     B   B   B   B     B   B   B   
  B   B   B     B   B   B   B     B   B   B     B   B   B   B 
B   B   B   B     B   B   B     B   B   B   B     B   B   B   
  B   B   B     B   B   B   B     B   B   B     B   B   B   B 
B   B   B   B     B   B   B     B   B   B   B     B   B   B   
  B   B   B     B   B   B   B     B   B   B     B   B   B   B
B   B   B   B     B   B   B     B   B   B   B     B   B   B   
  B   B   B     B   B   B   B     B   B   B     B   B   B   B

Thread 0          Thread 1        Thread 2         Thread 3

4) Wait until all the black squares are done.

5) Compute all the white squares in parallel. 

  W   W   W     W   W   W   W     W   W   W     W   W   W   W
W   W   W   W     W   W   W     W   W   W   W     W   W   W  
  W   W   W     W   W   W   W     W   W   W     W   W   W   W 
W   W   W   W     W   W   W     W   W   W   W     W   W   W   
  W   W   W     W   W   W   W     W   W   W     W   W   W   W 
W   W   W   W     W   W   W     W   W   W   W     W   W   W   
  W   W   W     W   W   W   W     W   W   W     W   W   W   W 
W   W   W   W     W   W   W     W   W   W   W     W   W   W   
  W   W   W     W   W   W   W     W   W   W     W   W   W   W 
W   W   W   W     W   W   W     W   W   W   W     W   W   W  
  W   W   W     W   W   W   W     W   W   W     W   W   W   W 
W   W   W   W     W   W   W     W   W   W   W     W   W   W  
Thread 0          Thread 1        Thread 2         Thread 3


6) Repeat a large number (typically 100) times. 

7) Check for convergence. 

8) Stop if the solution has converged. 
*/

extern double r;

pthread_mutex_t barrier;  /* mutex semaphore for the barrier */
pthread_cond_t go;        /* condition variable for leaving */
int numArrived = 0;       /* count of the number who have arrived */

#define BARRIER2 

#ifdef BARRIER1
void Barrier() {
#ifndef DEBUG
  pthread_mutex_lock(&barrier);
#else
  if( pthread_mutex_lock(&barrier) != 0 )
    exit_with_msg_and_exit_code("pthread_mutex_lock failed",PTHREAD_MUTEX_LOCK_FAILED);
#endif
  
  numArrived++;
  if (numArrived == number_of_workers) {
    numArrived = 0;
    pthread_cond_broadcast(&go);
  } else
    pthread_cond_wait(&go, &barrier);
#ifndef DEBUG
  pthread_mutex_unlock(&barrier);
#else
  if( pthread_mutex_unlock(&barrier) != 0 )
    exit_with_msg_and_exit_code("pthread_mutex_unlock failed",PTHREAD_MUTEX_UNLOCK_FAILED);
#endif
}
#endif

#ifdef BARRIER2
int numArrived2[2] = {0, 0};
int barrierNdx = 0;

void Barrier() {
  int localNdx;
#ifndef DEBUG
  pthread_mutex_lock(&barrier);
#else
  if( pthread_mutex_lock(&barrier) != 0 )
    exit_with_msg_and_exit_code("pthread_mutex_lock failed in finite_difference_multi_threaded.c",PTHREAD_MUTEX_LOCK_FAILED);
#endif
  
  numArrived2[barrierNdx]++;
  if (numArrived2[barrierNdx] == number_of_workers) {
    barrierNdx = (barrierNdx + 1)%2;  /* toggle */
    numArrived2[barrierNdx] = 0; /* reset other count */

#ifndef DEBUG
    pthread_cond_broadcast(&go);
#else
    if( pthread_cond_broadcast(&go) != 0)
      exit_with_msg_and_exit_code("pthread_cond_broadcast failed in finite_difference_multi_threaded.c",PTHREAD_COND_BROADCAST_FAILED);
#endif
  }
  else
  {
    localNdx = barrierNdx; /* wait on "current" numArrived. */
    while (numArrived2[localNdx] != number_of_workers)
#ifndef DEBUG
       pthread_cond_wait(&go, &barrier);
#else
       if( pthread_cond_wait(&go, &barrier) != 0)
         exit_with_msg_and_exit_code("pthread_cond_wait failed finite_difference_multi_threaded.c",PTHREAD_COND_WAIT_FAILED);
#endif
  } 
#ifndef DEBUG
  pthread_mutex_unlock(&barrier);
#else
  if( pthread_mutex_unlock(&barrier) != 0 )
    exit_with_msg_and_exit_code("pthread_mutex_unlock failed finite_difference_multi_threaded.c",PTHREAD_MUTEX_UNLOCK_FAILED);
#endif
}
#endif



/* Each Worker computes values in one strip of the grids.
   The main worker loop does two computations to avoid copying from
   one grid to the other.  */

void *worker(void *arg) {
  int myid = (int) arg;
  double r_over_4,a,b,c,d,e,f,g,h;
  double one_minus_r;
  int i, j, iters, jstart;
  int firstcol, lastcol;
  int strip_width=width/number_of_workers;

  firstcol = myid*strip_width+1;
  lastcol = firstcol + strip_width - 1;
  r_over_4=r/4.0;
  one_minus_r=1-r;
  if(myid == number_of_workers -1) 
    lastcol=width-2;
  Barrier();
  for (iters = 1; iters <= ITERATIONS; iters++) 
  {
    for(i= firstcol ; i <= lastcol; ++i){
      if(i%2 ==1 )
	jstart=1;
      else
	jstart=2;
      for(j=jstart ; j < height-1 ; j+=2){
        if(oddity[i][j] == ORDINARY_INTERIOR_POINT) /* Same dielectric all around */
          Vij[i][j]=r_over_4*(Vij[i][j+1]+Vij[i+1][j]+Vij[i][j-1]+Vij[i-1][j])+one_minus_r*Vij[i][j];
        else if(oddity[i][j] > ORDINARY_INTERIOR_POINT) /* only update dielectrics, not conductors */
        {
          a=(Er[i][j] * Er[i][j-1] * Vij[i][j-1])/(Er[i][j] + Er[i][j-1]);
          b=(Er[i][j] * Er[i][j+1] * Vij[i][j+1])/(Er[i][j] + Er[i][j+1]);
          c=(Er[i][j] * Er[i-1][j] * Vij[i-1][j])/(Er[i][j] + Er[i-1][j]);
          d=(Er[i][j] * Er[i+1][j] * Vij[i+1][j])/(Er[i][j] + Er[i+1][j]);
    
          e=(Er[i][j] * Er[i][j-1])/(Er[i][j]+Er[i][j-1]);
          f=(Er[i][j] * Er[i][j+1])/(Er[i][j]+Er[i][j+1]);
          g=(Er[i][j] * Er[i-1][j])/(Er[i][j]+Er[i-1][j]);
          h=(Er[i][j] * Er[i+1][j])/(Er[i][j]+Er[i+1][j]);
                        
          Vij[i][j]=r*(a+b+c+d)/(e+f+g+h) + (1-r)*Vij[i][j];
        }
      }
    }
    Barrier();
    for(i= firstcol ; i <= lastcol; ++i){
      if(i%2 ==1 )
	jstart=2;
      else
	jstart=1;
      for(j=jstart ; j < height -1; j+=2){
        if(oddity[i][j] == ORDINARY_INTERIOR_POINT) /* Same dielectric all around */
          Vij[i][j]=r_over_4*(Vij[i][j+1]+Vij[i+1][j]+Vij[i][j-1]+Vij[i-1][j])+one_minus_r*Vij[i][j];
        else if(oddity[i][j] > ORDINARY_INTERIOR_POINT) /* only update dielectrics, not conductors */
        {
          a=(Er[i][j] * Er[i][j-1] * Vij[i][j-1])/(Er[i][j] + Er[i][j-1]);
          b=(Er[i][j] * Er[i][j+1] * Vij[i][j+1])/(Er[i][j] + Er[i][j+1]);
          c=(Er[i][j] * Er[i-1][j] * Vij[i-1][j])/(Er[i][j] + Er[i-1][j]);
          d=(Er[i][j] * Er[i+1][j] * Vij[i+1][j])/(Er[i][j] + Er[i+1][j]);
    
          e=(Er[i][j] * Er[i][j-1])/(Er[i][j]+Er[i][j-1]);
          f=(Er[i][j] * Er[i][j+1])/(Er[i][j]+Er[i][j+1]);
          g=(Er[i][j] * Er[i-1][j])/(Er[i][j]+Er[i-1][j]);
          h=(Er[i][j] * Er[i+1][j])/(Er[i][j]+Er[i+1][j]);
                        
          Vij[i][j]=r*(a+b+c+d)/(e+f+g+h) + (1-r)*Vij[i][j];
        }
      }
    }
    Barrier();
  }
  Barrier();
  return(0);
}

double finite_difference_multi_threaded()
{
  int i, j, ret, thread_number;
  pthread_t thread_id[MAXIMUM_PROCESSING_DEVICES];


  double capacitance_per_metre, energy_per_metre;


  /* initialize mutex and condition variable */
  pthread_mutex_init(&barrier, NULL);
  pthread_cond_init(&go, NULL);
  for(thread_number=0;thread_number<number_of_workers;thread_number++){   
    ret=pthread_create(&thread_id[thread_number],NULL, worker,(void *)thread_number);
    if(ret != 0)
      exit_with_msg_and_exit_code("failed to create thread in finite_difference_multi_threaded.c",THREAD_CREATION_FAILED);
  } 
  /* Wait for each thread to join - i.e. once they are all finished. */
  for(thread_number=0;thread_number<number_of_workers;thread_number++)
  {
    ret=pthread_join(thread_id[thread_number], NULL);
    if(ret != 0)
      exit_with_msg_and_exit_code("failed to join thread in finite_difference_multi_threaded.c",THREAD_FAILED_TO_JOIN);
      }
  energy_per_metre=0.0;
  /*
  The following code is wrong, but worked on all systems apart from AIX !!

  for(i=0;i<width;++i)
    for(j=0;j<height;++j)
	energy_per_metre+=find_energy_per_metre(i,j);
	*/

  for(i=1;i<width-1;++i)
    for(j=1;j<height-1;++j)
	energy_per_metre+=find_energy_per_metre(i,j);
 
  if(coupler==FALSE)
    capacitance_per_metre=2*energy_per_metre;
  else 
    capacitance_per_metre=energy_per_metre;
  return(capacitance_per_metre);
}
#endif
