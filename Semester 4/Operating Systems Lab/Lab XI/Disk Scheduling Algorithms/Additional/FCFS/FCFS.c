#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <math.h>
#include <limits.h>

// Utility function to clear the input buffer
void clearInputBuffer() {
    while(getchar() != '\n');
}

// Function to input disk requests from the user (order is preserved)
void inputRequests(int **requests, int *numRequests) {
    int n;
    printf("Enter the number of disk requests: ");
    scanf("%d", &n);
    clearInputBuffer();

    if(n <= 0) {
        printf("The number of disk requests must be positive.\n");
        return;
    }
    
    int *temp = (int *)malloc(n * sizeof(int));
    if(temp == NULL) {
        printf("Memory allocation failed.\n");
        exit(EXIT_FAILURE);
    }
    
    printf("Enter the disk request positions separated by space:\n");
    for (int i = 0; i < n; i++) {
        scanf("%d", &temp[i]);
    }
    clearInputBuffer();

    *requests = temp;
    *numRequests = n;
    printf("Disk requests stored successfully.\n");
}

// Function to input the initial head position
void inputInitialHead(int *initialHead) {
    printf("Enter the initial head position: ");
    scanf("%d", initialHead);
    clearInputBuffer();
    printf("Initial head position stored successfully.\n");
}

// Function to simulate the FCFS algorithm
void simulateFCFS(int requests[], int numRequests, int initialHead) {
    int totalSeekTime = 0;
    int currentHead = initialHead;
    
    printf("\nFCFS Scheduling Order (Starting at head position %d):\n", initialHead);
    
    // Process the requests in the order they were entered
    for (int i = 0; i < numRequests; i++) {
        int distance = abs(requests[i] - currentHead);
        totalSeekTime += distance;
        printf("Head moves from %d to %d (Seek Time: %d)\n", currentHead, requests[i], distance);
        currentHead = requests[i];
    }
    
    printf("Total Seek Time: %d\n", totalSeekTime);
}

int main() {
    int choice;
    int *requests = NULL;       // Array to store disk request positions (FIFO order)
    int numRequests = 0;        // Number of disk requests
    int initialHead = -1;       // Initial head position

    // Flags to ensure data is entered before simulation
    bool requestsEntered = false;
    bool headEntered = false;

    do {
        printf("\n----- FCFS Disk Scheduling Simulation -----\n");
        printf("1. Enter Disk Requests (order matters)\n");
        printf("2. Enter Initial Head Position\n");
        printf("3. Simulate FCFS\n");
        printf("4. Exit\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);
        clearInputBuffer();

        switch(choice) {
            case 1:
                inputRequests(&requests, &numRequests);
                requestsEntered = true;
                break;
            case 2:
                inputInitialHead(&initialHead);
                headEntered = true;
                break;
            case 3:
                if (!requestsEntered || !headEntered) {
                    printf("Please enter disk requests and the initial head position before simulation.\n");
                } else {
                    simulateFCFS(requests, numRequests, initialHead);
                }
                break;
            case 4:
                printf("Exiting program.\n");
                break;
            default:
                printf("Invalid choice. Please try again.\n");
        }
    } while(choice != 4);

    if (requests != NULL) {
        free(requests);
    }
    return 0;
}