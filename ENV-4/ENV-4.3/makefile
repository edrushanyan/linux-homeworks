all: manual-append

manual-append: manual-append.o
	g++ manual-append.o -o manual-append

manual-append.o: manual-append.cpp
	g++ manual-append.cpp -c

clean:
	rm manual-append.o manual-append
