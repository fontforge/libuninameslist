# Common CPPFLAGS
AM_CPPFLAGS = -I$(top_srcdir) -I$(top_builddir)

AM_CFLAGS = -I$(top_srcdir) -I$(top_builddir) $(DEP_CFLAGS) $(BABL_CFLAGS) -lm

DEPS = $(top_builddir)/.libs/libuninameslist.la

LDADDS = $(top_builddir)/.libs/libuninameslist.la

# The tests
noinst_PROGRAMS = call-test0 call-test1 call-test2

call_test0_SOURCES = call-test0.c
call_test0_LDADD = $(LDADDS)

call_test1_SOURCES = call-test1.c
call_test1_LDADD = $(LDADDS)

call_test2_SOURCES = call-test2.c
call_test2_LDADD = $(LDADDS)

TESTS = $(noinst_PROGRAMS)
