check_PROGRAMS = driver simple-number-test

# Turn off dependency tracking, since Automake doesn't
# know how to handle Bigloo.
AUTOMAKE_OPTIONS=no-dependencies

driver_SOURCES = driver.c
simple_number_test_SOURCES=simple-number-test.c

CLEANFILES = driver.c simple-number-test.c

INCLUDES = -I$(top_srcdir)/include -I$(top_srcdir)/src

TESTS = simple-number-test

RNUMBER_STATIC_LIBS = \
	$(top_srcdir)/src/libRNumber.a

LDADD = $(RNUMBER_STATIC_LIBS)

BIGLOO_C_OPT = -copt "-I ../include"  
BIGLOO_LIB_PATH = -L $(top_srcdir)/src -L $(top_srcdir)/bigloo/src
BIGLOO_LIB_OPTIONS = -lstdc++ -lRNumber -lgcc_s -ldopt "-R $(BIGLOO_LIBDIR)"

% : %.scm
	bigloo -g -cg -v2 $(BIGLOO_C_OPT) $(BIGLOO_LIB_PATH)  -o $@ $< $(BIGLOO_LIB_OPTIONS)

simple-number-test: simple-number-test.scm
number-tests: number-tests.scm
driver: driver.scm

##	bigloo -g -cg -v2 $(BIGLOO_C_OPT) $(BIGLOO_LIB_PATH) +rm -o $@ $< $(BIGLOO_LIB_OPTIONS)
