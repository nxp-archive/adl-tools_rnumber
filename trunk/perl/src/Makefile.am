
perllibdir=$(pkglibdir)

noinst_DATA = example.so 

perllib_DATA = RNumber.so RNumber.pm rnumber.pm

EXTRA_DIST = example.i example.c RNumber.i RNumber.c rnumber.pm  rnumber_test2.pl

CLEANFILES = $(EXAMPLE_CLEANFILES) $(PL_RNUMBER_CLEANFILES) 

EXAMPLE_CLEANFILES = example.o example_wrap.o example_wrap.c example_wrap.o example.so example_wrap.doc RNumber.so example.pm

PL_RNUMBER_CLEANFILES = pl_rnumber.pm pl_rnumber_wrap.c pl_rnumber_wrap.o pl_rnumber.so RNumber.pm RNumber_wrap.c RNumber.o RNumber_wrap.o

#PERL_INC=-I/usr/local/lib/perl5/sun4-solaris/5.00404/CORE
#PERL_INC=-I/local/tdukes/lib/perl5/5.00503/sun4-solaris/CORE
#PERL_INC=-I/usr/lib/perl5/5.8.0/i386-linux-thread-multi/CORE/

RNUMBER_LIB = $(top_builddir)/src/.libs/libRNumber.a
STD_CPP_LIB = -lstdc++

TESTS = rnumber_test2.pl

%.o:%.c
	gcc -c $^ $(PERL_ARCH_INCL) $(PERL_CC_FLAGS)

example_wrap.c example.pm : example.i example.c
	swig -perl5 -o $@ $<

example.so : example.o example_wrap.o 
	g++ -shared $^ -o $@

RNumber_wrap.c RNumber.pm : RNumber.i 
	swig -perl5 -o $@ -shadow $<

RNumber.so : RNumber_wrap.o RNumber.o $(RNUMBER_LIB)	
	g++ -shared $^ -o $@ 
