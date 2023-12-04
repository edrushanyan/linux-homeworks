all: demo-application

demo-application: demo-application.o parallel_scheduler.so
	g++ demo-application.o -pthread -fpermissive -o demo-application -L. -lparallel_scheduler

demo-application.o: demo-application.cpp parallel_scheduler.so
	g++ demo-application.cpp -c

parallel_scheduler.so: parallel_scheduler.o
	g++ parallel_scheduler.o -pthread -shared -o parallel_scheduler.so

parallel_scheduler.o: parallel_scheduler.cpp parallel_scheduler.h
	g++ parallel_scheduler.cpp -c -fPIC

clean:
	rm *.o *.so demo-application
