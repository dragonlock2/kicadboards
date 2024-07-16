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

#ifdef HAVE_MATH_H
#include <math.h>
#endif 

#ifdef HAVE_STDIO_H
#include <stdio.h>
#endif

#define EXIT_READ_FAILURE

#define       FREE_ARG char*
#define       NR_END 1

#define    CONDUCTOR_MINUS_ONE_V                                               5 
#define    CONDUCTOR_ZERO_V                                                   10 
#define    CONDUCTOR_PLUS_ONE_V                                               15 

#define    CONDUCTOR_FLOATING                                                 20

#define    METAL_LEFT                                                         25
#define    METAL_RIGHT                                                        30
#define    METAL_ABOVE                                                        35
#define    METAL_BELOW                                                        40
#define    METAL_BELOW_AND_LEFT                                               45
#define    METAL_BELOW_AND_RIGHT                                              50
#define    METAL_ABOVE_AND_LEFT                                               55 
#define    METAL_ABOVE_AND_RIGHT                                              60

#define    DIELECTRIC                                                         65 /* not for oddity */
#define    ORDINARY_INTERIOR_POINT                                            70

#define    TOP_LEFT_CORNER                                                    75
#define    BOTTOM_RIGHT_CORNER                                                80
#define    TOP_RIGHT_CORNER                                                   85
#define    BOTTOM_LEFT_CORNER                                                 90
#define    ORDINARY_POINT_BOTTOM_EDGE                                         95
#define    ORDINARY_POINT_TOP_EDGE                                           100
#define    ORDINARY_POINT_LEFT_EDGE                                          105
#define    ORDINARY_POINT_RIGHT_EDGE                                         110
#define    DIFFERENT_DIELECTRIC_LOCALLY                                      115

#define    DIFFERENT_DIELECTRIC_ABOVE_AND_RIGHT                              120
#define    DIFFERENT_DIELECTRIC_BELOW_AND_LEFT                               125
#define    DIFFERENT_DIELECTRIC_BELOW_AND_RIGHT                              135
#define    DIFFERENT_DIELECTRIC_VERTICALLY                                   140
#define    DIFFERENT_DIELECTRIC_HORIZONTALLY                                 145
#define    DIFFERENT_DIELECTRIC_BELOW                                        150
#define    DIFFERENT_DIELECTRIC_LEFT                                         155
#define    DIFFERENT_DIELECTRIC_RIGHT                                        160
#define    DIFFERENT_DIELECTRIC_ABOVE_AND_LEFT                               165

#define    UNDEFINED_ODDITY                                                  255

/* The following two determine what happens when a coupler is present
and the voltages have to be swapped from negative to positive in the
simulation. */
#define ITERATIONS                      100
#define POS_TO_NEG                         1
#define NEG_TO_POS                         -1
#define METAL_ER  1e9 

#define DONT_ZERO_ELEMENTS  0       
#define ZERO_ELEMENTS_FIRST 1       

#ifndef TRUE 
#define TRUE 1
#define FALSE 0
#endif

#define DONT_CARE                          0
#define ODD                                1
#define EVEN                               2

#define Vij_TO_Vij                         1
#define VijB_TO_Vij                        2
#define Vij_TO_VijB                        3

#define MAXIMUM_PROCESSING_DEVICES              1024
#define MAX_DIFFERENT_PERMITTIVITIES   10000
#define MAX_ER 12.0

#define COLOUR 0
#define MONOCHROME 1
#define MIXED      2
#define Z0                              1

#define Z_ODD_SINGLE_DIELECTRIC         1
#define Z_EVEN_SINGLE_DIELECTRIC        2
#define Z_ODD_MULTIPLE_DIELECTRIC       3
#define Z_EVEN_MULTIPLE_DIELECTRIC      4

#define Z_ALL                       5

/* The value of EPSILON_0 is taken from the UK National Physical
Laboratory's list of physical constants found on the web. */

#define EPSILON_0 8.854187817e-12
#define MU_0 M_PI*4e-7
#define MAX_THREADS  16
#define BORDER   5 /* The border to put around images. 1 is minimum, but 5 looks better */

#define TINY 1e-12
#define VERY_LARGE 1e15
#define DEFAULT_BMP_SIZE 6
#define DEFAULT_COUPLER_BMP_SIZE 18

