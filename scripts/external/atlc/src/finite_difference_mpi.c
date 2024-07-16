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

#ifdef ENABLE_MPI /* file only needed on MPI systems. */

#include <mpi.h>

#ifdef HAVE_STDLIB_H
#include <stdlib.h>
#endif

#include "definitions.h"


extern int coupler;
extern int width, height;
extern double **Vij, **Er;
extern signed char **oddity;
extern int num_pes;
extern int dielectrics_to_consider_just_now;
extern struct strip strip_map[MAX_PES+1];

/* these variables are only needed on PE 0,
   but are declared here for all for convenience.
   by switching to a dynamic allocation scheme,
   we could make them local to finite_difference,
   and only allocate them on PE 0.
*/
MPI_Request energy_rcv_requests[MAX_PES];
double energies[MAX_PES];

/*
  the job of a worker PE is to work on a columnar strip
  of the voltage array for a given number of iterations,
  then send off the results to PE 0.

  in order for a worker PE to calculate the edges of 
  its strip, it needs two additional columns of data
  to the left and two additional columns of data to
  the right of its strip.  initially, PE 0 supplies
  the extra columns.  after the first iteration, the
  the PE needs to update the columns adjacent to its
  strip edges, and to do that, it needs the columns
  that are adjacent to those (hence each worker PE
  maintains 4 columns of data in addtion to its strip).  
  the outermost columns are sent from the neighbor PEs
  after they are done computing them for the current
  iteration.  after they are received, the columns 
  adjacent to the strip edges are updated, and the PE
  moves on to the next iteration.

  after the prescribed number of iterations are completed,
  each worker PE sends its strip of the voltage matrix 
  to PE 0, so that PE 0 has a complete up-to-date copy
  of the voltage array after each call to finite_difference.
  while that data is being sent, the worker PE computes
  the energy_per_metre ot its strip and then sends that
  off to PE 0, so that PE 0 can compute the overall
  capacitance_per_metre.
  
*/


/*
  this routine is only run on the worker PEs
*/

