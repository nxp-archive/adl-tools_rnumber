
example.pm example_wrap.c: example.i example.c
	swig -perl5 example.i

example.so : example.o example_wrap.o 
	gcc -shared example.o example_wrap.o -o example.so

