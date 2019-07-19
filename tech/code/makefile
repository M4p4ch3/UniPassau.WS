
default: main clean

main: main.o GPXData.o Stats.o debug.o
	g++ -o main GPXData.o Stats.o debug.o main.o

main.o:
	gcc -o main.o -c main.cpp -Idebug -IGPXData -IStats

GPXData.o:
	g++ -o GPXData.o -c GPXData/GPXData.cpp -Idebug

Stats.o:
	g++ -o Stats.o -c Stats/Stats.cpp

debug.o:
	g++ -o debug.o -c debug/debug.c

clean:
	rm -f *.o