# -*- Autoconf -*-
dnl Process this file with autoconf to produce a configure script.
AC_PREREQ([2.64])
#-------------------------------------------
# PackageTimestamp, major version, minor version, and Nameslist.txt version
# Libraries have a "package" version of the form major.minor.micro.
m4_define([uninameslist_package_stamp], [20170807]) dnl yyyymmdd
m4_define([uninameslist_major_version], [10]) dnl Nameslist.txt
m4_define([uninameslist_minor_version], [0])
m4_define([uninameslist_nameslist_ver], [uninameslist_major_version.uninameslist_minor_version])
# Libraries have a "libtool" version of the form current:revision:age.
m4_define([uninameslist_current], [1])
m4_define([uninameslist_revision],[2])
m4_define([uninameslist_age],     [0])
m4_define([uninameslist_libver],
          [uninameslist_current:uninameslist_revision:uninameslist_age])

# These values below are kept for backwards compatibility with older programs
# that are using the French namesList. This increments with ListeDesNoms.txt.
m4_define([fr_major_version], [10]) dnl latest ListeDesNoms.txt = ver10.0
m4_define([fr_minor_version], [0])
m4_define([uninameslist_fr_nameslist_ver], [fr_major_version.fr_minor_version])
m4_define([uninameslist_fr_current], [1])
m4_define([uninameslist_fr_revision],[1])
m4_define([uninameslist_fr_age],     [0])
m4_define([uninameslist_fr_libver],
          [uninameslist_fr_current:uninameslist_fr_revision:uninameslist_fr_age])

#-------------------------------------------
#
# To update the libtool version, which should be set independently of the
# library's major and minor version, execute the following steps.
#
# 1. If the code has changed at all (e.g., a namelist update):
#
#      uninameslist_revision += 1
#
# 2. If any interfaces have been added, removed, or changed (e.g., a new
#    function has been added):
#
#      uninameslist_current += 1
#      uninameslist_revision = 0
#
# 3. If any interfaces have been added:
#
#      uninameslist_age += 1
#
# 4. If any interfaces have been removed or changed (i.e., the backwards
#    compatibility has been broken):
#
#      uninameslist_age = 0
#
m4_define([uninameslist_package_name], [libuninameslist])

#-------------------------------------------
AC_INIT([uninameslist],[uninameslist_package_stamp],[fontforge-devel@lists.sourceforge.net],
	[uninameslist_package_name],[https://github.com/fontforge/libuninameslist])
AC_CONFIG_SRCDIR([buildnameslist.c])
AM_INIT_AUTOMAKE([foreign -Wall])
#-------------------------------------------
AC_CONFIG_MACRO_DIR([m4])
AC_CANONICAL_HOST
AC_CANONICAL_BUILD

#-------------------------------------------
# automake 1.12 seems to require AM_PROG_AR,
# but automake 1.11 doesn't recognize it.
m4_ifdef([AM_PROG_AR], [AM_PROG_AR])

LT_INIT
AC_SUBST([LIBTOOL_DEPS])

# Check building environment
AC_PROG_CC
AC_PROG_LN_S
AC_PROG_MKDIR_P
AC_PROG_MAKE_SET
AC_PROG_SED
AC_CHECK_TOOL([WGET],[wget],[:])
AC_CHECK_TOOL([STRIP],[strip],[:])
AC_PROG_INSTALL

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
AC_ARG_ENABLE([frenchlib],AS_HELP_STRING([--enable-frenchlib],[This library may be useful for French programs. Currently at ListeDesNoms.txt version ${uninameslist_fr_nameslist_ver}]),
  [case "${enableval}" in
    yes) frenchlib=true ;;
    no)  frenchlib=false ;;
    *) AC_MSG_ERROR([bad value ${enableval} for --enable-frenchlib]) ;;
   esac],[frenchlib=false])
AM_CONDITIONAL([WANTLIBOFR],[test x$frenchlib = xtrue])

#-------------------------------------------
# Platform specific stuff, AC_CANONICAL_HOST
case "$host" in
*-pc-cygwin*)
 AC_DEFINE(__CygWin,1)
 AC_LIBTOOL_WIN32_DLL
 ;;
esac

#-------------------------------------------
# Compiler and Linker flags to override auto
# detection and insertion. Use CFLAGS if you
# want to add more in addition to autodetect
AC_ARG_VAR([UN_CFLAGS],[C compiler flags for libuninameslist, overriding automatic detection])
AC_ARG_VAR([UN_LIB],[Linker flags for libuninameslist, overriding automatic detection])

