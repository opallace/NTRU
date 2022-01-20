all: main

main: aux.o poly.o ntru.o
	gcc main.c -o main aux.o poly.o ntru.o -lm

aux.o: aux.c aux.h
	gcc -c aux.c

poly.o: poly.c poly.h
	gcc -c poly.c -lm

ntru.o: ntru.c ntru.h
	gcc -c ntru.c

clean:
	rm -rf *.o *~ main
