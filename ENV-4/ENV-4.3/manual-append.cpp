#include <iostream>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <errno.h>
#include <string.h>
#include <unistd.h>

#define Size 13

using std::endl;

int main(int argc, char** argv) {
    // Checking if the file was added.
    if(argc < 2) {
        std::cerr << "No file." << endl;
        exit(1);
    }
    // Assigning by file our file.
    char* file = argv[1];

    // Opening out file and checking if something went wrong while opening it.
    int firstFile = open(file, O_WRONLY | O_CREAT | O_TRUNC, S_IRUSR | S_IWUSR | S_IRGRP | S_IROTH);
    if(firstFile < 0) {
        std::cerr << strerror(errno) << endl;
        exit(errno);
    }

    // Creating lines that we need to write in future.
    char firstLine[] = "First line.\n", secondLine[] = "Second line.\n";

    // Writing the first line and checking if something went wrong while writing.
    int writeBytes = write(firstFile, firstLine, Size);

    if(writeBytes < 0){
        std::cerr << strerror(errno) << endl;
        exit(errno);
    }    
    // Duplicating our file and checking if something went wrong while duplicating.
    int secondFile = dup(firstFile);
    
    if(secondFile < 0) {
        std::cerr << strerror(errno) << endl;
        exit(errno);
    }

    // Wrint the second line and checking if something went wrong while writing.
    writeBytes = write(secondFile, secondLine, Size + 1);
    
    if(writeBytes < 0){
        std::cerr << strerror(errno) << endl;
        exit(errno);
    }

    // Closing the first file and checking if somethin went wrong while closing. 
    int closeFile = close(firstFile);
    
    if(closeFile < 0){
        std::cerr << strerror(errno) << endl;
        exit(errno);
    }

    // Closing duplicated file and checking if somethin went wrong while closing.
    int closeDup = close(secondFile);

    if(closeDup < 0){
        std::cerr << strerror(errno) << endl;
        exit(errno);
    }

    return 0;
}