pkglib_LIBRARIES = libbl-rnumber_s.a libbl-rnumber_u.a
# libbl-rnumber.so

SUBDIRS = rnumber

EXTRA_DIST = $(bigloo_DATA)
CLEANFILES = bl-rnumber.heap 
BUILT_SOURCES = bl-rnumber.heap

bigloodir = $(pkglibdir)
bigloo_DATA = bl-rnumber.init bl-rnumber.heap 

libbl_rnumber_s_a_SOURCES =  bl-rnumber.c rnumber.scm rnumber_proxy.c
libbl_rnumber_u_a_SOURCES =  bl-rnumber.c rnumber.scm rnumber_proxy.c

noinst_HEADERS = \
	bl-rnumber.h 

INCLUDES = -I$(BIGLOO_LIBDIR) -I$(top_srcdir)/include

RNUMBER_STATIC_LIBS = \
	$(top_srcdir)/src/libRNumber.a

LDADD = $(RNUMBER_STATIC_LIBS)

BIGLOO_O_OPTIONS_OPT   = -c -v2 -O3 -mkaddlib -cc gcc -fsharing -q -unsafe -unsafev -c
BIGLOO_O_OPTIONS_DEBUG = -c -v2     -mkaddlib -g4 -cg -cc gcc -fsharing -q -rm
BIGLOO_O_OPTIONS = $(BIGLOO_O_OPTIONS_OPT)

BIGLOO_HEAP_OPTIONS_OPT = -unsafe -q -mkaddheap -mkaddlib 
BIGLOO_HEAP_OPTIONS_DEBUG = -q -mkaddheap -mkaddlib 
BIGLOO_HEAP_OPTIONS = $(BIGLOO_HEAP_OPTIONS_OPT)

%_u.o:%.scm
	bigloo $(BIGLOO_O_OPTIONS_OPT)  $< -o $@

all: libbl-rnumber_s.a  libbl-rnumber_u.a 
# libbl-rnumber_s.so libbl-rnumber_u.so

libbl-rnumber_s.a: bl-rnumber.heap rnumber_proxy.o bl-rnumber.o brnumber_s.o 
	ar qvc libbl-rnumber_s.a bl-rnumber.o brnumber_s.o rnumber_proxy.o $(RNUMBER_STATIC_LIBS)
	ranlib libbl-rnumber_s.a

libbl-rnumber_u.a: bl-rnumber.heap rnumber_proxy.o bl-rnumber.o brnumber_u.o 
	ar qvc libbl-rnumber_u.a bl-rnumber.o brnumber_u.o rnumber_proxy.o $(RNUMBER_STATIC_LIBS)
	ranlib libbl-rnumber_u.a

libbl-rnumber_s.so: libbl-rnumber_s.a bl-rnumber.o 
	ld -G -o libbl-rnumber_s.so bl-rnumber.o brnumber_s.o rnumber_proxy.o $(RNUMBER_STATIC_LIBS)

libbl-rnumber_u.so: libbl-rnumber_u.a bl-rnumber.o 
	ld -G -o libbl-rnumber_u.so bl-rnumber.o brnumber_u.o rnumber_proxy.o $(RNUMBER_STATIC_LIBS)

# the -addheap option is anylogous to the -o option of compiling.
bl-rnumber.heap: rnumber.scm make-lib.scm
	bigloo $(BIGLOO_HEAP_OPTIONS) make-lib.scm -addheap bl-rnumber.heap

brnumber_u.o: rnumber.scm 
	bigloo $(BIGLOO_O_OPTIONS_OPT)  rnumber.scm -o brnumber_u.o

brnumber_s.o: rnumber.scm 
	bigloo $(BIGLOO_O_OPTIONS_DEBUG) rnumber.scm -o brnumber_s.o 

