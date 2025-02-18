// CLI Argument passing

/*
Write a C program to accept a set of strings as command line arguments. Sort the
strings and display them in a child process. Parent process should display the un-
sorted strings only after the child displays the sorted list.
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>

// Function to compare two strings (for qsort)
int compare_strings(const void *a, const void *b) {
    return strcmp(*(const char **)a, *(const char **)b);
}

int main(int argc, char *argv[]) {
    // Ensure that at least two strings are provided
    if (argc < 2) {
        fprintf(stderr, "Please provide a set of strings as command line arguments.\n");
        return 1;
    }

    pid_t pid = fork();  // Create a child process

    if (pid < 0) {
        // Error in forking
        perror("Fork failed");
        return 1;
    }

    if (pid == 0) {
        // Child process: sort and display the strings
        printf("Child Process (Sorted Strings):\n");
        
        // Sorting the strings (we will use qsort to sort)
        qsort(&argv[1], argc - 1, sizeof(char *), compare_strings);
        
        // Display sorted strings
        for (int i = 1; i < argc; i++) {
            printf("%s\n", argv[i]);
        }
        exit(0);  // Child process exits here
    } else {
        // Parent process: wait for child to complete and display unsorted strings
        wait(NULL);  // Wait for the child process to finish
        printf("Parent Process (Unsorted Strings):\n");

        // Display original unsorted strings (argv[0] is the program name)
        for (int i = 1; i < argc; i++) {
            printf("%s\n", argv[i]);
        }
    }

    return 0;
}
