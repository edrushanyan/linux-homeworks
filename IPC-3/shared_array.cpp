#include "shared_array.h" 
#include <sys/mman.h> 
#include <sys/stat.h>
#include <fcntl.h>
#include <errno.h>
#include <string.h>
#include <unistd.h> 
#include <string> 

using std::endl; 
using std::string; 

// constructor for the shared_array class
shared_array::shared_array(const char* name, int size){

    // assigning the size of the shared array
    this->size = size; 

    // converting size to string
    string sizeString = std::to_string(size);

    // combining name and size to create a unique identifier for the shared memory segment
    string nameAndSize = name + sizeString;

    // converting the combined string to a C-style string
    const char* uniqueName = nameAndSize.c_str();

    // opening the shared memory segment
    shmOpenedFile = shm_open(uniqueName, O_CREAT | O_RDWR, S_IWRITE | S_IREAD);

    // checking if theres any error
    if(shmOpenedFile < 0){
        std::cerr << strerror(errno) << endl; 
        exit(errno); 
    }

    // mapping the shared memory segment
    data = (int*)mmap(NULL, size * sizeof(int), PROT_READ | PROT_WRITE, MAP_SHARED, shmOpenedFile, 0);

    // checking if theres any error
    if(data == (int*)-1){
        std::cerr << strerror(errno) << endl; 
        exit(errno);
    }

}

// overloading [] operator
int& shared_array::operator[](int index){

    // checking if the index is out of bounds
    if(index < 0 || index >= size){
        std::cerr << strerror(errno) << endl; 
        exit(errno);
    }

    // returning a reference to the element at the specified index
    return data[index]; 
}

// destructor for the shared_array class
shared_array::~shared_array(){

    // unmapping the shared memory
    int unmapFile = munmap(data, size * sizeof(int));

    // checking if theres any error
    if(unmapFile == -1){
        std::cerr << strerror(errno) << endl; 
        exit(errno); 
    }

    // closing the shared file descriptor
    int closeSharedFile = close(shmOpenedFile);
    
    // checking if theres any error
    if(closeSharedFile == -1){
        std::cerr << strerror(errno) << endl; 
        exit(errno); 
    }
}
