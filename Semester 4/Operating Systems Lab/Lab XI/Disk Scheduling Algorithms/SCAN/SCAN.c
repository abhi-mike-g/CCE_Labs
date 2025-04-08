#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <limits.h>
#include <math.h>

// Utility function to flush the input buffer
void clearInputBuffer() {
    while(getchar() != '\n');
}

// Function to input disk requests from user
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

// Function to input the disk end (maximum track number)
void inputDiskEnd(int *diskEnd) {
    printf("Enter the disk end (maximum track number, lower bound assumed 0): ");
    scanf("%d", diskEnd);
    clearInputBuffer();
    printf("Disk end stored successfully.\n");
}

// Function to input the initial scanning direction: 1 for upward (increasing), 0 for downward (decreasing)
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

// Comparison function for qsort (ascending order)
int compare(const void *a, const void *b) {
    return (*(int*)a - *(int*)b);
}

// Function to simulate the SCAN disk scheduling algorithm
void simulateSCAN(int requests[], int numRequests, int initialHead, int diskEnd, int direction) {
    // First, sort the requests in ascending order.
    qsort(requests, numRequests, sizeof(int), compare);
    
    int totalSeekTime = 0;
    int currentHead = initialHead;
    printf("\nSCAN Scheduling Order (Starting at %d):\n", initialHead);
    
    if (direction == 1) {
        // UPWARD: first service all requests >= initialHead in ascending order.
        // Then, go to diskEnd, reverse direction, and service the remaining requests in descending order.
        int i = 0;
        // Find first index with request >= initialHead
        while(i < numRequests && requests[i] < initialHead)
            i++;
        
        // Service the upward requests.
        for (int j = i; j < numRequests; j++) {
            int distance = abs(requests[j] - currentHead);
            totalSeekTime += distance;
            currentHead = requests[j];
            printf("-> %d (Seek Time: %d)\n", currentHead, distance);
        }
        
        // Once done, if the head is not at the end, go to diskEnd.
        if(currentHead != diskEnd) {
            int distance = abs(diskEnd - currentHead);
            totalSeekTime += distance;
            currentHead = diskEnd;
            printf("-> %d (Seek Time: %d) [Reached Disk End]\n", currentHead, distance);
        }
        
        // Reverse direction: service requests < initialHead in descending order.
        for (int j = i - 1; j >= 0; j--) {
            int distance = abs(currentHead - requests[j]);
            totalSeekTime += distance;
            currentHead = requests[j];
            printf("-> %d (Seek Time: %d)\n", currentHead, distance);
        }
    }
    else if (direction == 0) {
        // DOWNWARD: first service all requests <= initialHead in descending order.
        // Then, go to 0 and reverse to service the remaining requests in ascending order.
        int i = numRequests - 1;
        // Find last index with request <= initialHead
        while(i >= 0 && requests[i] > initialHead)
            i--;
        
        // Service downward requests.
        for (int j = i; j >= 0; j--) {
            int distance = abs(currentHead - requests[j]);
            totalSeekTime += distance;
            currentHead = requests[j];
            printf("-> %d (Seek Time: %d)\n", currentHead, distance);
        }
        
        // Once done, if the head is not at 0, go to 0.
        if(currentHead != 0) {
            int distance = abs(currentHead - 0);
            totalSeekTime += distance;
            currentHead = 0;
            printf("-> %d (Seek Time: %d) [Reached Disk Start]\n", currentHead, distance);
        }
        
        // Reverse direction: service requests > initialHead in ascending order.
        for (int j = i + 1; j < numRequests; j++) {
            int distance = abs(currentHead - requests[j]);
            totalSeekTime += distance;
            currentHead = requests[j];
            printf("-> %d (Seek Time: %d)\n", currentHead, distance);
        }
    }
    else {
        printf("Invalid direction encountered. Simulation aborted.\n");
        return;
    }
    
    printf("Total Seek Time: %d\n", totalSeekTime);
}

int main() {
    int choice;
    int *requests = NULL;    // Array to store disk request positions
    int numRequests = 0;     // Number of disk requests
    int initialHead = -1;    // Initial head position
    int diskEnd = -1;        // Maximum disk cylinder (lower bound is assumed 0)
    int direction = -1;      // 1 for upward (increasing), 0 for downward (decreasing)
    
    bool requestsEntered = false;
    bool headEntered = false;
    bool diskSizeEntered = false;
    bool directionEntered = false;
    
    do {
        printf("\n----- SCAN Disk Scheduling Simulation -----\n");
        printf("1. Enter Disk Requests\n");
        printf("2. Enter Initial Head Position\n");
        printf("3. Enter Disk End (Max Track)\n");
        printf("4. Enter Initial Direction (1 for upward, 0 for downward)\n");
        printf("5. Simulate SCAN\n");
        printf("6. Exit\n");
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
                inputDiskEnd(&diskEnd);
                diskSizeEntered = true;
                break;
            case 4:
                inputDirection(&direction);
                directionEntered = true;
                break;
            case 5:
                if (!requestsEntered || !headEntered || !diskSizeEntered || !directionEntered) {
                    printf("Please ensure you have entered disk requests, initial head position, disk end, and direction.\n");
                } else {
                    simulateSCAN(requests, numRequests, initialHead, diskEnd, direction);
                }
                break;
            case 6:
                printf("Exiting program.\n");
                break;
            default:
                printf("Invalid choice. Please try again.\n");
                break;
        }
    } while(choice != 6);
    
    if (requests != NULL) {
        free(requests);
    }
    
    return 0;
}
