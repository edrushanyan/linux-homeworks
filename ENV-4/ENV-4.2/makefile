all: redirect-sin

redirect-sin: redirect-sin.o
	g++ redirect-sin.o -o redirect-sin

redirect-sin.o: redirect-sin.cpp
	g++ redirect-sin.cpp -c

clean:
	rm redirect-sin.o redirect-sin
