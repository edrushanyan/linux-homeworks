#ifndef SHARED_ARRAY_H
#define SHARED_ARRAY_H

#include <iostream>

#define PAGE_SIZE 4096

class shared_array{
private:

    // adding pointer to shared array data
    int* data;
    // adding file descriptor to shared memory object
    int shmOpenedFile;
    // size of the shared array
    int size;

public:

    // constructor declaration
    shared_array(const char* name, int size);

    // overloaded subscript operator declaration
    int& operator[](int index);

    // destructor declaration
    ~shared_array();

};

#endif