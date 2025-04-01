#include <stdio.h>
#include <stdlib.h>
#include <limits.h>
#include <stdbool.h>

// Function prototypes
int simulateFIFO(int *pages, int n, int frameCount);
int simulateOptimal(int *pages, int n, int frameCount);
bool isPresent(int *frames, int frameCount, int page);

int main() {
    int frameCount, n, choice;

    // Get frame allocation from user
    printf("Enter number of frames: ");
    scanf("%d", &frameCount);

    // Get the number of pages in the reference string
    printf("Enter number of pages in the reference string: ");
    scanf("%d", &n);

    // Dynamically allocate array for the page reference string
    int *pages = (int *)malloc(n * sizeof(int));
    if (pages == NULL) {
        perror("Memory allocation failed");
        exit(1);
    }

    printf("Enter the page reference string (space-separated):\n");
    for (int i = 0; i < n; i++) {
        scanf("%d", &pages[i]);
    }

    // Choose algorithm to simulate
    printf("Select Page Replacement Algorithm:\n");
    printf("1. FIFO\n");
    printf("2. Optimal\n");
    printf("Enter your choice: ");
    scanf("%d", &choice);

    int faults = 0;
    if (choice == 1) {
        faults = simulateFIFO(pages, n, frameCount);
    } else if (choice == 2) {
        faults = simulateOptimal(pages, n, frameCount);
    } else {
        printf("Invalid choice.\n");
        free(pages);
        exit(1);
    }

    printf("\nTotal Page Faults: %d\n", faults);

    free(pages);
    return 0;
}

// Checks if page is already in frames, returns true if found
bool isPresent(int *frames, int frameCount, int page) {
    for (int i = 0; i < frameCount; i++) {
        if (frames[i] == page) {
            return true;
        }
    }
    return false;
}

// FIFO Page Replacement Simulation
int simulateFIFO(int *pages, int n, int frameCount) {
    int faults = 0;

    // Dynamically allocate array for frames and initialize to -1 (empty)
    int *frames = (int *)malloc(frameCount * sizeof(int));
    for (int i = 0; i < frameCount; i++) {
        frames[i] = -1;
    }

    int pointer = 0; // Points to the frame to replace next (FIFO order)

    printf("\n--- FIFO Simulation ---\n");
    for (int i = 0; i < n; i++) {
        int page = pages[i];
        printf("Processing page %d: ", page);

        // If page is not already present, it is a page fault
        if (!isPresent(frames, frameCount, page)) {
            faults++;
            frames[pointer] = page;
            pointer = (pointer + 1) % frameCount;
            printf("Page fault! Frames: ");
        } else {
            printf("Hit! Frames: ");
        }

        // Print current state of frames
        for (int j = 0; j < frameCount; j++) {
            if (frames[j] != -1)
                printf("%d ", frames[j]);
            else
                printf("- ");
        }
        printf("\n");
    }

    free(frames);
    return faults;
}

// Optimal Page Replacement Simulation
int simulateOptimal(int *pages, int n, int frameCount) {
    int faults = 0;

    // Dynamically allocate array for frames and initialize to -1 (empty)
    int *frames = (int *)malloc(frameCount * sizeof(int));
    for (int i = 0; i < frameCount; i++) {
        frames[i] = -1;
    }

    printf("\n--- Optimal Simulation ---\n");
    for (int i = 0; i < n; i++) {
        int page = pages[i];
        printf("Processing page %d: ", page);

        // If page already in frames, it's a hit
        if (isPresent(frames, frameCount, page)) {
            printf("Hit! Frames: ");
        } else {
            faults++;
            // Check if there is an empty frame available
            bool allocated = false;
            for (int j = 0; j < frameCount; j++) {
                if (frames[j] == -1) {
                    frames[j] = page;
                    allocated = true;
                    break;
                }
            }

            // If no empty frame, find the optimal frame to replace
            if (!allocated) {
                int indexToReplace = -1;
                int farthest = i + 1;
                for (int j = 0; j < frameCount; j++) {
                    int k;
                    // Find next use of frames[j]
                    for (k = i + 1; k < n; k++) {
                        if (frames[j] == pages[k])
                            break;
                    }
                    // If this page is never used again, choose it
                    if (k == n) {
                        indexToReplace = j;
                        break;
                    }
                    // Else choose the page used farthest in future
                    if (k > farthest) {
                        farthest = k;
                        indexToReplace = j;
                    }
                }
                // Replace the chosen frame
                frames[indexToReplace] = page;
            }
            printf("Page fault! Frames: ");
        }

        // Print current state of frames
        for (int j = 0; j < frameCount; j++) {
            if (frames[j] != -1)
                printf("%d ", frames[j]);
            else
                printf("- ");
        }
        printf("\n");
    }

    free(frames);
    return faults;
}
