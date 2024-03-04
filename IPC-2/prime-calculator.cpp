#include <iostream>
#include <fcntl.h>
#include <unistd.h>
#include <sys/types.h>
#include <cstring>
#include <errno.h>
#include <sys/wait.h>
#include <string>

using std::string;
using std::endl;

// bool function that check if number is prime or not
bool isPrime(int num){
    
    if(num <= 1){
        return false;
    }

    for(int i = 2; i <= num / 2; ++i){

        if(num % i == 0){
            return false;
        }
    }

    return true;
}

// function that finds m-th prime number
int findMthPrime(int m) {

    int count = 0;
    int num = 1;

    while (count != m) {
        
        ++num;
        
        if (isPrime(num)) {

            ++count;
        }
    }

    return num;
}


int main(){

    // creating array to store file descriptors for parent-to-child pipe
    int pipefd1[2];

    // creating array to store file descriptors for child-to-parent pipe
    int pipefd2[2];

    // creating parent-to-child pipe
    int pipeResult1 = pipe(pipefd1);

    // checking if there's any error
    if(pipeResult1 == -1){
        std::cerr << strerror(errno) << endl;
        exit(errno);
    }

    // creating child-to-parent pipe
    int pipeResult2 = pipe(pipefd2);

    // checking if there's any error
    if(pipeResult2 == -1){
        std::cerr << strerror(errno) << endl;
        exit(errno);
    }

    // creating child process
    int pid = fork();

    // checking if there's any error
    if(pid == -1){
        std::cerr << strerror(errno) << endl;
        exit(errno);
    }

    // parent process
    if(pid > 0){

        // close read end of parent-to-child pipe
        close(pipefd1[0]);
        
        // close write end of child-to-parent pipe
        close(pipefd2[1]);

        string input;

        // endless loop
        while(true){

            std::cout << "[Parent] Please enter the number: ";
            std::cin >> input;
        
            // stopping main process's execution
            if(input == "exit"){
                break;
            }
        
            // convert string to int
            int m = std::stoi(input);

            std::cout << "[Parent] Sending " << m << " to child process..." << endl;

            // write m to parent-to-child pipe
            int writeToPipe = write(pipefd1[1], &m, sizeof(m));

            // checking if there's any error
            if(writeToPipe == -1){
                std::cerr << strerror(errno) << endl;
                exit(errno);
            }

            std::cout << "[Parent] Waiting for the response from the child process..." << endl;

            // creating result int to store result
            int result;

            // read calculation result from child-to-parent pipe
            int readResult = read(pipefd2[0], &result, sizeof(result));

            // checking if there's any error
            if(readResult == -1){
                std::cerr << strerror(errno) << endl;
                exit(errno);
            }


            std::cout << "[Parent] Received calculation result of prime(" << m << ") = " << result << "..." << endl;
        }
    }

    // child process
    if(pid == 0){

        // close write end of parent-to-child pipe
        close(pipefd1[1]);
        // close read end of child-to-parent pipe
        close(pipefd2[0]);

        // creating int to store input number
        int m;

        // endless loop
        while(true){

            // read m from parent-to-child pipe
            int readFromPipe = read(pipefd1[0], &m, sizeof(m));

            // checking if there's any error
            if(readFromPipe == -1){
                std::cerr << strerror(errno) << endl;
                exit(errno);
            } 

            std::cout << "[Child] Calculating " << m << "-th prime number..." << endl;
            
            // creating int that stores m-th prime number
            int result = findMthPrime(m);

            std::cout << "[Child] Sending calculation result of prime(" << m << ")...";

            // write calculation result to child-to-parent pipe
            int writeResultToPipe = write(pipefd2[1], &result, sizeof(result)); 

            // checking if there's any error
            if(writeResultToPipe == -1){
                std::cerr << strerror(errno) << endl;
                exit(errno);
            }
        }
    }

    return 0;
}
