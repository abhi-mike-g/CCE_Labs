#include <stdio.h>
#include <stdlib.h>

typedef struct Block {
    int start;           // Start address of the free block
    int size;            // Size of the free block
    struct Block* next;  // Pointer to next free block
} Block;

// Create a new block with given start and size
Block* createBlock(int start, int size) {
    Block* newBlock = (Block*)malloc(sizeof(Block));
    newBlock->start = start;
    newBlock->size = size;
    newBlock->next = NULL;
    return newBlock;
}

// Insert block at the beginning of the free list (simple insertion)
void insertBlock(Block** head, Block* newBlock) {
    newBlock->next = *head;
    *head = newBlock;
}

// Print the current free list (addresses and sizes)
void printFreeList(Block* head) {
    while (head) {
        printf("Start: %d, Size: %d\n", head->start, head->size);
        head = head->next;
    }
}

// First Fit: Find the first free block that is large enough
// If found, update free list and return allocation start address in allocStart
// Return 1 if allocation succeeds, 0 otherwise.
int allocateFirstFit(Block** freeList, int reqSize, int *allocStart) {
    Block *curr = *freeList, *prev = NULL;
    while (curr) {
        if (curr->size >= reqSize) {
            // Found a block; allocate from its beginning
            *allocStart = curr->start;
            curr->start += reqSize;
            curr->size -= reqSize;
            // If block size becomes zero, remove it from the list
            if (curr->size == 0) {
                if (prev)
                    prev->next = curr->next;
                else
                    *freeList = curr->next;
                free(curr);
            }
            return 1;
        }
        prev = curr;
        curr = curr->next;
    }
    return 0;
}

// Best Fit: Find the smallest free block that fits the request
// Return allocation start address via allocStart; update free list
int allocateBestFit(Block** freeList, int reqSize, int *allocStart) {
    Block *curr = *freeList, *prev = NULL;
    Block *bestFit = NULL, *bestFitPrev = NULL;

    while (curr) {
        if (curr->size >= reqSize) {
            if (!bestFit || curr->size < bestFit->size) {
                bestFit = curr;
                bestFitPrev = prev;
            }
        }
        prev = curr;
        curr = curr->next;
    }

    if (!bestFit)
        return 0;

    // Allocate from the best fit block found
    *allocStart = bestFit->start;
    bestFit->start += reqSize;
    bestFit->size -= reqSize;

    // If block size becomes zero, remove it
    if (bestFit->size == 0) {
        if (bestFitPrev)
            bestFitPrev->next = bestFit->next;
        else
            *freeList = bestFit->next;
        free(bestFit);
    }
    return 1;
}


int main() {
    int totalMemory, numProcesses;
    int strategy;

    printf("Enter total memory size: ");
    scanf("%d", &totalMemory);

    // Create the free list with one block representing all available memory
    Block* freeList = createBlock(0, totalMemory);

    printf("Select allocation strategy:\n");
    printf("1. First Fit\n");
    printf("2. Best Fit\n");
    printf("Enter your choice: ");
    scanf("%d", &strategy);

    printf("Enter the number of processes: ");
    scanf("%d", &numProcesses);

    // Array to store allocated start addresses for each process (-1 if not allocated)
    int *allocations = (int*)malloc(numProcesses * sizeof(int));

    // Process each allocation request
    for (int i = 0; i < numProcesses; i++) {
        int reqSize;
        printf("Enter memory required for process %d: ", i + 1);
        scanf("%d", &reqSize);

        int allocStart = -1;
        int result = 0;
        if (strategy == 1) {
            result = allocateFirstFit(&freeList, reqSize, &allocStart);
        } else if (strategy == 2) {
            result = allocateBestFit(&freeList, reqSize, &allocStart);
        } else {
            printf("Invalid strategy selected.\n");
            free(allocations);
            return 1;
        }

        if (result == 1) {
            printf("Process %d allocated at address %d\n", i + 1, allocStart);
            allocations[i] = allocStart;
        } else {
            printf("Process %d: Not enough memory to allocate %d units\n", i + 1, reqSize);
            allocations[i] = -1;
        }
    }

    // Display final free list after all allocations
    printf("\nFinal Free Memory Blocks:\n");
    printFreeList(freeList);

    free(allocations);

    // Free the free list
    while (freeList) {
        Block* temp = freeList;
        freeList = freeList->next;
        free(temp);
    }

    return 0;
}