void mpi_worker(int rank) {

  int width_height[2];
  int strip_params[2];
  int start_col, num_cols;
  MPI_Status status;
  int control, done;
  int i,j,iterations;
  MPI_Request send_requests[2];
  MPI_Status send_statuses[2];
  MPI_Request rcv_requests[2];
  double energy_per_metre;
  int index;

  /* get the total width and height of the voltage
	 matrix.  the worker PE needs to know the column
	 height in order to run its calculations.  the
	 width is also currently needed for the electric
	 field subroutines.
  */
  MPI_Recv(&width_height,
		   2,
		   MPI_INT,
		   0,
		   MSG_TAG_WIDTH_HEIGHT,
		   MPI_COMM_WORLD,
		   &status);

  width = width_height[0];
  height = width_height[1];

  /* get the location and size of the strip of the
	 voltage matrix that has been assigned to this
	 PE.  strictly speaking, the PE does not need
	 to know the starting column number since it 
	 uses its own local indexing scheme, but it
	 is sent anyway as a debugging aid if needed.
  */
  MPI_Recv(&strip_params,
		   sizeof(strip_params)/sizeof(int),
		   MPI_INT,
		   0,
		   MSG_TAG_STRIP_PARAMS,
		   MPI_COMM_WORLD,
		   &status);

  /* this is the starting column in the global voltage matrix
	 of the columnar strip this PE has been assigned*/
  start_col = strip_params[0]; 
  
  /* this is the width of the columnar strip that this PE
	 has been assigned from the global voltage matrix */
  num_cols = strip_params[1];

  /* allocate matrixes big enough to contain the
	 assigned strip and supporting data */
  oddity=cmatrix(0,num_cols+4,0,height);
  Vij=dmatrix(0,num_cols+4,0,height);
  Er=dmatrix(0,num_cols+4,0,height);
 
  /* get the oddity data to use in computing 
	 the assigned strip */
  MPI_Recv(oddity[0],
		   (num_cols+4)*height,
		   MPI_DOUBLE,
		   0,
		   MSG_TAG_NODE_TYPE,
		   MPI_COMM_WORLD,
		   &status);

  /* get the Er data to use in computing 
	 the assigned strip */
  MPI_Recv(Er[0],
		   (num_cols+4)*height,
		   MPI_DOUBLE,
		   0,
		   MSG_TAG_ER,
		   MPI_COMM_WORLD,
		   &status);

  /*************************************************
   * all of the data received above this point is  *
   * sent only once in the lifetime of the program *
   *************************************************/

  done = 0;
  do {

	/* recieve a control word that tells
	   the PE whether to set off on another
	   set of iterations, or to exit */

	MPI_Recv(&control,
			 1,
			 MPI_INT,
			 0,
			 MSG_TAG_CONTROL,
			 MPI_COMM_WORLD,
			 &status);

	switch (control) {
	case CONTROL_VALUE_RECEIVE_DATA:
	  /* receive the strip of the voltage matrix
		 that we are to update. this is sent by PE 0. */
	  MPI_Recv(Vij[1],
			   (num_cols+2)*height,
			   MPI_DOUBLE,
			   0,
			   MSG_TAG_VIJ,
			   MPI_COMM_WORLD,
			   &status);

	  /* receive the current value of 
		 dielectrics_to_consider_just_now.
		 this is sent by PE 0. */
	  MPI_Recv(&dielectrics_to_consider_just_now,
			   1,
			   MPI_INT,
			   0,
			   MSG_TAG_ORDINARY_INTERIOR_POINTS,
			   MPI_COMM_WORLD,
			   &status);

	  break;
	case CONTROL_VALUE_SEND_DATA:
	  /* send our strip to PE 0 */
	  MPI_Send(Vij[2],
			   num_cols*height,
			   MPI_DOUBLE,
			   0,
			   MSG_TAG_VIJ,
			   MPI_COMM_WORLD);
	  break;
	case CONTROL_VALUE_DO_ITERATIONS:
	  /* receive the number of iterations we are
		 to compute for. this is sent by PE 0 at
		 the beginning of finite_difference. */
	  MPI_Recv(&iterations,
			   1,
			   MPI_INT,
			   0,
			   MSG_TAG_ITERATIONS,
			   MPI_COMM_WORLD,
			   &status);

	  i=0;
	  do {

		/* update our strip of the voltage matrix */
		do_columns(2, num_cols, 0);

		/* send the columns that the neighbor PEs
		   require to the nieghbor PEs */
		MPI_Isend(Vij[num_cols+1],
				  height,
				  MPI_DOUBLE,
				  (rank+1)%num_pes,
				  MSG_TAG_VIJ_RBORDER,
				  MPI_COMM_WORLD,
				  &send_requests[1]);

		MPI_Isend(Vij[2],
				  height,
				  MPI_DOUBLE,
				  rank-1,
				  MSG_TAG_VIJ_LBORDER,
				  MPI_COMM_WORLD,
				  &send_requests[0]);

		/* receive the columns that we need
		   to update the columns adjacent
		   to our strip edges from the neighbor
		   PEs */
		MPI_Irecv(Vij[num_cols + 3],
				  height,
				  MPI_DOUBLE,
				  (rank+1)%num_pes,
				  MSG_TAG_VIJ_LBORDER,
				  MPI_COMM_WORLD,
				  &rcv_requests[0]);
	  
		MPI_Irecv(Vij[0],
				  height,
				  MPI_DOUBLE,
				  rank-1,
				  MSG_TAG_VIJ_RBORDER,
				  MPI_COMM_WORLD,
				  &rcv_requests[1]);

		/* update the columns adjacent to our strip
		   edges */
		MPI_Waitany(2, 
					rcv_requests, 
					&index,
					&status);

		if (0 == index) {
		  update_voltage_array(num_cols + 2,0,Vij_TO_Vij);
		} else {
		  update_voltage_array(1,0,Vij_TO_Vij);
		}

		MPI_Waitany(2, 
					rcv_requests, 
					&index,
					&status);

		if (0 == index) {
		  update_voltage_array(num_cols + 2,0,Vij_TO_Vij);
		} else {
		  update_voltage_array(1,0,Vij_TO_Vij);
		}


		MPI_Waitall(2, send_requests, send_statuses);
	  
		i++;
	  } while(i < iterations);


	  energy_per_metre=0.0;
	  for(i=2;i<2+num_cols;++i)
		for(j=0;j<height;++j) { 
		  energy_per_metre+=find_energy_per_metre(i,j);
		}

	  MPI_Send(&energy_per_metre,
			   1,
			   MPI_DOUBLE,
			   0,
			   MSG_TAG_ENERGY,
			   MPI_COMM_WORLD);
	  break;
	case CONTROL_VALUE_EXIT:
	  done = 1;
	  break;
	}
	
  } while (0 == done);
  
}



void do_columns(int start_col, int num_cols, int calculate_edges)
{
  int i;
  int end_col;

  end_col = start_col + num_cols - 1;

  for(i=start_col; i<=end_col; ++i)
  {
	update_voltage_array(i, calculate_edges,Vij_TO_Vij);
  }
}



