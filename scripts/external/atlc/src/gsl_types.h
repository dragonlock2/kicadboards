/*
atlc - arbitrary transmission line calculator, for the analysis of
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

Dr. David Kirkby, e-mail drkirkby@gmail.com 

This is haevily hacked from the gsl_types.h file which is copyright

* Copyright (C) 2001 Brian Gough
and for part of the GNU Scientific library (gsl).

It is not identical and only contrains a subset of the information 
from that file and is hacked somewhat. 

*/


#ifndef __GSL_TYPES_H__
#define __GSL_TYPES_H__

#ifndef GSL_VAR

#ifdef WIN32
#  ifdef _DLL
#    ifdef DLL_EXPORT
#      define GSL_VAR __declspec(dllexport)
#    else
#      define GSL_VAR __declspec(dllimport)
#    endif
#  else
#    define GSL_VAR extern
#  endif
#else
#  define GSL_VAR extern
#endif

#endif

#endif /* __GSL_TYPES_H__ */