#define IMAGE_FIDDLE_FACTOR 2.0
#define ACCEPTABLE_ERROR 0.02
#define UNACCEPTABLE_ERROR 0.05

#define RECT_IN_RECT 1
#define CIRC_IN_CIRC 2
#define CIRC_IN_RECT 3
#define RECT_IN_CIRC 4

#define DEFAULT_GMIN 0.5
#define DEFAULT_GMAX 5.0
#define DEFAULT_GSTEP 0.5

#define DEFAULT_SMIN 0.5
#define DEFAULT_SMAX 5.0
#define DEFAULT_SSTEP 0.5

#define DEFAULT_WMIN 0.5
#define DEFAULT_WMAX 5.0
#define DEFAULT_WSTEP 0.5


#ifdef ENABLE_MPI
#define MAX_PES 256
#define MSG_TAG_WIDTH_HEIGHT 1
#define MSG_TAG_STRIP_PARAMS 2
#define MSG_TAG_NODE_TYPE    3
#define MSG_TAG_ER           4
#define MSG_TAG_CONTROL      5
#define MSG_TAG_ITERATIONS   6
#define MSG_TAG_VIJ          7
#define MSG_TAG_VIJ_LBORDER  8
#define MSG_TAG_VIJ_RBORDER  9
#define MSG_TAG_ENERGY      10
#define MSG_TAG_DIELECTRICS 11

#define CONTROL_VALUE_RECEIVE_DATA     0
#define CONTROL_VALUE_SEND_DATA        1
#define CONTROL_VALUE_DO_ITERATIONS    2
#define CONTROL_VALUE_EXIT             3
#endif /* ENABLE_MPI */


extern char *my_optarg;
/* I needed to invent add my_ in front of the usual name for optind,
opterr, optopt etc, since they are defined by the system, and I'm using
a local package_version of getopts (get_options) so it exists with the PC too.
Most systems do not seem to mind if these names exist or not, but a
Power Machintosh powerpc running Darwin Kernel Package_version 5.3 gave this as
a warning. Hence I'll avoid the problem by adding my_ */

extern int my_optind, my_opterr, my_optopt;

struct transmission_line_properties{
double WW, HH, ww, ss, gg, hh, tt, Er1, Er2;
int  W, H, w, s, g, h, t, bmp_size;

int verbose_level; /* 0, 1 or 2 */
double Codd, Ceven, C;
double velocity_odd, velocity_factor_odd, relative_permittivity_odd;
double velocity_even, velocity_factor_even, relative_permittivity_even;
double Lodd_vacuum, Leven_vacuum, L_vacuum;
double Codd_vacuum, Ceven_vacuum, C_vacuum, C_non_vacuum;
double Zo, Zo_vacuum, Zo_non_vacuum, Zodd, Zodd_vacuum, Zeven;
double Zeven_vacuum, Zdiff, Zdiff_vacuum, Zcomm, Zcomm_vacuum;
double Er, the_single_Er, Er_odd, Er_even;
double velocity, velocity_factor, relative_permittivity;
double r; /* rate multiplier */
double image_fiddle_factor;
double cutoff; /* How small the error in subsequent itterations must be */
int compute, display; /* none, ZO, ZODD, ZEVEN. ZEVEN_VAC, ZODD_VAC; */
int should_binary_data_be_written_tooQ;
int dielectrics_to_consider_just_now;
int non_vacuum_dielectric_found;
double found_this_dielectric;
int dielectrics_on_command_line;
int dielectrics_in_bitmap;
int avoid_use_of_fast_convergence_methodQ;
int couplerQ;
int write_binary_field_imagesQ;
int write_bitmap_field_imagesQ;
double float_values[10];
int int_values[10];
int importance[10];
int odd_or_even[10];
int best[10];
int non_metallic_pixels;
int tenth_of_estimated_iterations_needed;
};

#define NOT_IMPORTANT 0   /* The importance to attach to getting the */
#define IMPORTANT 1       /* best value of integers for the grid */
#define MOST_IMPORTANT 2

struct pixels
{
   int red;          /* +1 V */
   int green;        /* 0 V */
   int blue;         /* -1 V */
   int white;        /* Vacuum */
   int other_colour;  /* mix of red, green and blue  */
   double epsilon;
};

