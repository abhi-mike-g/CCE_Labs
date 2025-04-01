#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

// Function to find the index of a page in the frames array
int findFrameIndex(int *frames, int frameCount, int page) {
    for (int i = 0; i < frameCount; i++) {
        if (frames[i] == page)
            return i;
    }
    return -1;
}

int main() {
    int frameCount, n;

    // Get the number of frames from the user
    printf("Enter number of frames: ");
    scanf("%d", &frameCount);

    // Get the length of the page reference string
    printf("Enter number of pages in the reference string: ");
    scanf("%d", &n);

    // Dynamically allocate memory for the page reference string
    int *pages = (int *)malloc(n * sizeof(int));
    if (pages == NULL) {
        perror("Memory allocation failed");
        exit(1);
    }

    printf("Enter the page reference string (space-separated):\n");
    for (int i = 0; i < n; i++) {
        scanf("%d", &pages[i]);
    }

    // Dynamically allocate memory for frames and initialize them to -1 (empty)
    int *frames = (int *)malloc(frameCount * sizeof(int));
    // Array to track last used time for each frame (for LRU)
    int *lastUsed = (int *)malloc(frameCount * sizeof(int));
    if (frames == NULL || lastUsed == NULL) {
        perror("Memory allocation failed");
        exit(1);
    }

    for (int i = 0; i < frameCount; i++) {
        frames[i] = -1;
        lastUsed[i] = 0;
    }

    int faults = 0;
    int time = 0; // A counter to track the order of usage

    printf("\n--- LRU Page Replacement Simulation ---\n");
    for (int i = 0; i < n; i++) {
        int page = pages[i];
        time++;  // Increment "time" with each page reference

        // Check if the page is already in one of the frames (a hit)
        int index = findFrameIndex(frames, frameCount, page);
        if (index != -1) {
            // It's a hit – update the last used time for this frame
            lastUsed[index] = time;
            printf("Processing page %d: Hit! Frames: ", page);
        } else {
            // Page fault occurs
            faults++;
            // Check for an empty frame first
            int emptyIndex = -1;
            for (int j = 0; j < frameCount; j++) {
                if (frames[j] == -1) {
                    emptyIndex = j;
                    break;
                }
            }

            if (emptyIndex != -1) {
                // Place the page in the empty frame
                frames[emptyIndex] = page;
                lastUsed[emptyIndex] = time;
            } else {
                // No empty frame available: find the least recently used (LRU) page
                int lruIndex = 0;
                int minTime = lastUsed[0];
                for (int j = 1; j < frameCount; j++) {
                    if (lastUsed[j] < minTime) {
                        minTime = lastUsed[j];
                        lruIndex = j;
                    }
                }
                // Replace the LRU page with the new page
                frames[lruIndex] = page;
                lastUsed[lruIndex] = time;
            }
            printf("Processing page %d: Fault! Frames: ", page);
        }

        // Print the current state of frames
        for (int k = 0; k < frameCount; k++) {
            if (frames[k] == -1)
                printf("- ");
            else
                printf("%d ", frames[k]);
        }
        printf("\n");
    }

    printf("\nTotal Page Faults: %d\n", faults);

    // Free dynamically allocated memory
    free(pages);
    free(frames);
    free(lastUsed);

    return 0;
}
