
default: main clean

main: GPXDataUnit.o debug.o main.o
	g++ -o main GPXDataUnit.o debug.o main.o

debug.o: debug/debug.c
	g++ -o debug.o -c debug/debug.c

GPXDataUnit.o: GPXDataUnit.cpp
	g++ -o GPXDataUnit.o -c GPXDataUnit.cpp

main.o: main.cpp GPXDataUnit.h debug/debug.h
	gcc -o main.o -c main.cpp

clean:
	rm -f *.o