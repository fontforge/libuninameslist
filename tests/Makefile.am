# Common CPPFLAGS
AM_CPPFLAGS = -I$(top_srcdir) -I$(top_builddir)

AM_CFLAGS = -I$(top_srcdir) -I$(top_builddir) $(DEP_CFLAGS) $(BABL_CFLAGS) -lm

#DEPS = $(top_builddir)/libuninameslist.la

EXTRA_DIST = call-test.c

LDADDS = $(top_builddir)/libuninameslist.la

# The tests
noinst_PROGRAMS = call-test0 call-test1 call-test2

call_test0_SOURCES = call-test0.c
call_test0_LDADD = $(LDADDS)

call_test1_SOURCES = call-test1.c
call_test1_LDADD = $(LDADDS)

call_test2_SOURCES = call-test2.c
call_test2_LDADD = $(LDADDS)

if WANTLIBOFR
LDADDF = $(top_builddir)/libuninameslist-fr.la

call_test3_SOURCES = call-test3.c
call_test3_LDADD = $(LDADDF)

call_test4_SOURCES = call-test4.c
call_test4_LDADD = $(LDADDF)

call_test5_SOURCES = call-test5.c
call_test5_LDADD = $(LDADDS) $(LDADDF)

call_test7_SOURCES = call-test7.c
call_test7_LDADD = $(LDADDS)

noinst_PROGRAMS += call-test3 call-test4 call-test5 call-test6 call-test7
else
noinst_PROGRAMS += call-test6
EXTRA_DIST += call-test3.c call-test4.c call-test5.c call-test7.c
endif

call_test6_SOURCES = call-test6.c
call_test6_LDADD = $(LDADDS)

TESTS = $(noinst_PROGRAMS)

-include $(top_srcdir)/git.mk
