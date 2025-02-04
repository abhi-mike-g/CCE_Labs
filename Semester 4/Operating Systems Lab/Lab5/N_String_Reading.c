// N string Reading

/*
Write a C program to read N strings. Create two child processes, each of this
should perform sorting using two different methods (bubble, selection, quicksort
etc). The parent should wait until one of the child process terminates.
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>

// Bubble Sort function
void bubble_sort(char *arr[], int n) {
    for (int i = 0; i < n - 1; i++) {
        for (int j = 0; j < n - 1 - i; j++) {
            if (strcmp(arr[j], arr[j + 1]) > 0) {
                // Swap strings
                char *temp = arr[j];
                arr[j] = arr[j + 1];
                arr[j + 1] = temp;
            }
        }
    }
}

// Selection Sort function
void selection_sort(char *arr[], int n) {
    for (int i = 0; i < n - 1; i++) {
        int min_index = i;
        for (int j = i + 1; j < n; j++) {
            if (strcmp(arr[j], arr[min_index]) < 0) {
                min_index = j;
            }
        }
        // Swap strings
        if (min_index != i) {
            char *temp = arr[i];
            arr[i] = arr[min_index];
            arr[min_index] = temp;
        }
    }
}

// Quick Sort function
int compare_strings(const void *a, const void *b) {
    return strcmp(*(const char **)a, *(const char **)b);
}

void quick_sort(char *arr[], int n) {
    qsort(arr, n, sizeof(char *), compare_strings);
}

int main() {
    int N;

    printf("Enter the number of strings: ");
    scanf("%d", &N);
    getchar(); // To consume the newline character after the number input

    // Allocate memory for N strings
    char *strings[N];
    printf("Enter the strings:\n");
    for (int i = 0; i < N; i++) {
        strings[i] = (char *)malloc(100 * sizeof(char));
        fgets(strings[i], 100, stdin);
        strings[i][strcspn(strings[i], "\n")] = '\0';  
    pid_t pid1 = fork();  // Create the first child process for Bubble Sort

    if (pid1 < 0) {
        perror("Fork failed");
        return 1;
    }

    if (pid1 == 0) {
        // First child process - Bubble Sort
        printf("Child Process 1 (Bubble Sort) is sorting...\n");
        bubble_sort(strings, N);
        
        printf("Child Process 1 (Sorted using Bubble Sort):\n");
        for (int i = 0; i < N; i++) {
            printf("%s\n", strings[i]);
        }
        exit(0);  // Exit child process 1
    } else {
        pid_t pid2 = fork();  // Create the second child process for Quick Sort

        if (pid2 < 0) {
            perror("Fork failed");
            return 1;
        }

        if (pid2 == 0) {
            // Second child process - Quick Sort
            printf("Child Process 2 (Quick Sort) is sorting...\n");
            quick_sort(strings, N);
            
            printf("Child Process 2 (Sorted using Quick Sort):\n");
            for (int i = 0; i < N; i++) {
                printf("%s\n", strings[i]);
            }
            exit(0);  // Exit child process 2
        } else {
            // Parent process - wait for either of the child processes
            wait(NULL);  // Wait for any child to terminate
            printf("Parent Process: One child has completed sorting.\n");
        }
    }

    // Free the allocated memory for strings
    for (int i = 0; i < N; i++) {
        free(strings[i]);
    }

    return 0;
}
