SHELL = /bin/sh

ACLOCAL_AMFLAGS = -I m4

AM_CFLAGS = $(WCFLAGS)
AM_LDFLAGS = $(WCFLAGS) -no-undefined --mode=link

lib_LTLIBRARIES = libuninameslist.la
if WANTLIBOFR
lib_LTLIBRARIES += libuninameslist-fr.la
endif

libuninameslist_la_LDFLAGS = -version-info $(UN_VERSION)
libuninameslist_la_SOURCES = nameslist.c
libuninameslist_la.$(OBJEXT): uninameslist.h

if WANTLIBOFR
libuninameslist_fr_la_LDFLAGS = -version-info $(FR_VERSION)
libuninameslist_fr_la_SOURCES = nameslist-fr.c
libuninameslist_fr_la.$(OBJEXT): uninameslist.h
endif

EXTRA_PROGRAMS = buildnameslist
buildnameslist_SOURCES = buildnameslist.c
nodist_EXTRA_DATA = NamesList.txt ListeDesNoms.txt

include_HEADERS = nameslist.h

NamesList.txt:
	$(WGET) "http://www.unicode.org/Public/UNIDATA/NamesList.txt" -O NamesList.txt

ListeDesNoms.txt:
	$(WGET) "http://hapax.qc.ca/ListeDesNoms-5.0.0.txt" -O ListeDesNoms.txt

CLEANFILES = NamesList.txt ListeDesNoms.txt buildnameslist
