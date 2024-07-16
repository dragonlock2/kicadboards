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

#define OKAY                                                       0
#define CANT_OPEN_FILE_FOR_READING                                 1
#define CANT_OPEN_FOR_WRITING                                      2
#define CANT_OPEN_FILE_FOR_APPENDING                               3
#define CANT_CLOSE_FILE                                            4
#define WRITE_FAILURE                                              5
#define THE_WIDTH_w_DIVIDED_BY_THE_HEIGHT_H_IS_TOO_LARGE           6
#define PROGRAM_NOT_IMPLEMENTED                                    7
#define PROGRAM_CALLED_WITH_WRONG_NUMBER_OF_ARGUMENTS              8
#define UNACCEPTABLE_ERROR_WHEN_CONVERTING_TO_INTEGERS             9
#define MEMORY_ALLOCATION_ERROR_IN_VECTOR                         10
#define MEMORY_ALLOCATION_ERROR_IN_IVECTOR                        11
#define MEMORY_ALLOCATION_ERROR_IN_CVECTOR                        12
#define MEMORY_ALLOCATION_ERROR_IN_DVECTOR                        13
#define MEMORY_ALLOCATION_ERROR_IN_CMATRIX                        14
#define MEMORY_ALLOCATION_ERROR_IN_UCMATRIX                       15
#define MEMORY_ALLOCATION_ERROR_IN_MATRIX                         16
#define MEMORY_ALLOCATION_ERROR_IN_DMATRIX                        17
#define MEMORY_ALLOCATION_ERROR_IN_IMATRIX                        18
#define MEMORY_ALLOCATION_ERROR_IN_STRING                         19
#define MEMORY_ALLOCATION_ERROR_IN_USTRING                        20
#define SILLY_ARGUMENTS_IN_FREE_VECTOR                            21
#define SILLY_ARGUMENTS_IN_FREE_IVECTOR                           22
#define SILLY_ARGUMENTS_IN_FREE_CVECTOR                           23
#define SILLY_ARGUMENTS_IN_FREE_DVECTOR                           24
#define SILLY_ARGUMENTS_IN_FREE_DMATRIX                           25
#define SILLY_ARGUMENTS_IN_FREE_CMATRIX                           26
#define SILLY_ARGUMENTS_IN_FREE_UCMATRIX                          27
#define SILLY_ARGUMENTS_IN_FREE_IMATRIX                           28
#define SILLY_ARGUMENTS_IN_FREE_STRING                            29
#define SILLY_ARGUMENTS_IN_FREE_USTRING                           30
#define VOLTAGE_OUT_OF_RANGE                                      31
#define ARGUMENT_w_OUT_OF_RANGE                                   32
#define ARGUMENT_h_OUT_OF_RANGE                                   33
#define ARGUMENT_s_OUT_OF_RANGE                                   34
#define ARGUMENT_g_OUT_OF_RANGE                                   35
#define ARGUMENT_Er1_OUT_OF_RANGE                                 36
#define ARGUMENT_Er2_OUT_OF_RANGE                                 37
#define ARGUMENT_W_OUT_OF_RANGE                                   36
#define ARGUMENT_H_OUT_OF_RANGE                                   38
#define ARGUMENT_t_OUT_OF_RANGE                                   39
#define ARGUMENT_ideal_Zodd_OUT_OF_RANGE                          41
#define ARGUMENT_ideal_Zeven_OUT_OF_RANGE                         42
#define IDEAL_Zodd_NOT_LESS_THAN_IDEAL_Zeven                      43
#define NOT_LINKED_WITH_GSL_LIBRARY                               44
#define NOT_LINKED_WITH_THREADS_LIBRARY                           45
#define NOT_LINKED_WITH_MPI_LIBRARY                               46
#define UNDEFINED_COLOUR_IN_BITMAP                                47
#define NOT_A_VALID_BITMAP_FILE                                   48
#define OS2_FORMAT_BMP_FILE                                       49
#define NOT_A_WINDOZE_FORMAT_BITMAP                               50
#define BITMAP_NOT_24_BIT                                         51
#define WIDTH_OR_HEIGHT_ZERO_IN_BITMAP                            52
#define BITPLANES_NOT_1_IN_BITMAP                                 53
#define COLOURMAP_GREATER_THAN_256                                54
#define MALLOC_FAILED                                             55
#define IMPOSSIBLE_COUPLING_COEFFICIENT                           56
#define FMAX_NOT_ABOVE_FMIN                                       57
#define IMPOSSIBLE_TO_MAKE_COUPLER_THAT_LENGTH                    58
#define W_OR_H_TOO_SMALL                                          59
#define INVALID_SWITCH                                            60
#define DIMENSION_LESS_THAN_ZERO                                  61
#define PERMITTIVITY_LESS_THAN_1                                  62
#define VARIABLE_NOT_INITIALISED                                  63
#define GAP_BETWEEN_CONDUCTORS_TOO_SMALL                          64
#define VOLTAGE_NOT_MINUS_ONE_V_AS_EXPECTED                       65
#define VOLTAGE_NOT_PLUS_ONE_V_AS_EXPECTED                        66
#define VOLTAGE_NOT_ZERO_V_AS_EXPECTED                            67
#define THREAD_CREATION_FAILED                                  68
#define MUTEX_INITIALISATION_FAILED                               69
#define MUTEX_ALLOCATION_FAILED                                   70
#define USER_REQUESTED_TOO_MANY_THREADS                           71
#define THREAD_FAILED_TO_JOIN                                     71
#define CANT_OBTAIN_SEMAPHORE                                     73
#define SEM_INIT_FAILED                                           74
#define SEM_POST_FAILED                                           75
#define SEM_WAIT_FAILED                                           76
#define PTHREAD_ATTR_SETINHERITSCHED_FAILED                       77
#define PTHREAD_ATTR_INIT_FAILED                                  78 
#define PTHREAD_ATTR_SETSCOPE_FAILED                              79
#define PTHREAD_MUTEX_LOCK_FAILED                                 80
#define PTHREAD_MUTEX_UNLOCK_FAILED                               81
#define PTHREAD_COND_WAIT_FAILED                                  82
#define PTHREAD_COND_BROADCAST_FAILED                             83
#define SILLY_ARGUMENTS_IN_FREE_SCMATRIX                          84
#define MEMORY_ALLOCATION_ERROR_IN_SCMATRIX                       85
#define CANT_READ_ALL_OF_FILE                                     86
#define FSEEK_FAILURE                                             87
#define FTELL_FAILURE                                             88
#define DOMAIN_ERROR                                              89
#define INTERNAL_ERROR                                            90   
