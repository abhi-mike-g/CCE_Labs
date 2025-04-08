#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <limits.h>
#include <math.h>

// Utility function to clear extraneous characters from the input buffer
void clearInputBuffer() {
    while(getchar() != '\n');
}

// Function to input disk requests from the user
void inputRequests(int **requests, int *numRequests) {
    int n;
    printf("Enter the number of disk requests: ");
    scanf("%d", &n);
    clearInputBuffer();

    if(n <= 0) {
        printf("Number of disk requests must be positive.\n");
        return;
    }
    
    int *temp = (int *)malloc(n * sizeof(int));
    if(temp == NULL) {
        printf("Memory allocation failed.\n");
        exit(EXIT_FAILURE);
    }
    
    printf("Enter the disk request positions (separated by space):\n");
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

// Function to input the scanning direction: 1 for upward/increasing, 0 for downward/decreasing
void inputDirection(int *direction) {
    printf("Enter the initial scanning direction (1 for upward, 0 for downward): ");
    scanf("%d", direction);
    clearInputBuffer();
    if(*direction == 1 || *direction == 0) {
        printf("Initial direction stored successfully.\n");
    } else {
        printf("Invalid direction. Please enter 1 or 0.\n");
        *direction = -1;
    }
}

// Comparison function used by qsort (ascending order)
int compare(const void *a, const void *b) {
    return (*(int*)a - *(int*)b);
}

// Function to simulate the LOOK disk scheduling algorithm
void simulateLOOK(int requests[], int numRequests, int initialHead, int direction) {
    // First, sort the requests array in ascending order.
    qsort(requests, numRequests, sizeof(int), compare);
    
    int totalSeekTime = 0;
    int currentHead = initialHead;
    
    printf("\nLOOK Scheduling Order (Starting at head position %d):\n", initialHead);
    
    if (direction == 1) { 
        // UPWARD Direction:
        // 1. Service all requests with positions >= initialHead in ascending order.
        // 2. Then, reverse direction and service the requests that are less than initialHead in descending order.
        int i = 0;
        // Find first index such that request >= initialHead.
        while (i < numRequests && requests[i] < initialHead)
            i++;
        
        // Service requests upward.
        for (int j = i; j < numRequests; j++) {
            int distance = abs(requests[j] - currentHead);
            totalSeekTime += distance;
            currentHead = requests[j];
            printf("-> %d (Seek Time: %d)\n", currentHead, distance);
        }
        
        // Reverse direction: service the remaining requests in descending order.
        for (int j = i - 1; j >= 0; j--) {
            int distance = abs(currentHead - requests[j]);
            totalSeekTime += distance;
            currentHead = requests[j];
            printf("-> %d (Seek Time: %d)\n", currentHead, distance);
        }
        
    } else if (direction == 0) {
        // DOWNWARD Direction:
        // 1. Service all requests with positions <= initialHead in descending order.
        // 2. Then, reverse direction and service the remaining requests in ascending order.
        int i = numRequests - 1;
        // Find last index with request <= initialHead.
        while (i >= 0 && requests[i] > initialHead)
            i--;
        
        // Service requests downward.
        for (int j = i; j >= 0; j--) {
            int distance = abs(currentHead - requests[j]);
            totalSeekTime += distance;
            currentHead = requests[j];
            printf("-> %d (Seek Time: %d)\n", currentHead, distance);
        }
        
        // Reverse direction: service the remaining requests in ascending order.
        for (int j = i + 1; j < numRequests; j++) {
            int distance = abs(requests[j] - currentHead);
            totalSeekTime += distance;
            currentHead = requests[j];
            printf("-> %d (Seek Time: %d)\n", currentHead, distance);
        }
    } else {
        printf("Invalid direction encountered. Simulation aborted.\n");
        return;
    }
    
    printf("Total Seek Time: %d\n", totalSeekTime);
}

int main() {
    int choice;
    int *requests = NULL;       // Array to store disk request positions
    int numRequests = 0;        // Number of disk requests
    int initialHead = -1;       // Initial head position
    int direction = -1;         // 1 for upward/increasing, 0 for downward/decreasing
    
    // Flags to ensure data is entered before simulation
    bool requestsEntered = false;
    bool headEntered = false;
    bool directionEntered = false;

    do {
        printf("\n----- LOOK Disk Scheduling Simulation -----\n");
        printf("1. Enter Disk Requests\n");
        printf("2. Enter Initial Head Position\n");
        printf("3. Enter Initial Direction (1 for upward, 0 for downward)\n");
        printf("4. Simulate LOOK\n");
        printf("5. Exit\n");
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
                inputDirection(&direction);
                if(direction == 0 || direction == 1)
                    directionEntered = true;
                break;
            case 4:
                if (!requestsEntered || !headEntered || !directionEntered) {
                    printf("Please ensure you have entered disk requests, initial head position, and direction.\n");
                } else {
                    simulateLOOK(requests, numRequests, initialHead, direction);
                }
                break;
            case 5:
                printf("Exiting program.\n");
                break;
            default:
                printf("Invalid choice. Please try again.\n");
        }
    } while(choice != 5);

    if (requests != NULL) {
        free(requests);
    }
    return 0;
}