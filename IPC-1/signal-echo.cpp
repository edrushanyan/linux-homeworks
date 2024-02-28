#include <iostream>
#include <unistd.h>
#include <signal.h>
#include <string.h>
#include <errno.h>
#include <sys/ucontext.h>
#include <sys/types.h>
#include <pwd.h>

using std::endl;

void signalHandler(int sig, siginfo_t *info, void *context) {

    // getting UID
    struct passwd *pwd = getpwuid(info->si_uid);

    uid_t userUID = info->si_uid;

    // getting PID
    pid_t userPID = info->si_pid;

    // getting username
    const char* username = nullptr;
    
    // checking if we found user's information
    if (pwd != nullptr) {
        username = pwd->pw_name;
    }

    // getting access to the user's context information
    struct ucontext_t *userContext = (ucontext_t*)context;

    // printing result
    std::cout << "Received a SIGUSR1 signal from process " << userPID << " executed by " << userUID << " ("<< username << ")." << endl;
    std::cout << "State of the context: EIP = " << userContext->uc_mcontext.gregs[REG_RIP] 
              << ", EAX = " << userContext->uc_mcontext.gregs[REG_RAX]
              << ", EBX = " << userContext->uc_mcontext.gregs[REG_RBX] << "." << endl;
}

int main() {
    
    // creating structur for handling signals
    struct sigaction action;
    
    // clearing the memory of the action
    memset(&action, 0, sizeof(action));
    
    // setting the flag
    action.sa_flags = SA_SIGINFO;
    
    // assigning the signalHandler function to the action
    action.sa_sigaction = signalHandler;

    // registering signalHandler for SIGUSR1
    int sig_result = sigaction(SIGUSR1, &action, NULL);

    // checking if there's any error
    if (sig_result < 0) {
        std::cerr << strerror(errno) << std::endl;
        exit(errno);
    }


    std::cout << "PID:" << getpid() << endl;
 
 
    // entering an infinite loop with a sleep delay
    while (true) {
        sleep(10);
    }

    return 0;
}
