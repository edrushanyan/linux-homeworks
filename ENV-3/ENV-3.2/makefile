all: simple-copy

simple-copy: simple-copy.o
	g++ simple-copy.o -o simple-copy

simple-copy.o: simple-copy.cpp
	g++ simple-copy.cpp -c

clean:
	rm simple-copy.o simple-copy
