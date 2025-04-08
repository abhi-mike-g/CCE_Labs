#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <limits.h>
#include <math.h>

// Clear any extraneous characters from input buffer
void clearInputBuffer() {
    while(getchar() != '\n');
}

// Input disk requests from the user
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

// Input initial head position
void inputInitialHead(int *initialHead) {
    printf("Enter the initial head position: ");
    scanf("%d", initialHead);
    clearInputBuffer();
    printf("Initial head position stored successfully.\n");
}

// Input disk end (maximum track number)
void inputDiskEnd(int *diskEnd) {
    printf("Enter the disk end (maximum track number, lower bound assumed 0): ");
    scanf("%d", diskEnd);
    clearInputBuffer();
    printf("Disk end stored successfully.\n");
}

// Input scan direction: 1 for upward, 0 for downward
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

// Function to simulate the C-SCAN algorithm
void simulateCSCAN(int requests[], int numRequests, int initialHead, int diskEnd, int direction) {
    // Sort the disk requests in ascending order.
    qsort(requests, numRequests, sizeof(int), compare);

    int totalSeekTime = 0;
    int currentHead = initialHead;

    printf("\nC-SCAN Scheduling Order (Starting at head position %d):\n", initialHead);

    if (direction == 1) {
        // For upward scanning:
        // 1. Service all requests with positions >= initialHead in ascending order.
        // 2. Move the head to the disk end if not already there.
        // 3. Jump from disk end to 0 (this jump cost is added).
        // 4. Service remaining requests (those < initialHead) in ascending order.
        int i = 0;
        // Find the first request >= initialHead
        while(i < numRequests && requests[i] < initialHead)
            i++;

        // Service upward direction requests.
        for (int j = i; j < numRequests; j++) {
            int distance = abs(requests[j] - currentHead);
            totalSeekTime += distance;
            currentHead = requests[j];
            printf("-> %d (Seek Time: %d)\n", currentHead, distance);
        }
        // Move to disk end if not already there.
        if (currentHead != diskEnd) {
            int distance = abs(diskEnd - currentHead);
            totalSeekTime += distance;
            currentHead = diskEnd;
            printf("-> %d (Seek Time: %d) [Reached Disk End]\n", currentHead, distance);
        }
        // Jump from disk end to 0.
        int jumpDistance = diskEnd;  // Since lower bound is 0.
        totalSeekTime += jumpDistance;
        currentHead = 0;
        printf("-> %d (Jump: %d) [Jump from Disk End to Start]\n", currentHead, jumpDistance);

        // Service remaining requests (those < initialHead) in ascending order.
        for (int j = 0; j < i; j++) {
            int distance = abs(requests[j] - currentHead);
            totalSeekTime += distance;
            currentHead = requests[j];
            printf("-> %d (Seek Time: %d)\n", currentHead, distance);
        }
    }
    else if (direction == 0) {
        // For downward scanning:
        // 1. Service all requests with positions <= initialHead in descending order.
        // 2. Move the head to 0 if not already there.
        // 3. Jump from 0 to diskEnd.
        // 4. Service remaining requests (those > initialHead) in descending order.
        int i = numRequests - 1;
        // Find the last request <= initialHead
        while(i >= 0 && requests[i] > initialHead)
            i--;

        // Service requests in downward direction.
        for (int j = i; j >= 0; j--) {
            int distance = abs(currentHead - requests[j]);
            totalSeekTime += distance;
            currentHead = requests[j];
            printf("-> %d (Seek Time: %d)\n", currentHead, distance);
        }
        // Move to the lower end (0) if not already there.
        if(currentHead != 0) {
            int distance = abs(currentHead - 0);
            totalSeekTime += distance;
            currentHead = 0;
            printf("-> %d (Seek Time: %d) [Reached Disk Start]\n", currentHead, distance);
        }
        // Jump from 0 to diskEnd.
        int jumpDistance = diskEnd; // Since diskEnd is maximum track.
        totalSeekTime += jumpDistance;
        currentHead = diskEnd;
        printf("-> %d (Jump: %d) [Jump from Start to Disk End]\n", currentHead, jumpDistance);

        // Service remaining requests (those > initialHead) in descending order.
        for (int j = numRequests - 1; j > i; j--) {
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
    int diskEnd = -1;        // Maximum disk track (lower bound is assumed 0)
    int direction = -1;      // 1 for upward, 0 for downward

    bool requestsEntered = false;
    bool headEntered = false;
    bool diskSizeEntered = false;
    bool directionEntered = false;

    do {
        printf("\n----- C-SCAN Disk Scheduling Simulation -----\n");
        printf("1. Enter Disk Requests\n");
        printf("2. Enter Initial Head Position\n");
        printf("3. Enter Disk End (Maximum Track)\n");
        printf("4. Enter Initial Direction (1 for upward, 0 for downward)\n");
        printf("5. Simulate C-SCAN\n");
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
                if(direction == 0 || direction == 1)
                    directionEntered = true;
                break;
            case 5:
                if (!requestsEntered || !headEntered || !diskSizeEntered || !directionEntered) {
                    printf("Please make sure you have entered disk requests, initial head position, disk end, and direction.\n");
                } else {
                    simulateCSCAN(requests, numRequests, initialHead, diskEnd, direction);
                }
                break;
            case 6:
                printf("Exiting program.\n");
                break;
            default:
                printf("Invalid choice. Please try again.\n");
        }
    } while(choice != 6);

    if (requests != NULL) {
        free(requests);
    }
    return 0;
}