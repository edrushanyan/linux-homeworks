#ifndef PARALLEL_SCHEDULER_H
#define PARALLEL_SCHEDULER_H

#include <functional>
#include <vector>
#include <thread>
#include <queue>
#include <mutex>
#include <condition_variable>

using std::unique_lock;
using std::condition_variable;
using std::mutex;
using std::queue;
using std::vector;
using std::thread;
using std::function;

class parallelScheduler{
private:

    // adding the maximum number of threads allowed in the parallel scheduler
    int capacity;

    // adding a bool for indicating the parallel scheduler should stop processing tasks or not
    bool stop;

    // adding vector of threads
    vector<thread> threads;

    // adding queue of functions
    queue<function<void()>> tasks;

    // adding mutex for providing exclusive access to the queue for thread safety
    mutex taskMutex;

    // adding a condition variable for synchronizating signal changes in the queue
    condition_variable condition;

    void workingThread(){
        while (true) {

            unique_lock<mutex> lock(taskMutex);

            // waiting until stop is true or queue is not empty
            condition.wait(lock, [this]() {return stop || !tasks.empty(); } );

            // ending the loop if stop is true and if queue is empty
            if (stop == true && tasks.empty()) {
                return;
            }

            // moving task from queue to currentTask 
            auto currentTask = move(tasks.front());

            // removing the task that we moved to currentTask
            tasks.pop();

            // unlocking lock object and allowing other threads to access the queue
            lock.unlock();

            // executing the extracted task
            currentTask();
        }
    }

    static void workingThreadWrapper(parallelScheduler* scheduler){
        scheduler->workingThread();
    }

public:
    
    explicit parallelScheduler(int capacity) : capacity(capacity), stop(false){
        
        // creating worker threads
        for(int i = 0; i < capacity; ++i){
            threads.emplace_back(&workingThreadWrapper, this);
        }
    }

    ~parallelScheduler(){
        // using braces to automatically release lock when it goes out of scope
        {
            unique_lock<mutex> lock(taskMutex);
            stop = true;
        }

        // notifying all threads to wake up and check stop condition
        condition.notify_all();

        // joining all worker threads to wait for them to complete
        for(size_t i = 0; i < threads.size(); ++i){
            threads[i].join();
        }
    }

    void run(function<void()> task){
        // using braces to automatically release lock when it goes out of scope
        {
            unique_lock<mutex> lock(taskMutex);

            // adding the task to the queue for execution by the worker threads
            tasks.push(move(task));
        }

        // notifying one thread to wake up and process the added task
        condition.notify_one();
    }
};

#endif 