#-------------------------------------------
# Check for and add usable compiler warnings
# Skip if using UNINAMESLIST_CFLAGS instead.
WCFLAGS=""
AC_LANG_PUSH([C])
AX_CHECK_COMPILE_FLAG([-Wall],[WCFLAGS="$WCFLAGS -Wall"])
AX_CHECK_COMPILE_FLAG([-Wextra],[WCFLAGS="$WCFLAGS -Wextra"])
AX_CHECK_COMPILE_FLAG([-Wconversion],[WCFLAGS="$WCFLAGS -Wconversion"])
AX_CHECK_COMPILE_FLAG([-Wsign-conversion],[WCFLAGS="$WCFLAGS -Wsign-conversion"])
AX_CHECK_COMPILE_FLAG([-Wcast-align],[WCFLAGS="$WCFLAGS -Wcast-align"])
AX_CHECK_COMPILE_FLAG([-Wformat=2],[WCFLAGS="$WCFLAGS -Wformat=2"])
AX_CHECK_COMPILE_FLAG([-Wformat-security],[WCFLAGS="$WCFLAGS -Wformat-security"])
AX_CHECK_COMPILE_FLAG([-fno-common],[WCFLAGS="$WCFLAGS -fno-common"])
AX_CHECK_COMPILE_FLAG([-Wbad-function-cast],[WCFLAGS="$WCFLAGS -Wbad-function-cast"])
AX_CHECK_COMPILE_FLAG([-Wc++-compat],[WCFLAGS="$WCFLAGS -Wc++-compat"])
AX_CHECK_COMPILE_FLAG([-Wmissing-prototypes],[WCFLAGS="$WCFLAGS -Wmissing-prototypes"])
AX_CHECK_COMPILE_FLAG([-Wmissing-declarations],[WCFLAGS="$WCFLAGS -Wmissing-declarations"])
AX_CHECK_COMPILE_FLAG([-Wstrict-prototypes],[WCFLAGS="$WCFLAGS -Wstrict-prototypes"])
AX_CHECK_COMPILE_FLAG([-Wunused],[WCFLAGS="$WCFLAGS -Wunused"])

dnl currently for extra testing
dnl   AX_CHECK_COMPILE_FLAG([-fPIC],[WCFLAGS="$WCFLAGS -fPIC"])
dnl   AX_CHECK_COMPILE_FLAG([-Wstrict-overflow],[WCFLAGS="$WCFLAGS -Wstrict-overflow"])
dnl   AX_CHECK_COMPILE_FLAG([-Wpointer-arith],[WCFLAGS="$WCFLAGS -Wpointer-arith"])
dnl   AX_CHECK_COMPILE_FLAG([-Wcast-qual],[WCFLAGS="$WCFLAGS -Wcast-qual"])
dnl   AX_CHECK_COMPILE_FLAG([-Wcast-align],[WCFLAGS="$WCFLAGS -Wcast-align"])
dnl   AX_CHECK_COMPILE_FLAG([-Wpadded],[WCFLAGS="$WCFLAGS -Wpadded"])
dnl   AX_CHECK_COMPILE_FLAG([-Woverlength-strings],[WCFLAGS="$WCFLAGS -Woverlength-strings"])

dnl reduce exported symbol list for dynamic library
dnl AX_CHECK_COMPILE_FLAG([-fvisibility=hidden],[WCFLAGS="$WCFLAGS -fvisibility=hidden"])
dnl AX_CHECK_COMPILE_FLAG([-fvisibility-inlines-hidden],[WCFLAGS="$WCFLAGS -fvisibility-inlines-hidden"])
AC_LANG_POP

# Skip if replacing with UN_LIB instead.
WUNLIB=""
if test -z $UN_LIB ; then
   WUNLIB="${WCFLAGS}"
fi
if test "${UN_CFLAGS}"x != x; then
   WCFLAGS=""
fi

#-------------------------------------------
# Pass some definitions to buildnameslist.c
echo 'const char NL_VERSION[[]] = "uninameslist_nameslist_ver";' > buildnameslist.h
echo 'const char NFR_VERSION[[]] = "uninameslist_fr_nameslist_ver";' >> buildnameslist.h
AC_DEFINE([LU_VERSION_MJ],[uninameslist_current])
AC_DEFINE([LU_VERSION_MN],[uninameslist_revision])
AC_DEFINE([LFR_VERSION_MJ],[uninameslist_fr_current])
AC_DEFINE([LFR_VERSION_MN],[uninameslist_fr_revision])

#-------------------------------------------
# Pass variables to build libuninameslist.pc
uninameslist_libs="-luninameslist"
dnl if test x"${frenchlib}" = xtrue; then
dnl   uninameslist_libs="${uninameslist_libs} -luninameslist-fr"
dnl fi
AC_SUBST([LIBUNINAMESLIST_PKGCONFIG_LIBS],["${uninameslist_libs}"])

#-------------------------------------------
# Pass variables to MAKEFILE.AM
AC_SUBST([UN_VERSION],[uninameslist_libver])
AC_SUBST([FR_VERSION],[uninameslist_fr_libver])
AC_SUBST([NL_VERSION],[uninameslist_nameslist_ver])
AC_SUBST([NFR_VERSION],[uninameslist_fr_nameslist_ver])
AC_SUBST([UN_CFLAGS])
AC_SUBST([UN_LIB])
AC_SUBST([WCFLAGS])
AC_SUBST([WUNLIB])

#-------------------------------------------
AC_PROG_LIBTOOL

AC_CONFIG_FILES([
Makefile
tests/Makefile
libuninameslist.pc
])

AC_OUTPUT

AC_MSG_NOTICE([

Configuration:
  Source code location	${srcdir}
  Build code location	${builddir}
  Destination prefix	${prefix}
  Compiler		${CC}
  Config auto WCFLAGS	"${WCFLAGS}"
  Config auto WUNLIB	"${WUNLIB}"
  Config CFLAGS		"${CFLAGS}"
  Config LDFLAGS	"${LDFLAGS}"
  Config UN_CFLAGS	"${UN_CFLAGS}"
  Config UN_LIB		"${UN_LIB}"

])
