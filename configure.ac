# -*- Autoconf -*-
dnl Process this file with autoconf to produce a configure script.
AC_PREREQ([2.61])
#-------------------------------------------
# PackageTimestamp and Nameslist.txt version
m4_define([uninameslist_package_stamp], [20130501])
m4_define([uninameslist_nameslist_ver], [6.2])
#-------------------------------------------
# Making point releases:
#   uninameslist_major_version += 0;
#   uninameslist_minor_version += 1; (namelist update or added function(s))
#
# If any new functions have been added:
#   uninameslist_major_version += 0;
#   uninameslist_minor_version += 1; (added function(s))
#
# If backwards compatibility has been broken:
#   uninameslist_major_version += 1;
#   uninameslist_minor_version = 0;
#
m4_define([uninameslist_major_version], [0])
m4_define([uninameslist_minor_version], [3])
m4_define([uninameslist_version],
          [uninameslist_major_version.uninameslist_minor_version.uninameslist_package_stamp])
m4_define([uninameslist_info],
          [uninameslist_major_version:uninameslist_minor_version:0])
m4_define([uninameslist_package_name], [libuninameslist])

#-------------------------------------------
# These values below are kept for backwards compatibility with older programs
# that may still be using the older French namesList. This is unnecessary to
# increment unless ListeDesNoms.txt increases from version 5.0 (value=0.3.0).
m4_define([oldfr_major_version], [0])
m4_define([oldfr_minor_version], [3]) dnl latest ListeDesNoms.txt = ver5.0
m4_define([oldfr_info],
          [oldfr_major_version:oldfr_minor_version:0])

#-------------------------------------------
AC_INIT([uninameslist],[uninameslist_version],[fontforge-devel@lists.sourceforge.net],
	[uninameslist_package_name],[https://github.com/fontforge/libuninameslist])
AC_CONFIG_SRCDIR([buildnameslist.c])
AM_INIT_AUTOMAKE([foreign -Wall])
#-------------------------------------------
AC_CONFIG_MACRO_DIR([m4])

#-------------------------------------------
# automake 1.12 seems to require AM_PROG_AR,
# but automake 1.11 doesn't recognize it.
m4_ifdef([AM_PROG_AR], [AM_PROG_AR])

LT_INIT
AC_SUBST(LIBTOOL_DEPS)

AC_PROG_CC
AC_PROG_INSTALL
AC_PROG_LN_S
AC_PROG_MKDIR_P
AC_PROG_MAKE_SET
AC_PROG_SED
AC_PATH_PROGS([WGET],[wget],[wget])

#-------------------------------------------
# Indicate this is a release build and that
# dependancies for changes between Makefile.am
# and Makefile.in should not be checked. This
# makes compiling faster. If you are working
# on the library, run:
# ./configure --enable-maintainer-mode
# to enable the dependancies
dnl AM_MAINTAINER_MODE([enable])

#-------------------------------------------
# Enable silent build rules by default, this
# requires atleast Automake-1.11. Disable by
# either passing --disable-silent-rules to
# configure or passing V=1 to make
m4_ifdef([AM_SILENT_RULES],[AM_SILENT_RULES([yes])],[AC_SUBST([AM_DEFAULT_VERBOSITY],[1])])

#-------------------------------------------
# Include deprecated French library too?
AC_ARG_ENABLE([oldfrenchlib],AS_HELP_STRING([--enable-oldfrenchlib],[This library may be useful for older programs. Currently at ListeDesNoms.txt version 5.0]),
  [case "${enableval}" in
    yes) oldfrenchlib=true ;;
    no)  oldfrenchlib=false ;;
    *) AC_MSG_ERROR([bad value ${enableval} for --enable-oldfrenchlib]) ;;
   esac],[oldfrenchlib=false])
AM_CONDITIONAL([WANTLIBOFR],[test x$oldfrenchlib = xtrue])

#-------------------------------------------
# Platform specific stuff
AC_CANONICAL_HOST
case "$host" in
*-pc-cygwin*)
 AC_DEFINE(__CygWin,1)
 AC_LIBTOOL_WIN32_DLL
 ;;
esac
#-------------------------------------------
# Pass variables to MAKEFILE.AM
AC_SUBST([UN_VERSION],[uninameslist_info])
AC_SUBST([FR_VERSION],[oldfr_info])
#-------------------------------------------
# Check for and add usable compiler warnings
AC_LANG_PUSH([C])
AC_SUBST([WCFLAGS],[])
AX_CHECK_COMPILE_FLAG([-Wall],[WCFLAGS+=" -Wall"])
AX_CHECK_COMPILE_FLAG([-Wextra],[WCFLAGS+=" -Wextra"])
AX_CHECK_COMPILE_FLAG([-Wcast-align],[WCFLAGS+=" -Wcast-align"])
AX_CHECK_COMPILE_FLAG([-Wbad-function-cast],[WCFLAGS+=" -Wbad-function-cast"])
AX_CHECK_COMPILE_FLAG([-Wc++-compat],[WCFLAGS+=" -Wc++-compat"])
AX_CHECK_COMPILE_FLAG([-Wmissing-prototypes],[WCFLAGS+=" -Wmissing-prototypes"])
AX_CHECK_COMPILE_FLAG([-Wunused],[WCFLAGS+=" -Wunused"])
AC_LANG_POP
#-------------------------------------------
echo 'const char NL_VERSION[[]] = "uninameslist_nameslist_ver";' > buildnameslist.h
#-------------------------------------------
AC_PROG_LIBTOOL

AC_CONFIG_FILES([
Makefile
libuninameslist.pc
])

AC_OUTPUT
