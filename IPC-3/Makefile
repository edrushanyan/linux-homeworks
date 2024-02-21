shared_array.o: shared_array.cpp
	g++ shared_array.cpp -c

first: first.o shared_array.o
	g++ first.o shared_array.o -lpthread -lrt -o first

first.o: first.cpp
	g++ first.cpp -c

second: second.o shared_array.o
	g++ second.o shared_array.o -lpthread -lrt -o second

clean:
	rm *.o first second
