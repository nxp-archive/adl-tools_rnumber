check_PROGRAMS = NumberTest ReadTest RandTest ShiftTest simple_test number_test 

NumberTest_SOURCES = NumberTest.C
RandTest_SOURCES = RandTest.C
ShiftTest_SOURCES = ShiftTest.C
ReadTest_SOURCES = ReadTest.C
number_test_SOURCES = c-io.C number_test.c
simple_test_SOURCES = simple_test.c c-io.C

noinst_HEADERS = c-io.h

INCLUDES = -I$(top_srcdir)/include -I$(top_srcdir)/src -I$(top_srcdir)/tests

TESTSCRIPTS = NumberRegress ReadRegress 
TESTS = $(TESTSCRIPTS) RandTest ShiftTest simple_test number_test 

EXTRA_DIST = $(TESTSCRIPTS) ReadIn.txt ReadOut.regress

LDADD = $(top_builddir)/src/libRNumber.la

#bigloo_tests = simple_test number_test driver
#EXTRA_PROGRAMS = simple_test number_test driver
#number_test_SOURCES = c-io.C number_test.scm
#simple_test_SOURCES = simple_test.scm c-io.C
#driver_SOURCES = driver.scm
#CLEANFILES = driver.c 

#BIGLOO_C_OPT = -copt "-I ../include"  
#BIGLOO_LIB_PATH = -L ../src -L ../bigloo
#BIGLOO_LIB_OPTIONS = -lstdc++ -lRNumber

#% : %.scm
#	bigloo -g -cg -v2 $(BIGLOO_C_OPT) $(BIGLOO_LIB_PATH) +rm -o $@ $< $(BIGLOO_LIB_OPTIONS)

#simple-number-test: simple-number-test.scm
#number-tests: number-tests.scm

#driver: driver.scm
#	bigloo -g -cg -v2 $(BIGLOO_C_OPT) $(BIGLOO_LIB_PATH) +rm -o $@ $< $(BIGLOO_LIB_OPTIONS)

cinstall:
	$(MAKE) install
