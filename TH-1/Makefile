all: array-summery

array-summery: array-summery.o
	g++ array-summery.o -pthread -o array-summery

array-summery.o: array-summery.cpp
	g++ array-summery.cpp -c

clean:
	rm *.o array-summery
