check_PROGRAMS =  simple_test NumberTest RandTest number_test  driver 

# randtest

NumberTest_SOURCES = NumberTest.C
RandTest_SOURCES = RandTest.C
number_test_SOURCES = c-io.C number_test.c
simple_test_SOURCES = simple_test.c c-io.C
# randtest_SOURCES = randtest.c
driver_SOURCES = driver.scm

EXTRA_DIST = $(TESTS) 

#INCLUDES = -I$(top_srcdir)/include -I$(top_srcdir)/src
INCLUDES = -I$(top_srcdir)/include -I$(top_srcdir)/src

TESTS = number-tests.scm simple_test NumberRegress  RandTest number_test

RNUMBER_STATIC_LIBS = \
	$(top_srcdir)/src/libRNumber.a

LDADD = $(RNUMBER_STATIC_LIBS)

number-tests: number-tests.scm
	bigloo -g -cg -v2 -copt "-I ../include" -L ../src -L ../bigloo/ -rm -o number-tests number-tests.scm -lstdc++ -lRNumber

driver: driver.scm
	bigloo -g -cg -v2 -copt "-I ../include" -L ../src -L ../bigloo/ -rm -o driver driver.scm -lstdc++ -lRNumber
