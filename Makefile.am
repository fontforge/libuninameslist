# Makefile.am - Top level automakefile for libuninameslist

ACLOCAL_AMFLAGS = -I m4 ${ACLOCAL_FLAGS}

AM_CFLAGS = $(WCFLAGS)
AM_LDFLAGS = $(WCFLAGS) -no-undefined --mode=link

DISTCLEANFILES = libuninameslist.pc
DISTCHECK_CONFIGURE_FLAGS = --enable-oldfrenchlib

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

NamesList.txt:
	$(WGET) "http://www.unicode.org/Public/UNIDATA/NamesList.txt" -O NamesList.txt

ListeDesNoms.txt:
	$(WGET) "http://hapax.qc.ca/ListeDesNoms-5.0.0.txt" -O ListeDesNoms.txt

CLEANFILES = NamesList.txt ListeDesNoms.txt buildnameslist buildnameslist.h

