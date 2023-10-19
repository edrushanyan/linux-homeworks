#include <iostream>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <errno.h>
#include <string.h>
#include <unistd.h>

#define bufferSize 64

using std::endl;

int main(int argc, char** argv){
    // Checking if the file exist or no. 
    if(argc < 2){
        std::cerr << "No file." << endl;
        exit(1);
    }

    // Assigning by file our text file.
    char* file = argv[1];

    // Opening the file.
    int openFile = open(file, O_RDONLY, S_IRUSR | S_IWUSR | S_IROTH | S_IRGRP);
    
    // Checking if the file is opened or no.
    if(openFile < 0){
        std::cerr << strerror(errno) << endl;
        exit(errno);
    }
    
    // Creating a buffer. Using given size + 1 for '/0' character.
    char buffer[bufferSize + 1];
    
    while(true) {
        // Reading the file.
        ssize_t readBytes = read(openFile, buffer, bufferSize);

        // Checking if there's an error while reading the file.
        if(readBytes < 0){
            std::cerr << strerror(errno) << endl;
            exit(errno);
        }
        //if readBytes is there's no data to read.
        if(readBytes == 0){
            break;
        }

        // Printing read bytes.
        buffer[readBytes] = '\0';
        std::cout << buffer;
    }
    // Closing opened file.
    int closeFile = close(openFile);
    
    // Checking if the file closed.
    if(closeFile < 0){
        std::cerr << strerror(errno) << endl;
        exit(errno);   
    }

    return 0;
}