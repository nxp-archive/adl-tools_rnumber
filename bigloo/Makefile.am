pkglib_LIBRARIES = libbl-rnumber.a
# libbl-rnumber.so
pkginclude_HEADERS = rnumber_proxy.h

EXTRA_DIST = $(bigloo_DATA)
CLEANFILES = bl-rnumber.heap 
BUILT_SOURCES = bl-rnumber.heap

bigloodir = $(pkglibdir)
bigloo_DATA = bl-rnumber.init bl-rnumber.heap 

libbl_rnumber_a_SOURCES =  bl-rnumber.c rnumber.scm rnumber_proxy.c
#libbl_rnumber_so_SOURCES = bl-rnumber.c rnumber.scm  rnumber_proxy.c

#noinst_HEADERS = \
#	rnumber_exceptions.h 

INCLUDES = -I$(BIGLOO_LIBDIR) -I$(top_srcdir)/include

#TESTS = simple_test NumberRegress  RandTest number_test

RNUMBER_STATIC_LIBS = \
	$(top_srcdir)/src/libRNumber.a

LDADD = $(RNUMBER_STATIC_LIBS)

both: libbl-rnumber.a libbl-rnumber.so

libbl-rnumber.a: bl-rnumber.heap rnumber_proxy.o bl-rnumber.o brnumber.o 
	ar qvc libbl-rnumber.a bl-rnumber.o brnumber.o rnumber_proxy.o $(RNUMBER_STATIC_LIBS)
	ranlib libbl-rnumber.a

libbl-rnumber.so: libbl-rnumber.a brnumber.o 
	ld -G -o libbl-rnumber.so bl-rnumber.o brnumber.o rnumber_proxy.o $(RNUMBER_STATIC_LIBS)

bl-rnumber.heap: rnumber.scm 
	bigloo -unsafe -q -mkaddheap -mkaddlib make-lib.scm -addheap bl-rnumber.heap

brnumber_u.o: rnumber.scm 
	bigloo -O3 -unsafe -mkaddlib -cc gcc -fsharing -q +rm -unsafev rnumber.scm -o brnumber_u.o -c

brnumber.o: rnumber.scm
	bigloo -v2 -O3 -mkaddlib -g -cg -cc gcc -fsharing -q -rm -unsafe rnumber.scm -o brnumber.o -c

evprim_u.o: evprim.scm
	bigloo -O3 -mkaddlib -g -cg -cc gcc -fsharing -q -rm +unsafev evprim.scm -o evprim_u.o -c

evprim.o: evprim.scm
	bigloo -v2 -O3 -mkaddlib -g -cg -cc gcc -fsharing -q -rm -unsafe evprim.scm -o evprim.o -c
