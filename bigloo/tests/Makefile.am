check_PROGRAMS = simple_test number_test driver

number_test_SOURCES = c-io.C number_test.c
simple_test_SOURCES = simple_test.c c-io.C
driver_SOURCES = driver.scm

CLEANFILES = driver.c 
EXTRA_DIST = $(TESTS) 

INCLUDES = -I$(top_srcdir)/include -I$(top_srcdir)/src

TESTS = simple_test number_test 

RNUMBER_STATIC_LIBS = \
	$(top_srcdir)/src/libRNumber.a

LDADD = $(RNUMBER_STATIC_LIBS)

BIGLOO_C_OPT = -copt "-I ../include"  
BIGLOO_LIB_PATH = -L $(top_srcdir)/src -L $(top_srcdir)/bigloo/src
BIGLOO_LIB_OPTIONS = -lstdc++ -lRNumber

% : %.scm
	bigloo -g -cg -v2 $(BIGLOO_C_OPT) $(BIGLOO_LIB_PATH) +rm -o $@ $< $(BIGLOO_LIB_OPTIONS)

simple-number-test: simple-number-test.scm
number-tests: number-tests.scm

driver: driver.scm
	bigloo -g -cg -v2 $(BIGLOO_C_OPT) $(BIGLOO_LIB_PATH) +rm -o $@ $< $(BIGLOO_LIB_OPTIONS)
