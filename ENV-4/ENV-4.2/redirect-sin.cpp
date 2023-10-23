#include <iostream>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <errno.h>
#include <string.h>

using std::endl;
using std::string;

// Initialize function.
bool initialize(int argc, char** argv){
    // Checking if file was added.
    if(argc < 2){
        std::cerr << "No file." << endl;
        return false;
    }

    // Assigning by file our file.
    char* file = argv[1];

    // Opening our file.
    int openFile = open(file, O_RDONLY | O_WRONLY);
    
    // Checking if file opened correctly.
    if(openFile < 0){
        std::cerr << strerror(errno) << endl; 
        return false;
    }

    return true;
}

// Reverse string function.
string reverseString(string str){
    // Reversing string and returning it.    
    string reversed(str.rbegin(), str.rend());
    return reversed;
}


int main(int argc, char**  argv){
    // Calling our initialize function and checking the result.
    bool check = initialize(argc, argv);
    if(check == false){
        exit(1);
    }
    // Reading the string.
    string input;
    std::cin >> input;

    // Calling our string reversing function.
    string reversed = reverseString(input);

    // Printing reversed string.
    std::cout << reversed << endl;

    return 0;
}