//Deadlock Detection Algorithm

#include <stdio.h>
#include <stdbool.h>

#define MAX_PROCESSES 5
#define MAX_RESOURCES 3

// Function to check if a process is in a deadlock state
bool isDeadlocked(int processes[], int avail[], int max[][MAX_RESOURCES], int allot[][MAX_RESOURCES], int n, int m) {
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
            // A process is waiting and cannot proceed, thus there is a deadlock
            return true;
        }
    }

    // No deadlock found
    return false;
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

    // Checking if the system is in a deadlocked state
    if (isDeadlocked(processes, avail, max, allot, n, m)) {
        printf("The system is in a deadlock state.\n");
    } else {
        printf("The system is not in a deadlock state.\n");
    }

    return 0;
}
