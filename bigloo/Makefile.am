pkglib_LIBRARIES = libBLRNumber.a

libBLRNumber_a_SOURCES = \
	bl-rnumber.c \
	rnumber_proxy.c

INCLUDES = -I$(BIGLOO_LIBDIR) -I$(top_srcdir)/include

#TESTS = simple_test NumberRegress  RandTest number_test

RNUMBER_STATIC_LIBS = \
	$(top_srcdir)/src/libRNumber.a

LDADD = $(RNUMBER_STATIC_LIBS)

both: libbl-rnumber.a libbl-rnumber.so

libbl-rnumber.a: bl-rnumber.heap rnumber_proxy.o bl-rnumber.o
	ar qvc libbl-rnumber.a bl-rnumber.o rnumber_proxy.o $(RNUMBER_STATIC_LIBS)
	ranlib libbl-rnumber.a

libbl-rnumber.so: libbl-rnumber.a 
	ld -G -o libbl-rnumber.so bl-rnumber.o rnumber_proxy.o $(RNUMBER_STATIC_LIBS)

bl-rnumber.heap: rnumber.scm 
	bigloo -unsafe -q -mkaddheap -mkaddlib make-lib.scm -addheap bl-rnumber.heap

libformat.a:
	ar qvc libformat.a format.o
	ranlib libformat.a

libformat.so:
	ld -G -o libformat.so format.o -lm -lc

libformat_u.a:
	ar qvc libformat_u.a format_u.o
	ranlib libformat_u.a

libformat_u.so:
	ld -G -o libformat_u.so format_u.o -lm -lc

brnumber_u.o: rnumber.scm 
	bigloo -O3 -unsafe -mkaddlib -cc gcc -fsharing -q -rm -unsafev rnumber.scm -o brnumber_u.o -c

brnumber.o: rnumber.scm
	bigloo -O3 -mkaddlib -g -cg -cc gcc -fsharing -q -rm -unsafev rnumber.scm -o brnumber.o -c
