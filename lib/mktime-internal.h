/* mktime variant that also uses an offset guess

   Copyright 2016-2019 Free Software Foundation, Inc.

   This program is free software; you can redistribute it and/or
   modify it under the terms of the GNU General Public
   License as published by the Free Software Foundation; either
   version 3 of the License, or (at your option) any later version.

   This program is distributed in the hope that it will be useful,
   but WITHOUT ANY WARRANTY; without even the implied warranty of
   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
   General Public License for more details.

   You should have received a copy of the GNU General Public
   License along with this program; if not, see
   <https://www.gnu.org/licenses/>.  */

#include <time.h>

/* mktime_offset_t is a signed type wide enough to hold a UTC offset
   in seconds, and used as part of the type of the offset-guess
   argument to mktime_internal.  Use time_t on platforms where time_t
   is signed, to be compatible with platforms like BeOS that export
   this implementation detail of mktime.  On platforms where time_t is
   unsigned, GNU and POSIX code can assume 'int' is at least 32 bits
   which is wide enough for a UTC offset.  */

#if TIME_T_IS_SIGNED
typedef time_t mktime_offset_t;
#else
typedef int mktime_offset_t;
#endif

time_t mktime_internal (struct tm *,
                        struct tm * (*) (time_t const *, struct tm *),
                        mktime_offset_t *);

/* Although glibc source code uses leading underscores, Gnulib wants
   ordinary names.

   Portable standalone applications should supply a <time.h> that
   declares a POSIX-compliant localtime_r, for the benefit of older
   implementations that lack localtime_r or have a nonstandard one.
   Similarly for gmtime_r.  See the gnulib time_r module for one way
   to implement this.  */

#undef __gmtime_r
#undef __localtime_r
#define __gmtime_r gmtime_r
#define __localtime_r localtime_r

#define __mktime_internal mktime_internal