struct max_values
{
double Ex_or_Ey_max, E_max, V_max, U_max, permittivity_max;
};


struct fit_doubles_to_integers{
int n_min, n_max, n;
int m, in[100];
double out[100], weight[100], good, acceptable;
double largest_errror;
double rms_errror;
};

#ifdef ENABLE_MPI
struct strip {
  int start_col;
  int num_cols;
};
#endif /* ENABLE_MPI */

/* Despite the fact the Bitmap_File_Head_Struct and Bitmap_Head_Struct
all have int's for the types of data, in practice these must be 2 and 4
byte varialbes. As such, they are written a character at a time, so the
data size is unimportant. This was neeed on the Cray, due to the fact
sizeof(short)=8 */

struct Bitmap_File_Head_Struct
{
  unsigned char   zzMagic[2];	/* 00 "BM" */
  int     bfSize;      /* 02 */
  int    zzHotX;	/* 06 */
  int    zzHotY;	/* 08 */
  int     bfOffs;      /* 0A */
  int     biSize;      /* 0E */
};

struct Bitmap_Head_Struct
{
  int     biWidth;     /* 12 */
  int     biHeight;    /* 16 */
  int    biPlanes;    /* 1A */
  int    biBitCnt;    /* 1C */
  int     biCompr;     /* 1E */
  int     biSizeIm;    /* 22 */
  int     biXPels;     /* 26 */
  int     biYPels;     /* 2A */
  int     biClrUsed;   /* 2E */
  int     biClrImp;    /* 32 */
                        /* 36 */
};

#ifndef M_PI
#define M_PI 3.141592653589793238462643383279502884197169399375105820975
#endif

#define NUMBER_OF_DIELECTRICS_DEFINED 13

int main(int argc, char **argv);
void byteswap_doubles(double *a);
void read_bitmap_file_headers(char *filename, int *offset, size_t *size, int *width, int *height);
void help(char *filename);
double **dmatrix(long nrl, long nrh, long ncl, long nch);
void free_dmatrix(double **m, long nrl, long nrh, long ncl, long nch);
void free_cmatrix(char **m, long nrl, long nrh, long ncl, long nch);
char *string(long nl,long nh);
void free_string(char *v, long nl, long nh);
void swap_bytes2(unsigned char *buffer, int offset, short *answer);
void swap_bytes4(unsigned char *buffer, int offset, int *answer);
void free_ustring(unsigned char *v, long nl, long nh);
void setup_arrays(struct transmission_line_properties *data);
double finite_difference_single_threaded();
double finite_difference_multi_threaded();
void *do_columns(void *thread_arg);
void usage_atlc(void);
void write_fields_for_two_conductor_lines(char *filename, struct transmission_line_properties data, size_t size);
void write_fields_for_directional_couplers(char *filename, struct transmission_line_properties data, size_t size, int odd_or_even);
char          **cmatrix(long nrl, long nrh, long ncl, long nch);
unsigned char **ucmatrix(long nrl, long nrh, long ncl, long nch);
signed char **scmatrix(long nrl, long nrh, long ncl, long nch);

int *ivector(long nl, long nh);
void get_Er1_and_Er2_colours(int *colour_Er1, int *colour_Er2);
void convert_create_bmp_for_rect_in_rect_dimensions_to_integers(int bmp_size);
void convert_create_bmp_for_circ_in_circ_dimensions_to_integers(int bmp_size);
unsigned char *ustring(long nl,long nh);
void write_bitmap(FILE *image_data_fp, struct transmission_line_properties foo);
void usage_create_bmp_for_rect_in_rect(void);
void usage_create_bmp_for_rect_cen_in_rect(void);
void write_bitmap_out(unsigned char *image_data, FILE *image_data_fp,int image_size, int W, int H);
int align_bitmap_image(int W, int H, unsigned char *unaligned_image, unsigned char *byte_aligned_image);
void fill_create_bmp_for_rect_in_rect(char *image_vector, int colour_Er1, int colour_Er2);
void check_create_bmp_for_rect_in_rect_ints(void);
void exit_with_msg_and_exit_code(const char *error_text, int exitnumber);
void check_error(double user, int create_bmp_for_rect_in_rect, double gridsize, const char *name);
void check_parameters_for_create_bmp_for_circ_in_circ(void);
void fill_image_vector_with_data(unsigned char *image_vector, int colour_Er1, int colour_Er2, struct transmission_line_properties x);
void usage_create_bmp_for_circ_in_circ(void);
void convert_create_bmp_for_rect_in_circ_dimensions_to_integers(int accuracy_level);
void usage_create_bmp_for_rect_in_circ(void);
void convert_create_bmp_for_circ_in_rect_dimensions_to_integers(int accuracy_level);
void usage_create_bmp_for_circ_in_rect(void);
void check_for_shorts(void);
void usage_symmetrical_strip(void);
void fill_image_vector_for_thin_strip(int W,int H, int w, unsigned char *unaligned_image_vector);
double K_over_Kdash(double k);
double calculate_symmetrical_stripline_impedance(int H, int w);

