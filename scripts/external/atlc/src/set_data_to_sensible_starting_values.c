#include "config.h"

#ifdef HAVE_STDLIB_H
#include <stdlib.h>
#endif

#ifdef SYS_TYPES_H
#include <sys/types.h>
#endif

#ifdef HAVE_STRINGS_H
#include <strings.h>
#endif

#ifdef HAVE_STRING_H
#include <string.h>
#endif

#ifdef HAVE_TIME_H
#include <time.h>
#endif

#include "definitions.h"


void set_data_to_sensible_starting_values(struct transmission_line_properties *data)
{
  /* Most of the values below are set to -3. This is so when they are unchanged,
  its easy to pick them up in a debugger. Others are set to important values
  rather than -3 */
  data->dielectrics_in_bitmap=0;
  data->dielectrics_on_command_line=0;
  data->r=1.9; /* For now at least, this is still global, so this has no effect XXX */
  data->image_fiddle_factor=IMAGE_FIDDLE_FACTOR;
  data->cutoff=0.0001;
  data->avoid_use_of_fast_convergence_methodQ=FALSE;
  data->the_single_Er=1.0;
  data->Er=1.0;
  data->found_this_dielectric=1.0;
  data->couplerQ=FALSE;
  data->verbose_level=0;
  data->should_binary_data_be_written_tooQ=FALSE;
  data->write_binary_field_imagesQ=TRUE;
  data->write_bitmap_field_imagesQ=TRUE;

  data->Lodd_vacuum=-3; data->Leven_vacuum=-3;
  data->L_vacuum=-3; data->Codd_vacuum=-3;
  data->Codd_vacuum=-3; data->Ceven_vacuum=-3;
  data->Lodd_vacuum=-3; data->Leven_vacuum=-3; 
  data->display=-3;
  data->Zo=-3 ; data->Zo_vacuum=-3 ; data->Zodd_vacuum=-3; 
  data->Zodd_vacuum=-3; data->Zeven_vacuum=-3; 
  data->Zeven_vacuum=-3; data->Zdiff=-3; data->Zdiff_vacuum=-3; 
  data->Zcomm=-3; data->Zcomm_vacuum=-3;
  data->velocity=-3; data->velocity_factor=-3; 
  data->relative_permittivity=-3;
}
