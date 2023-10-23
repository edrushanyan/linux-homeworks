all: hacker-rm

hacker-rm: hacker-rm.o
	g++ hacker-rm.o  -o hacker-rm

hacker-rm.o: hacker-rm.cpp
	g++ hacker-rm.cpp -c

clean:
	rm hacker-rm.o hacker-rm
