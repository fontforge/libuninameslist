# Makefile.am - Top level automakefile for libuninameslist

SUBDIRS = . tests
man_MANS = libuninameslist.3
if PSWRAP
SUBDIRS += py
endif
DIST_SUBDIRS = . py tests

test_programs = call-test0 call-test1 call-test2
if WANTLIBOFR
test_programs += call-test3 call-test4 call-test5
endif
test_programs += call-test6

# The braces around ACLOCAL_FLAGS below instead of parentheses are intentional!
# Otherwise autoreconf misparses the line.
ACLOCAL_AMFLAGS = -I m4 ${ACLOCAL_FLAGS}

AM_CFLAGS = $(WCFLAGS) $(UN_CFLAGS)
AM_LDFLAGS = $(WUNLIB) $(UN_LIB) -no-undefined

LIBTOOL_DEPS = @LIBTOOL_DEPS@

EXTRA_DIST = LICENSE README.md m4/ax_check_compile_flag.m4 tests/call-test.c \
	py/setup.py py/uninameslist.py libuninameslist.3
EXTRA_PROGRAMS = buildnameslist
buildnameslist_SOURCES = buildnameslist.c
noinst_PROGRAMS = buildnameslist
nodist_EXTRA_DATA = NamesList.txt ListeDesNoms.txt .git/*

DISTCLEANFILES = libuninameslist.pc
DISTCHECK_CONFIGURE_FLAGS = --enable-frenchlib --disable-pscript

lib_LTLIBRARIES = libuninameslist.la
if WANTLIBOFR
lib_LTLIBRARIES += libuninameslist-fr.la
endif

libuninameslist_la_LDFLAGS = $(AM_LDFLAGS) -version-info $(UN_VERSION)
libuninameslist_la_SOURCES = nameslist.c
libuninameslist_la.$(OBJEXT): uninameslist.h nameslist-dll.h

if WANTLIBOFR
libuninameslist_fr_la_LDFLAGS = $(AM_LDFLAGS) -version-info $(FR_VERSION)
libuninameslist_fr_la_SOURCES = nameslist-fr.c
libuninameslist_fr_la.$(OBJEXT): uninameslist-fr.h nameslist-dll.h
man_MANS += libuninameslist-fr.3
else
EXTRA_DIST += nameslist-fr.c uninameslist-fr.h libuninameslist-fr.3
endif

include_HEADERS = uninameslist.h
if WANTLIBOFR
include_HEADERS += uninameslist-fr.h
endif
noinst_HEADERS = nameslist-dll.h

pkgconfigdir = $(libdir)/pkgconfig
pkgconfig_DATA = libuninameslist.pc

libtool: $(LIBTOOL_DEPS)
	$(SHELL) ./config.status libtool

NamesList.txt:
	$(WGET) "http://www.unicode.org/Public/11.0.0/ucd/NamesList-11.0.0d5.txt" -O NamesList.txt

ListeDesNoms.txt:
	$(WGET) "http://hapax.qc.ca/ListeNoms-10.0.0-20170716.txt" -O ListeDesNoms.txt

# test: run all tests in cwd and subdirs
test:	$(TEST_PROGS)

.PHONY: test
# run make test as part of make check
check-local: test

CLEANFILES = NamesList.txt ListeDesNoms.latin1 ListeDesNoms.txt buildnameslist buildnameslist.h

