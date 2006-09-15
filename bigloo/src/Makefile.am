pkglib_LIBRARIES = libbl-rnumber_s-@BIGLOO_REVISION@.a libbl-rnumber_u-@BIGLOO_REVISION@.a
# libbl-rnumber.so

SUBDIRS = rnumber

CLEANFILES = bl-rnumber.heap brnumber_s.c
BUILT_SOURCES = bl-rnumber.heap
EXTRA_DIST = make-lib.scm

bigloodir = $(pkglibdir)
bigloo_DATA = bl-rnumber.init bl-rnumber.heap 

libbl_rnumber_s_@BIGLOO_REVISION@_a_SOURCES =  bl-rnumber.c rnumber.scm rnumber_proxy.c
libbl_rnumber_u_@BIGLOO_REVISION@_a_SOURCES =  bl-rnumber.c rnumber.scm rnumber_proxy.c

noinst_HEADERS = \
	bl-rnumber.h 

INCLUDES = -I$(BIGLOO_LIBDIR) -I$(top_srcdir)/include

RNUMBER_STATIC_LIBS = \
	$(top_builddir)/src/.libs/libRNumber.a

LDADD = $(RNUMBER_STATIC_LIBS)

BGL_CC = -cc gcc
BIGLOO_O_OPTIONS_OPT   = -c -O3 -mkaddlib         $(BGL_CC) -fsharing -q -unsafe -unsafev
BIGLOO_O_OPTIONS_DEBUG = -c     -mkaddlib -g4 -cg $(BGL_CC) -fsharing -q
BIGLOO_O_OPTIONS = $(BIGLOO_O_OPTIONS_OPT)

BIGLOO_HEAP_OPTIONS_OPT = -unsafe -q -mkaddheap -mkaddlib 
BIGLOO_HEAP_OPTIONS_DEBUG = -q -mkaddheap -mkaddlib 
BIGLOO_HEAP_OPTIONS = -heap-library rnumber $(BIGLOO_HEAP_OPTIONS_OPT) -I $(srcdir)

CFLAGS += -DBIGLOO_SYSPUTC_LEVEL=@BIGLOO_SYSPUTC@

%_u.o:%.scm
	bigloo $(BIGLOO_O_OPTIONS_OPT)  $< -o $@

all: libbl-rnumber_s-$(BIGLOO_REVISION).a  libbl-rnumber_u-$(BIGLOO_REVISION).a 
# libbl-rnumber_s.so libbl-rnumber_u.so

libbl-rnumber_s-@BIGLOO_REVISION@.a: bl-rnumber.heap rnumber_proxy.o bl-rnumber.o brnumber_s.o 
	ar qvc $@ bl-rnumber.o brnumber_s.o rnumber_proxy.o $(RNUMBER_STATIC_LIBS)
	ranlib $@

libbl-rnumber_u-@BIGLOO_REVISION@.a: bl-rnumber.heap rnumber_proxy.o bl-rnumber.o brnumber_u.o 
	ar qvc $@ bl-rnumber.o brnumber_u.o rnumber_proxy.o $(RNUMBER_STATIC_LIBS)
	ranlib $@

libbl-rnumber_s-@BIGLOO_REVISION@.so: libbl-rnumber_s-$(BIGLOO_REVISION).a bl-rnumber.o 
	ld -G -o $@ bl-rnumber.o brnumber_s.o rnumber_proxy.o $(RNUMBER_STATIC_LIBS)

libbl-rnumber_u-@BIGLOO_REVISION@.so: libbl-rnumber_u-$(BIGLOO_REVISION).a bl-rnumber.o 
	ld -G -o $@ bl-rnumber.o brnumber_u.o rnumber_proxy.o $(RNUMBER_STATIC_LIBS)

# the -addheap option is anylogous to the -o option of compiling.
bl-rnumber.heap: $(srcdir)/make-lib.scm $(srcdir)/rnumber.scm
	bigloo $(BIGLOO_HEAP_OPTIONS) $< -addheap $@

brnumber_u.o: $(srcdir)/rnumber.scm 
	bigloo $(BIGLOO_O_OPTIONS_OPT)  $< -o $@

brnumber_s.o: $(srcdir)/rnumber.scm 
	bigloo $(BIGLOO_O_OPTIONS_DEBUG) $< -o $@ 

