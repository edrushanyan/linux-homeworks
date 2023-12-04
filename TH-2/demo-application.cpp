#include <iostream>
#include "parallel_scheduler.h"

using std::endl;

void exampleTask(int task){
    std::cout << task << endl;
}

int main(){

    // creating the parallel scheduler with 5 threads capacity
    parallelScheduler scheduler(5);

    // creating const that we will use in our loop
    const int n = 10;

    // enqueue tasks to the thread pool
    for(int i = 0; i < n; ++i){
        scheduler.run([i]() { exampleTask(i); });
    }

    return 0;
}