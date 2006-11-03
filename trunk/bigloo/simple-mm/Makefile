BFLAGS          = -v -rm
CFLAGS	 	= -I. -I /usr/local/lib/bigloo/2.5a/
BIGLOO = bigloo

simple: b-simple.o simple.o simple_proxy.o
	$(BIGLOO) $(BFLAGS) -o simple b-simple.o simple.o simple_proxy.o -lstdc++

b-simple.o: simple.o b-simple.scm
	$(BIGLOO) $(BFLAGS) b-simple.scm -c -o b-simple.o

simple_proxy.o: simple_proxy.h simple_proxy.c
	gcc $(CFLAGS) -c -o simple_proxy.o simple_proxy.c

simple.o: simple.C
	g++ $(CFLAGS) -c -o simple.o simple.C

clean:
	rm -f *.o *~
