pkglib_LIBRARIES = libBLRNumber.a

libBLRNumber_a_SOURCES = \
	bl-rnumber.c \
	rnumber_proxy.c

INCLUDES = -I$(BIGLOO_LIBDIR) -I$(top_srcdir)/include

#TESTS = simple_test NumberRegress  RandTest number_test

RNUMBER_STATIC_LIBS = \
	$(top_srcdir)/src/libRNumber.a

LDADD = $(RNUMBER_STATIC_LIBS)

