check_PROGRAMS =  NumberTest

NumberTest_SOURCES = NumberTest.C

EXTRA_DIST = $(TESTS) 

INCLUDES = -I ../src

TESTS = NumberRegress 

RNUMBER_STATIC_LIBS = \
	$(top_srcdir)/src/libRNumber.a

LDADD = $(RNUMBER_STATIC_LIBS)

