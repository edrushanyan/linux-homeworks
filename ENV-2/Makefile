all: main

main: main.o complex.o
	g++ main.o complex.o -o main

complex.o: complex.cpp complex.h
	g++ complex.cpp -c

main.o: main.cpp
	g++ main.cpp -c

clean: 
	rm *.o main
