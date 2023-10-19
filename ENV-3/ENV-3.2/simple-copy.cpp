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
    if(argc < 3){
        std::cerr << "No file." << endl;
        exit(1);
    }

    // Assigning by file our source file.
    char* file = argv[1];

    // Opening the file.
    int openFile = open(file, O_RDONLY, S_IRUSR | S_IWUSR | S_IROTH | S_IRGRP);
    
    // Checking if the file is opened or no.
    if(openFile < 0){
        std::cerr << strerror(errno) << endl;
        exit(errno);
    }

    // Assinging by newFile our destination file.
    char* newFile = argv[2];

    // Opening newFile.
    int openNewFile = open(newFile, O_WRONLY | O_CREAT | O_TRUNC, S_IRUSR | S_IWUSR | S_IROTH | S_IRGRP);

    // Checking if the newFile is opened or no.
    if(openNewFile < 0){
        std::cerr << strerror(errno) << endl;
        exit(errno);
    }    
    
    // Creating a buffer. Using given size + 1 for '/0' character.
    char buffer[bufferSize + 1];
    
    while(true) {
        // Reading the source file.
        ssize_t readBytes = read(openFile, buffer, bufferSize);

        // Checking if there's an error while reading the source file.
        if(readBytes < 0){
            std::cerr << strerror(errno) << endl;
            exit(errno);
        }
        //if readBytes is there's no data to read.
        if(readBytes == 0){
            break;
        }
        // Writing in the destination file.
        ssize_t writeBytes = write(openNewFile, buffer, readBytes); 

        // Checking if there's an error while writing the destination file.
        if(writeBytes < 0){
            std::cerr << strerror(errno) << endl;
            exit(errno);
        }
    }
    // Closing source and destination files.
    int closeFile = close(openFile);
    int closeNewFile = close(openNewFile);
    // Checking if the source file is closed.
    if(closeFile < 0){
        std::cerr << strerror(errno) << endl;
        exit(errno);   
    }
    // Checking if the destination file is closed.
    if(closeNewFile < 0){
        std::cerr << strerror(errno) << endl;
        exit(errno);
    }

    std::cout << "Copying file completed." << endl;

    return 0;
}