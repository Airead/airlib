#                                               -*- Autoconf -*-
# Process this file with autoconf to produce a configure script.

AC_PREREQ([2.68])
AC_INIT([airlib], [0.0.1], [fgh1987168@gmail.com])
AC_CONFIG_SRCDIR([include/list.h])
AC_CONFIG_HEADERS([config.h])

AM_INIT_AUTOMAKE(airlib, 0.0.1)

CFLAGS="-g -O0 -Wall"
# Checks for programs.
AC_PROG_CC

# Checks for libraries.
AC_PROG_RANLIB

# Checks for header files.
AC_CHECK_HEADERS([limits.h stddef.h stdlib.h string.h sys/time.h unistd.h])

# Checks for typedefs, structures, and compiler characteristics.
AC_C_INLINE

# Checks for library functions.
AC_FUNC_MALLOC
AC_CHECK_FUNCS([gettimeofday memset strdup strerror strtol])

AC_CONFIG_FILES([Makefile
                 src/Makefile
                 test/Makefile])
AC_OUTPUT
