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
    // checking if we added the files.
    if(argc < 3){
        std::cerr << "Add file." << endl;
        exit(1);
    }

    char* sourceFile = argv[1];
    char* destinationFile = argv[2];

    int openSourceFile = open(sourceFile, O_RDONLY);

    if(openSourceFile < 0){
        std::cerr << strerror(errno) << endl;
        exit(errno);
    }

    int openDestinationFile = open(destinationFile, O_CREAT | O_TRUNC | O_WRONLY);

    if(openDestinationFile < 0){
        std::cerr << strerror(errno) << endl;
        exit(errno);
    }

    char buffer[bufferSize];

    off_t dataCopied = 0, holeCopied = 0;

    while(true){
        off_t currenOffset = lseek(openSourceFile, 0, SEEK_CUR);

        int readBytes = read(openSourceFile, buffer, bufferSize);

        if(readBytes < 0){
            std::cerr << strerror(errno) << endl;
            exit(errno);
        }

        if(readBytes == 0){
            break;
        }

        int newOffset = lseek(openSourceFile, 0, SEEK_CUR);

        holeCopied += newOffset - currenOffset - readBytes;

        dataCopied += readBytes;

        int writeBytes = write(openDestinationFile, buffer, readBytes);

        if(writeBytes < 0){
            std::cerr << strerror(errno) << endl;
            exit(errno);
        }
    }

    int closeSourceFile = close(openSourceFile);

    if(closeSourceFile < 0){
        std::cerr << strerror(errno) << endl;
        exit(errno);
    }

    int closeDestinationFile = close(openDestinationFile);

    if(closeDestinationFile < 0){
        std::cerr << strerror(errno) << endl;
        exit(errno);
    }

    std::cout << "Successfully copied " << dataCopied + holeCopied << " bytes (data: " << dataCopied << " hole: " << holeCopied << ")" << endl;

    return 0;
}