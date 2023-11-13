#include <iostream>
#include <errno.h>
#include <string.h>
#include <sys/types.h>
#include <unistd.h>
#include <sys/wait.h>
#include <sys/times.h>

using std::endl;

void do_command(char** argv){

    // creating everything ehat we need for time
    struct tms start, end;

    clock_t startTime, endTime;

    // geting the start time
    startTime = times(&start);

    // creating the child process
    pid_t pid = fork();

    // checking the errors
    if(pid < 0){
        std::cerr << strerror(errno) << endl;
        exit(errno);
    }

    // for child process executing commands
    if(pid == 0){
        int executed = execvp(argv[0], argv);

        // checking for errors
        if(executed < 0){
            std::cerr << strerror(errno) << endl;
            exit(errno);
        }
    }

    // parent process
    if(pid > 0){

        // adding the status
        int wstatus;

        // waiting for child process
        pid_t waitResult = waitpid(pid, &wstatus, 0);

        // geting the end time
        endTime = times(&end);

        // counting the whole time
        double fullTime = (double)(endTime - startTime);

        // printing the answer
        std::cout << "Comman completed with " << WEXITSTATUS(wstatus) << " exit code and took " << fullTime << " seconds." << endl;
    }
}


int main(int argc, char** argv){
    // checking if we added the files
    if(argc < 2){
        std::cerr << strerror(errno) << endl;
        exit(errno);
    }

    // creating array of arguments
    char* args[argc];

    for(int i = 0; i < argc; ++i){
        args[i] = argv[i + 1];
    }

    // giving last argument the nullptr
    args[argc] = nullptr;

    // calling the function
    do_command(args);

    return 0;
}