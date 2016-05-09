# Makefile.am - Top level automakefile for libuninameslist

ACLOCAL_AMFLAGS = -I m4 $(ACLOCAL_FLAGS)

AM_CFLAGS = $(WCFLAGS) $(UN_CFLAGS)
AM_LDFLAGS = $(WUNLIB) $(UN_LIB) -no-undefined

LIBTOOL_DEPS = @LIBTOOL_DEPS@

DISTCLEANFILES = libuninameslist.pc
DISTCHECK_CONFIGURE_FLAGS = --enable-frenchlib

lib_LTLIBRARIES = libuninameslist.la
if WANTLIBOFR
lib_LTLIBRARIES += libuninameslist-fr.la
endif

libuninameslist_la_LDFLAGS = $(AM_LDFLAGS) -version-info $(UN_VERSION)
libuninameslist_la_SOURCES = nameslist.c
libuninameslist_la.$(OBJEXT): nameslist.h

if WANTLIBOFR
libuninameslist_fr_la_LDFLAGS = $(AM_LDFLAGS) -version-info $(FR_VERSION)
libuninameslist_fr_la_SOURCES = nameslist-fr.c
libuninameslist_fr_la.$(OBJEXT): nameslist-fr.h
endif

EXTRA_DIST = LICENSE README.md
EXTRA_PROGRAMS = buildnameslist
buildnameslist_SOURCES = buildnameslist.c
noinst_PROGRAMS = buildnameslist
nodist_EXTRA_DATA = NamesList.txt ListeDesNoms.txt

include_HEADERS = uninameslist.h
if WANTLIBOFR
include_HEADERS += uninameslist-fr.h
endif

pkgconfigdir = $(libdir)/pkgconfig
pkgconfig_DATA = libuninameslist.pc

libtool: $(LIBTOOL_DEPS)
	$(SHELL) ./config.status libtool

NamesList.txt:
	$(WGET) "http://www.unicode.org/Public/9.0.0/ucd/NamesList-9.0.0d6.txt" -O NamesList.txt

ListeDesNoms.txt:
	$(WGET) "http://hapax.qc.ca/ListeDesNoms-7.0(2014-06-22).txt" -O ListeDesNoms.latin1
	iconv -f latin1 ListeDesNoms.latin1 -o ListeDesNoms.txt

CLEANFILES = NamesList.txt ListeDesNoms.latin1 ListeDesNoms.txt buildnameslist buildnameslist.h

