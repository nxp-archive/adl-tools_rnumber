
perllibdir=$(pkglibdir)

noinst_DATA = example.so 

perllib_DATA = pl_rnumber.so pl_rnumber.pm  rnumber.pm

CLEANFILES = $(EXAMPLE_CLEANFILES) $(PL_RNUMBER_CLEANFILES) 

EXAMPLE_CLEANFILES = example.o example_wrap.o example_wrap.c example_wrap.o example.so example_wrap.doc

PL_RNUMBER_CLEANFILES = pl_rnumber.pm pl_rnumber_wrap.c pl_rnumber_wrap.o pl_rnumber.so

PERL_INC=-I/local/tdukes/lib/perl5/5.00503/sun4-solaris/CORE

RNUMBER_LIB = $(top_srcdir)/src/libRNumber.a
STD_CPP_LIB = -lstdc++

TESTS = rnumber_test2.pl

%.o:%.c
	gcc -c $^ -o $@ $(PERL_INC)

example.pm example_wrap.c: example.i example.c
	swig -perl5 example.i

example.so : example.o example_wrap.o 
	g++ -shared example.o example_wrap.o -o example.so 

pl_rnumber.pm pl_rnumber_wrap.c: pl_rnumber.i 
	swig -perl5 pl_rnumber.i

pl_rnumber.so : pl_rnumber_wrap.o pl_rnumber.o $(RNUMBER_LIB)	
	g++ -shared $^ -o $@ 
