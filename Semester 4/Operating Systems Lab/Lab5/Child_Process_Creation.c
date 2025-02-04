// Child Process Creation

/*
Write a C program to create a child process. Display different messages in parent
process and child process. Display PID and PPID of both parent and child process.
*/

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

int main() {
    pid_t pid = fork();  // Create a child process

    if (pid < 0) {
        // Error in forking
        perror("Fork failed");
        return 1;
    }

    if (pid == 0) {
        // Child process
        printf("Child Process:\n");
        printf("PID: %d\n", getpid());
        printf("PPID: %d\n", getppid());
        printf("Hello from Child Process!\n");
    } else {
        // Parent process
        printf("Parent Process:\n");
        printf("PID: %d\n", getpid());
        printf("PPID: %d\n", getppid());
        printf("Hello from Parent Process!\n");
    }

    return 0;
}
