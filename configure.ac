#                                               -*- Autoconf -*-
# Process this file with autoconf to produce a configure script.

AC_PREREQ(2.61)
AC_INIT([g2hec-lib], [0.1.4], [Ning Shang <geek@cerias.net>])
AM_INIT_AUTOMAKE
AC_CONFIG_SRCDIR([src/divisor_negate.C])
AC_CONFIG_HEADER([config.h])
AC_CONFIG_MACRO_DIR([m4])

# Checks for programs.
AC_PROG_CC
AC_PROG_CXX
AC_PROG_MAKE_SET
AC_PROG_RANLIB
AC_LANG([C++])

# hack to locate on BSD systems
CPPFLAGS="$CPPFLAGS -I/usr/local/include"
LIBS="$LIBS -L/usr/local/lib"
 
dnl --------------------------------------------------------

# Checks for libraries.
# FIXME: Replace `main' with a function in `-lgmp':
AC_SEARCH_LIBS([__gmpz_init], [gmp])
# FIXME: Replace `main' with a function in `-lm':
AC_SEARCH_LIBS([pow], [m])
# FIXME: Replace `main' with a function in `-lntl':
AC_SEARCH_LIBS([FFT], [ntl])
#AC_SEARCH_LIBS([NTL::FFT], [ntl], [], [have_ntl=no])

# NTL is a must
#if test "x${have_ntl}" = xno; then
#  AC_ARG_WITH([ntl],
#  [AS_HELP_STRING([--with-ntl=<path>], 
#  [prefix of NTL installation, e.g. /usr/local])],
#  [NTL_PREFIX=$with_ntl],
#  [AC_MSG_ERROR([You must call configure with the --with-ntl option.
#  This tells configure where to find the NTL library and headers.
#  e.g. --with-ntl=/usr/local or --with-mysql=/homes/user/local])])

#  AC_SUBST(NTL_PREFIX)
#  NTL_LIBS="-L${NTL_PREFIX}/lib -lntl"
#  NTL_CPPFLAGS="-I${NTL_PREFIX}/include"
#  AC_SUBST(NTL_LIBS)
#  AC_SUBST(NTL_CPPFLAGS)
#fi

# Checks for header files.

# Checks for typedefs, structures, and compiler characteristics.
AC_HEADER_STDBOOL
AC_C_CONST
AC_C_INLINE

# Checks for library functions.

AC_CONFIG_FILES([Makefile
                 src/Makefile
                 doc/Makefile])

AC_OUTPUT
