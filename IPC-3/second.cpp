#include <iostream>
#include "shared_array.h"
#include <fcntl.h>
#include <sys/stat.h>
#include <semaphore.h>
#include <errno.h>
#include <string.h>
#include <unistd.h>

#define N 1000

using std::endl;

int main(){

    // creating shared array object
    shared_array shmArr("my_array", N);

    // creating semaphore for synchronization between processes
    sem_t* mySem = sem_open("/rndmfd", O_RDWR);

    // checking if theres any error
    if(mySem == SEM_FAILED){
        std::cerr << strerror(errno) << endl;
    }

    // infinity proccess
    while(true){

        sem_wait(mySem);

        for(int i = 0; i < N; ++i){
            std::cout << shmArr[i] << ", ";
        }

        sem_post(mySem);

        usleep(100000);

    }

    // closing semaphore
    sem_close(mySem);
    sem_unlink("/rndmfd");

    return 0;
}