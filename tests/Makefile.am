check_PROGRAMS =  NumberTest RandTest number_test 

# randtest

NumberTest_SOURCES = NumberTest.C
RandTest_SOURCES = RandTest.C
number_test_SOURCES = c-io.C number_test.c
# randtest_SOURCES = randtest.c

EXTRA_DIST = $(TESTS) 

INCLUDES = -I ../src

TESTS = NumberRegress  RandTest number_test

RNUMBER_STATIC_LIBS = \
	$(top_srcdir)/src/libRNumber.a

LDADD = $(RNUMBER_STATIC_LIBS)

