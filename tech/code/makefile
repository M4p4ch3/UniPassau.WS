
default: main clean

main: GPXDataUnit.o main.o
	g++ -o main GPXDataUnit.o main.o

GPXDataUnit.o: GPXDataUnit.cpp
	g++ -o GPXDataUnit.o -c GPXDataUnit.cpp

main.o: main.cpp GPXDataUnit.h
	gcc -o main.o -c main.cpp

clean:
	rm -f *.o