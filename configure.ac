#                                               -*- Autoconf -*-
# Process this file with autoconf to produce a configure script.

AC_PREREQ([2.69])
AC_INIT([simpleHelloGA], [1.0], [minterciso@gmail.com])
AM_INIT_AUTOMAKE
AC_CONFIG_SRCDIR([src/main.c])
AC_CONFIG_HEADERS([config.h])

# Checks for programs.
AC_PROG_CC

# Checks for libraries.

# Checks for header files.
AC_CHECK_HEADERS([stdlib.h string.h])

# Checks for typedefs, structures, and compiler characteristics.

# Checks for library functions.
AC_FUNC_MALLOC
AC_CHECK_FUNCS([memset])
AC_CHECK_PROG([GNUPLOT],[gnuplot], [yes])
AS_IF([test "x$GNUPLOT" = xyes], [AC_DEFINE([HAVE_GNUPLOT], [1], [gnuplot available])])
AC_OUTPUT(src/Makefile Makefile)