void free_ucmatrix(unsigned char **m, long nrl, long nrh, long ncl, long nch);
void free_scmatrix(signed char **m, long nrl, long nrh, long ncl, long nch);

int print_data(FILE *fp, char *filename, double Er, double C, double L, double Zo, double
Zodd, double Zeven, int whichZ, double v, double vf);
void set_oddity_value(void);
double find_energy_per_metre(int i, int j);
FILE *get_file_pointer_with_right_filename(char *filename, const char *ext);
void find_maximum_values(struct max_values *maximum_values, int zero_elementsQ);
void calculate_colour_data(double x, double xmax, int w, int h, int offset, unsigned char *image_dat, int image_type,
unsigned char *red, unsigned char *green, unsigned char *blue, double image_fiddle_factor);
double find_Ex(int w, int h) ;
double find_Ey(int w, int h);
double find_E(int w, int h);
double voltage_ij(int i, int j);
void usage_readbin(void);
void ERR(const char *s, char c, char **argv);
int get_options(int argc, char **argv, const char *opts); 
char *index2(const char *str, char c); 
void swap_conductor_voltages();
void usage_create_bmp_for_stripline_coupler(void);
double calculate_integer_values(struct transmission_line_properties *optimise, int n, int accuarcy_level);
void calculate_Zodd_and_Zeven(double *Zodd, double *Zeven, double *Zo, double w, double H, double s, double er);
void usage_design_coupler(void);
void print_copyright(const char *s);
void give_examples_of_using_design_coupler(void);
void do_fd_calculation(struct transmission_line_properties *data, size_t size, FILE *where_to_print_fp, char *inputfile_filename);
void print_data_for_directional_couplers(struct transmission_line_properties data, FILE *where_to_print_fp, char *inputfile_name);
void print_data_for_two_conductor_lines(struct transmission_line_properties data, FILE *where_to_print_fp, char *inputfile_name);
void set_data_to_sensible_starting_values(struct transmission_line_properties *data);
void check_parameters_of_create_bmp_for_microstrip_coupler(struct transmission_line_properties pcb);
void convert_create_create_bmp_for_coupled_microstrip_dimensions_to_integers(struct transmission_line_properties *pcb);
void usage_create_bmp_for_microstrip_coupler(void);
void usage_find_optimal_dimensions_for_microstrip_coupler(void);
void check_parameters_of_create_bmp_for_circ_in_circ(void);
void check_parameters_of_create_bmp_for_circ_in_rect(void);
void check_parameters_of_create_bmp_for_rect_in_circ(void);
void check_parameters_of_create_bmp_for_rect_in_rect(void);
void usage_create_bmp_for_symmetrical_stripline(void);
void check_parameters_for_find_optimal_dimensions_for_microstrip_coupler (double h,double t,double Er1,double Er2,double ideal_Zodd,double ideal_Zeven);
double *dvector(long nl, long nh);
void *worker(void *thread_arg);
void free_ivector(int *v, long nl, long nh);
double check_convergence(double **grid1, double **grid2, int w, int h);
void error_check(char *s);
void free_dvector(double *v, long nl, long nh);
void usage_create_any_bitmap();
void update_voltage_array(int n, int starti, int endi, int i_index, int j_index, double **from, double **to);
void nrerror(char error_text[]);
void check_for_boundaries(void);



#define ONE
#define TWO
#define THREE
#define FOUR
#define FIVE
#define SIX
#define SEVEN
#define EIGHT
#define NINE
#define HUNDRED

#define I 58
#define J 241
