#include <iostream>
#include <errno.h>
#include <string.h>
#include <cstdlib>
#include <chrono>
#include <vector>
#include <pthread.h>

using std::vector;
using namespace std::chrono;
using std::endl;

// creating thread struct for saving our sum for every thread
struct Thread{

    int start, end;
    long long sum;

};

// creating void* function which counting the sum(we use this function for pthread_creaate)
void* sumOfThread(void* arg){
    
    // we cast the void pointer argument to a thread pointer
    Thread* thread = static_cast<Thread*>(arg);

    // making the sum of current thread 0
    thread->sum = 0;

    // making loop that increments thread's sum by adding the current index value
    for(int i = thread->start; i < thread->end; ++i){
        thread->sum += i;
    }

    return NULL;
}


int main(int argc, char** argv){

    // checking if we added all the arguments
    if(argc < 3){
        std::cerr << strerror(errno) << endl;
        exit(errno);
    }

    // creating N & M ang giving them values(using std::atoi function which change arguments to int)
    int N = std::atoi(argv[1]);
    int M = std::atoi(argv[2]);

    // creating array and initializing it with random values
    int arr[N];
    for(int i = 0; i < N; ++i){
        arr[i] = rand();
    }

    // without threads case
    // getting the start timepoint  
    auto start = high_resolution_clock::now();
    // creating and computing the sum
    long long sumWithoutThreads = 0;
    for(int i = 0; i < N; ++i){
        sumWithoutThreads += arr[i];
    }

    // getting the end timepoint
    auto end = high_resolution_clock::now();

    // getting the duration and printing it
    auto duration = duration_cast<microseconds>(end - start);

    std::cout << "Time spent without threads: " << duration.count() << endl;

    // with threads case
    // creating vectors for computation
    vector<Thread> threadData(M);
    vector<pthread_t> threads(M);

    long long sumWithThreads = 0;

    // getting the start timepoint
    auto startForThreads = high_resolution_clock::now();

    // creating temp that we going to use for getting equal portions
    int temp = 0;

    // loop for creating threads and giving them portions
    for(int i = 0; i < M; ++i){

        // giving current thread the start index
        threadData[i].start = temp;
        
        // giving end index based on equal portions
        if(i < (N % M)){
            threadData[i].end = temp + (N / M) + 1;
        }

        else{
            threadData[i].end = temp + (N / M);
        }

        // creating thread
        int threadResult = pthread_create(&threads[i], NULL, sumOfThread, &threadData[i]);

        // checking for error
        if(threadResult != 0){
            std::cerr << strerror(errno) << endl;
            exit(errno);
        }

        // updating the temp for the next thread
        temp = threadData[i].end;
    }

    // joining threads
    for(int i = 0; i < M; ++i){
        int threadJoinResult = pthread_join(threads[i], NULL);
        
        // checking for errors
        if(threadJoinResult != 0){
            std::cerr << strerror(errno) << endl;
            exit(errno);
        }
    }

    // accumulating the sums calculated by each thread
    for(int i = 0; i < M; ++i){
            sumWithThreads += threadData[i].sum;
        }

    // getting the end timepoint
    auto endForThreads = high_resolution_clock::now();

    // counting the duration and printing it 
    auto durationForThreads = duration_cast<milliseconds>(endForThreads - startForThreads);
    
    std::cout << "Time spent with threads: " << durationForThreads.count() << endl;

    return 0;
}