/* There are three versions of finite_difference. They all take the same 
arguments and return the same data. One is single threaded, one is
multi-threaded, and this one uses MPI. */

double finite_difference(int accuracy)
{
  int i, j, a;
  double capacitance_per_metre=0.0, energy_per_metre;
  int left_start_col, left_num_cols;
  int right_start_col, right_num_cols;
  MPI_Status status;
  int control;
  MPI_Request send_requests[2];
  MPI_Status send_statuses[2];
  MPI_Request rcv_requests[2];
  MPI_Status rcv_statuses[2];
  int index;

  for(i=1; i<num_pes; i++) {

	/* arm worker */
	control = CONTROL_VALUE_DO_ITERATIONS;
	MPI_Send(&control,
			 1,
			 MPI_INT,
			 i,
			 MSG_TAG_CONTROL,
			 MPI_COMM_WORLD);

	/* send the iteration count */
	MPI_Send(&accuracy,
			 1,
			 MPI_INT,
			 i,
			 MSG_TAG_ITERATIONS,
			 MPI_COMM_WORLD);
  }

  /* these are the parameters of the left and right
	 half-strips that PE 0 is responsible for */
  left_start_col = strip_map[0].start_col;
  left_num_cols = strip_map[0].num_cols;

  right_start_col = strip_map[num_pes].start_col;
  right_num_cols = strip_map[num_pes].num_cols;

  for(a=1; a<=accuracy; ++a) {
	
	/* update the left and right half-strips */
	do_columns(left_start_col+1, left_num_cols-1, 1);
	do_columns(right_start_col, right_num_cols-1, 1);

	/* send the columns that PE 1 and PE N-1
	   need to those PEs */
	MPI_Isend(Vij[left_num_cols - 2],
			  height,
			  MPI_DOUBLE,
			  1,
			  MSG_TAG_VIJ_RBORDER,
			  MPI_COMM_WORLD,
			  &send_requests[0]);

	MPI_Isend(Vij[right_start_col+1],
			  height,
			  MPI_DOUBLE,
			  num_pes-1,
			  MSG_TAG_VIJ_LBORDER,
			  MPI_COMM_WORLD,
			  &send_requests[1]);

	/* receive the columns that we need
	   to update the columns adjacent
	   to our strip edges from PE 1 and
	   PE N-1 */
	MPI_Irecv(Vij[right_start_col-2],
			  height,
			  MPI_DOUBLE,
			  num_pes-1,
			  MSG_TAG_VIJ_RBORDER,
			  MPI_COMM_WORLD,
			  &rcv_requests[0]);

	MPI_Irecv(Vij[left_num_cols+1],
			  height,
			  MPI_DOUBLE,
			  1,
			  MSG_TAG_VIJ_LBORDER,
			  MPI_COMM_WORLD,
			  &rcv_requests[1]);

	MPI_Waitall(2, rcv_requests, rcv_statuses);

	/* update the columns adjacent to our strip
	   edges */
	update_voltage_array(left_num_cols, 1,Vij_TO_Vij);
	update_voltage_array(right_start_col - 1, 1,Vij_TO_Vij);

	MPI_Waitall(2, send_requests, send_statuses);

  }  /* end of accuracy loop */

  /* set up receives for the energies from the worker PEs */
  for(i=1; i<num_pes; i++) {
	MPI_Irecv(&energies[i-1],
			  1,
			  MPI_DOUBLE,
			  i,
			  MSG_TAG_ENERGY,
			  MPI_COMM_WORLD,
			  &energy_rcv_requests[i-1]);
  }


  /* The energy in the matrix has now been minimised a number
	 (accuracy) times, so we now calcuate the capacitance to see if it is
	 converging */

  energy_per_metre=0.0;

  /* sum up all of the PE energies.
     they can arrive in any order. */
  for(i=1; i<num_pes; i++) {
	MPI_Waitany(num_pes-1, 
				energy_rcv_requests,
				&index,
				&status);
	energy_per_metre += energies[index];
  }
	
  /* add in the left half-strip energy */
  for(i=left_start_col;i<left_start_col+left_num_cols;++i)
	for(j=0;j<height;++j)
	  { 
		energy_per_metre+=find_energy_per_metre(i,j);
	  }

  /* add in the right half-strip energy */
  for(i=right_start_col;i<right_start_col+right_num_cols;++i)
	for(j=0;j<height;++j)
	  { 
		energy_per_metre+=find_energy_per_metre(i,j);
	  }

  if(coupler==FALSE)
	capacitance_per_metre=2*energy_per_metre;
  else if (coupler==TRUE)
	capacitance_per_metre=energy_per_metre;

  return(capacitance_per_metre);
}
#endif
