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
    // Checking if we added a file.
    if(argc < 2){
        std::cerr << "No file." << endl;
        exit(1);
    }
    // Assigning by file our file.
    char* file = argv[1];

    // Opening our file.
    int openFile = open(file, O_WRONLY | O_TRUNC);

    // Checking if the file opened correctly.
    if(openFile < 0){
        std::cerr << strerror(errno) << endl;
        exit(errno);
    }
    // Creating stat struct for keeping our file information.
    struct stat statbf;
    
    // Geting the size of file.
    int fileSize = statbf.st_size;
    
    // Creating a buffer with our defined size and filling it wiht '\0'.
    char buffer[bufferSize];

    for(int i = 0; i < bufferSize; ++i){
        buffer[i] = '\0';
    }
    // Creating int for keeping count of writen bytes.
    int writenBytesCount = 0;
    
    while(true){
        // writing our file.
        ssize_t writeBytes = write(openFile, buffer, fileSize);
        // Checking if something went wrong while writing file.
        if(writeBytes < 0){
                    std::cerr << strerror(errno) << endl;
            exit(errno);
        }
        
        // Breaking the cycle if there's nothing to write.
        if(writeBytes == 0){
            break;
        }

        // adding to our counter writen bytes and checking if it's still bigger then size of the file.
        writenBytesCount += writeBytes;
        if(writenBytesCount >= fileSize){
            break;
        }
    }

    //Closing the file.
    int closeFile = close(openFile);
    // Checking if something went wrong while closing the file.
    if(closeFile < 0){
        std::cerr << strerror(errno) << endl;
        exit(errno);
    }
    // Unlinking file.
    int unlinkFile = unlink(file);

    return 0;
}


