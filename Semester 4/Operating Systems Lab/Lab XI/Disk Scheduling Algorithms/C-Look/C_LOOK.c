#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <limits.h>
#include <math.h>

// Function to clear any extraneous characters from the input buffer
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

// Function to input the scanning direction: 1 for upward, 0 for downward
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

// Comparison function used by qsort to sort the array in ascending order
int compare(const void *a, const void *b) {
    return (*(int*)a - *(int*)b);
}

// Function to simulate the C-LOOK disk scheduling algorithm
void simulateCLOOK(int requests[], int numRequests, int initialHead, int direction) {
    // Sort the disk requests in ascending order.
    qsort(requests, numRequests, sizeof(int), compare);
    
    int totalSeekTime = 0;
    int currentHead = initialHead;
    
    printf("\nC-LOOK Scheduling Order (Starting at head position %d):\n", initialHead);
    
    if (direction == 1) {
        // UPWARD direction:
        // 1. Service all requests with positions >= initialHead in ascending order.
        // 2. Jump to the smallest request (if any) that is below initialHead,
        //    and service remaining requests in ascending order.
        int i = 0;
        // Find the first index with a request >= initialHead.
        while (i < numRequests && requests[i] < initialHead)
            i++;
        
        // Service upward requests.
        for (int j = i; j < numRequests; j++) {
            int distance = abs(requests[j] - currentHead);
            totalSeekTime += distance;
            currentHead = requests[j];
            printf("-> %d (Seek Time: %d)\n", currentHead, distance);
        }
        
        // If there are any requests below the initial head, jump to the first request.
        if (i > 0) {
            int jumpDistance = abs(currentHead - requests[0]);
            totalSeekTime += jumpDistance;
            currentHead = requests[0];
            printf("-> %d (Jump: %d) [Jump from Highest to Lowest Request]\n", currentHead, jumpDistance);
            
            // Service remaining requests.
            for (int j = 1; j < i; j++) {
                int distance = abs(requests[j] - currentHead);
                totalSeekTime += distance;
                currentHead = requests[j];
                printf("-> %d (Seek Time: %d)\n", currentHead, distance);
            }
        }
    } else if (direction == 0) {
        // DOWNWARD direction:
        // 1. Service all requests with positions <= initialHead in descending order.
        // 2. Jump to the largest request (if any) that is above initialHead,
        //    and service remaining requests in descending order.
        int i = numRequests - 1;
        // Find the last index with a request <= initialHead.
        while (i >= 0 && requests[i] > initialHead)
            i--;
        
        // Service downward requests.
        for (int j = i; j >= 0; j--) {
            int distance = abs(currentHead - requests[j]);
            totalSeekTime += distance;
            currentHead = requests[j];
            printf("-> %d (Seek Time: %d)\n", currentHead, distance);
        }
        
        // If there are any requests above the initial head, jump to the largest of those.
        if (i < numRequests - 1) {
            int jumpDistance = abs(currentHead - requests[numRequests - 1]);
            totalSeekTime += jumpDistance;
            currentHead = requests[numRequests - 1];
            printf("-> %d (Jump: %d) [Jump from Lowest to Highest Request]\n", currentHead, jumpDistance);
            
            // Service remaining requests.
            for (int j = numRequests - 2; j > i; j--) {
                int distance = abs(currentHead - requests[j]);
                totalSeekTime += distance;
                currentHead = requests[j];
                printf("-> %d (Seek Time: %d)\n", currentHead, distance);
            }
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
    int *requests = NULL;       // Array to store disk request positions
    int numRequests = 0;        // Number of disk requests
    int initialHead = -1;       // Initial head position
    int direction = -1;         // 1 for upward/increasing, 0 for downward/decreasing

    bool requestsEntered = false;
    bool headEntered = false;
    bool directionEntered = false;

    do {
        printf("\n----- C-LOOK Disk Scheduling Simulation -----\n");
        printf("1. Enter Disk Requests\n");
        printf("2. Enter Initial Head Position\n");
        printf("3. Enter Initial Direction (1 for upward, 0 for downward)\n");
        printf("4. Simulate C-LOOK\n");
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
                    printf("Please make sure you have entered disk requests, initial head position, and direction.\n");
                } else {
                    simulateCLOOK(requests, numRequests, initialHead, direction);
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