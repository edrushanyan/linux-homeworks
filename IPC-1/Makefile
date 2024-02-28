all: signal-echo

signal-echo: signal-echo.o
	g++ signal-echo.o -o signal-echo

signal-echo.o: signal-echo.cpp
	g++ signal-echo.cpp -c

clean:
	rm *.o signal-echo
