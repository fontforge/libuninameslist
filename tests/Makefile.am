# Common CPPFLAGS
AM_CPPFLAGS = -I$(top_srcdir) -I$(top_builddir)

AM_CFLAGS = -I$(top_srcdir) -I$(top_builddir) $(DEP_CFLAGS) $(BABL_CFLAGS) -lm

DEPS = $(top_builddir)/.libs/libuninameslist.la

LDADDS = $(top_builddir)/.libs/libuninameslist.la

# The tests
noinst_PROGRAMS = call-test
call_test_SOURCES = call-test.c
call_test_LDADD = $(LDADDS)

TESTS = $(noinst_PROGRAMS)
