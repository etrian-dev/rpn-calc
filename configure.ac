#                                               -*- Autoconf -*-
# Process this file with autoconf to produce a configure script.

AC_PREREQ([2.69])
AC_INIT([RPN Calculator], [1.0], [nicola.vetrini@gmail.com], [], [])
AM_INIT_AUTOMAKE([-Wall -Werror foreign])
AC_COPYRIGHT([Feel free to experiment with this little toy program as you like])
AC_CONFIG_SRCDIR([src/main.c])
# Checks for programs.
AC_PROG_CC
# Checks for libraries.
AC_SEARCH_LIBS([readline], [readline],
    [], [AC_MSG_ERROR([unable to find the readline() function])]
)
AC_SEARCH_LIBS([pow], [m],
    [], [AC_MSG_ERROR([unable to find the pow() function])]
)
# Checks for header files.
AC_CHECK_HEADERS([stdio.h stdlib.h math.h])
# Checks for typedefs, structures, and compiler characteristics.

# Checks for library functions.
AC_FUNC_MALLOC
AC_CHECK_FUNCS([pow])
# Makefiles to be generated
AC_CONFIG_FILES([
                 Makefile
                 src/Makefile
])
AC_OUTPUT
