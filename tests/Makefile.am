check_PROGRAMS =  simple_test NumberTest RandTest number_test 

# randtest

NumberTest_SOURCES = NumberTest.C
RandTest_SOURCES = RandTest.C
number_test_SOURCES = c-io.C number_test.c
simple_test_SOURCES = simple_test.c c-io.C
# randtest_SOURCES = randtest.c

EXTRA_DIST = $(TESTS) 

INCLUDES = -I$(top_srcdir)/include -I$(top_srcdir)/src

TESTS = simple_test NumberRegress  RandTest number_test

RNUMBER_STATIC_LIBS = \
	$(top_srcdir)/src/libRNumber.a

LDADD = $(RNUMBER_STATIC_LIBS)

