check_PROGRAMS = driver simple-number-test check-number-test

# Turn off dependency tracking, since Automake doesn't
# know how to handle Bigloo.
AUTOMAKE_OPTIONS = no-dependencies serial-tests no-exeext

driver_SOURCES = driver.scm
simple_number_test_SOURCES = simple-number-test.scm
check_number_test_SOURCES = check-number-test.scm

EXTRA_DIST = simple-number-test.golden
CLEANFILES = driver.c simple-number-test.c check-number-test.c *.out

AM_CPPFLAGS = -I$(top_srcdir)/include -I$(top_srcdir)/src

TESTS = simple-number-test \
	check-number-test

RNUMBER_STATIC_LIBS = $(top_srcdir)/src/.libs/libRNumber.a

LDADD = $(RNUMBER_STATIC_LIBS)

BIGLOO_C_OPT = -copt "-I ../include"  
BIGLOO_LIB_PATH = -L $(top_builddir)/src/.libs -L $(top_builddir)/bigloo/src \
	-L $(top_srcdir)/bigloo/src

BIGLOO_LIB_OPTIONS = -lstdc++ $(BIGLOO_GCC3X) -ldopt "-Wl,-R$(BIGLOO_LIBDIR) \
	-Wl,-R$(top_builddir)/src/.libs" -L $(BIGLOO_LIBDIR)

BIGLOO = bigloo -c -g -cg -library bl-rnumber $(BIGLOO_C_OPT) -o $@ $(BIGLOO_LIB_PATH)

BIGLOO_LINK = $(BIGLOO) $< $(BIGLOO_LIB_OPTIONS)

%.o : %.scm
	$(BIGLOO) $< 

% : %.o
	$(BIGLOO_LINK)

simple-number-test: simple-number-test.scm
check-number-test: check-number-test.scm
number-tests: number-tests.scm
driver: driver.scm

