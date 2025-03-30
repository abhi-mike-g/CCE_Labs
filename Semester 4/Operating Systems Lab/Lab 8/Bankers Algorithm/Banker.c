#include <stdio.h>
#include <stdbool.h>

#define MAX_PROCESSES 5
#define MAX_RESOURCES 3

// Function to find if the system is in a safe state
bool isSafe(int processes[], int avail[], int max[][MAX_RESOURCES], int allot[][MAX_RESOURCES], int n, int m) {
    int need[n][m];

    // Calculate the need matrix
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++) {
            need[i][j] = max[i][j] - allot[i][j];
        }
    }

    bool finish[n];
    for (int i = 0; i < n; i++) {
        finish[i] = false;
    }

    int work[m];
    for (int i = 0; i < m; i++) {
        work[i] = avail[i];
    }

    int count = 0;
    while (count < n) {
        bool found = false;

        // Try to find a process that can be completed
        for (int p = 0; p < n; p++) {
            if (!finish[p]) {
                int j;
                for (j = 0; j < m; j++) {
                    if (need[p][j] > work[j]) {
                        break;
                    }
                }

                if (j == m) {
                    // If process p can be completed
                    for (int k = 0; k < m; k++) {
                        work[k] += allot[p][k];
                    }
                    finish[p] = true;
                    found = true;
                    count++;
                }
            }
        }

        if (!found) {
            return false; // No process can be completed, system is not in a safe state
        }
    }

    return true; // All processes can be completed, system is in a safe state
}

// Function to request resources from the system
bool requestResources(int processID, int request[], int avail[], int max[][MAX_RESOURCES], int allot[][MAX_RESOURCES], int n, int m, int processes[]) {
    // Check if the request is less than or equal to the need
    for (int i = 0; i < m; i++) {
        if (request[i] > max[processID][i] - allot[processID][i]) {
            printf("Error: Process has exceeded its maximum claim.\n");
            return false;
        }
    }

    // Check if the request is less than or equal to the available resources
    for (int i = 0; i < m; i++) {
        if (request[i] > avail[i]) {
            printf("Error: Resources are not available.\n");
            return false;
        }
    }

    // Pretend to allocate resources and check if the system is in a safe state
    for (int i = 0; i < m; i++) {
        avail[i] -= request[i];
        allot[processID][i] += request[i];
    }

    if (isSafe(processes, avail, max, allot, n, m)) {
        printf("Request granted.\n");
        return true;
    } else {
        // Rollback the allocation if not safe
        for (int i = 0; i < m; i++) {
            avail[i] += request[i];
            allot[processID][i] -= request[i];
        }
        printf("Request denied. System would be in an unsafe state.\n");
        return false;
    }
}

int main() {
    int n, m;
    int processes[MAX_PROCESSES];
    int avail[MAX_RESOURCES];
    int max[MAX_PROCESSES][MAX_RESOURCES];
    int allot[MAX_PROCESSES][MAX_RESOURCES];

    printf("Enter the number of processes: ");
    scanf("%d", &n);
    printf("Enter the number of resources: ");
    scanf("%d", &m);

    // Input available resources
    printf("Enter available resources:\n");
    for (int i = 0; i < m; i++) {
        printf("Resource %d: ", i);
        scanf("%d", &avail[i]);
    }

    // Input maximum resources for each process
    printf("Enter maximum resources required by each process:\n");
    for (int i = 0; i < n; i++) {
        processes[i] = i;
        for (int j = 0; j < m; j++) {
            printf("Max resources for process %d, resource %d: ", i, j);
            scanf("%d", &max[i][j]);
        }
    }

    // Input allocated resources for each process
    printf("Enter allocated resources for each process:\n");
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++) {
            printf("Allocated resources for process %d, resource %d: ", i, j);
            scanf("%d", &allot[i][j]);
        }
    }

    // Checking if the system is in a safe state initially
    if (isSafe(processes, avail, max, allot, n, m)) {
        printf("System is in a safe state.\n");
    } else {
        printf("System is not in a safe state.\n");
    }

    // Resource request from a process
    int processID;
    int request[MAX_RESOURCES];
    printf("Enter the process ID to request resources: ");
    scanf("%d", &processID);

    printf("Enter the request for resources:\n");
    for (int i = 0; i < m; i++) {
        printf("Resource %d: ", i);
        scanf("%d", &request[i]);
    }

    // Try to request the resources
    requestResources(processID, request, avail, max, allot, n, m, processes);

    return 0;
}
