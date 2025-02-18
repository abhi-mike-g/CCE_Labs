#include <stdio.h>
#include <stdlib.h>

#define MAX 10

// Structure to represent each process
struct Process {
    int id;
    int bt; // Burst time
    int at; // Arrival time
    int ct; // Completion time
    int wt; // Waiting time
    int tat; // Turnaround time
    int pr; // Priority
};

// Function prototypes
void preemptiveSJF(struct Process proc[], int n);
void roundRobin(struct Process proc[], int n, int quantum);
void priorityScheduling(struct Process proc[], int n);

void findWaitingTime(struct Process proc[], int n);
void findTurnAroundTime(struct Process proc[], int n);
void findCompletionTime(struct Process proc[], int n);
void displayResults(struct Process proc[], int n);

int main() {
    struct Process proc[MAX];
    int n, choice, quantum;

    while (1) {
        printf("\nMenu:\n");
        printf("1. Preemptive SJF Scheduling\n");
        printf("2. Round Robin Scheduling\n");
        printf("3. Non-Preemptive Priority Scheduling\n");
        printf("4. Exit\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);

        switch (choice) {
            case 1:
                // Input processes
                printf("Enter number of processes: ");
                scanf("%d", &n);
                for (int i = 0; i < n; i++) {
                    proc[i].id = i + 1;
                    printf("Enter burst time and arrival time for process %d: ", i + 1);
                    scanf("%d%d", &proc[i].bt, &proc[i].at);
                }
                preemptiveSJF(proc, n);
                break;

            case 2:
                // Input processes
                printf("Enter number of processes: ");
                scanf("%d", &n);
                for (int i = 0; i < n; i++) {
                    proc[i].id = i + 1;
                    printf("Enter burst time and arrival time for process %d: ", i + 1);
                    scanf("%d%d", &proc[i].bt, &proc[i].at);
                }
                printf("Enter time quantum: ");
                scanf("%d", &quantum);
                roundRobin(proc, n, quantum);
                break;

            case 3:
                // Input processes
                printf("Enter number of processes: ");
                scanf("%d", &n);
                for (int i = 0; i < n; i++) {
                    proc[i].id = i + 1;
                    printf("Enter burst time, arrival time, and priority for process %d: ", i + 1);
                    scanf("%d%d%d", &proc[i].bt, &proc[i].at, &proc[i].pr);
                }
                priorityScheduling(proc, n);
                break;

            case 4:
                exit(0);

            default:
                printf("Invalid choice! Please enter a valid option.\n");
        }
    }

    return 0;
}

// Preemptive SJF Scheduling
void preemptiveSJF(struct Process proc[], int n) {
    int complete = 0, time = 0, min_index;
    int bt_remaining[n];
    for (int i = 0; i < n; i++) {
        bt_remaining[i] = proc[i].bt;
    }

    while (complete < n) {
        int min_burst = 99999; // Initialize to a large value
        min_index = -1;
        for (int i = 0; i < n; i++) {
            if (proc[i].at <= time && bt_remaining[i] > 0 && bt_remaining[i] < min_burst) {
                min_burst = bt_remaining[i];
                min_index = i;
            }
        }

        if (min_index == -1) {
            time++; // No process can be executed, so increment time
            continue;
        }

        bt_remaining[min_index]--;
        time++;

        if (bt_remaining[min_index] == 0) {
            proc[min_index].ct = time;
            proc[min_index].tat = proc[min_index].ct - proc[min_index].at;
            proc[min_index].wt = proc[min_index].tat - proc[min_index].bt;
            complete++;
        }
    }

    displayResults(proc, n);
}

// Round Robin Scheduling
void roundRobin(struct Process proc[], int n, int quantum) {
    int complete = 0, time = 0;
    int bt_remaining[n];
    for (int i = 0; i < n; i++) {
        bt_remaining[i] = proc[i].bt;
    }

    while (complete < n) {
        for (int i = 0; i < n; i++) {
            if (proc[i].at <= time && bt_remaining[i] > 0) {
                if (bt_remaining[i] > quantum) {
                    time += quantum;
                    bt_remaining[i] -= quantum;
                } else {
                    time += bt_remaining[i];
                    proc[i].ct = time;
                    proc[i].tat = proc[i].ct - proc[i].at;
                    proc[i].wt = proc[i].tat - proc[i].bt;
                    bt_remaining[i] = 0;
                    complete++;
                }
            }
        }
    }

    displayResults(proc, n);
}

// Non-Preemptive Priority Scheduling
void priorityScheduling(struct Process proc[], int n) {
    int complete = 0, time = 0;
    int sorted = 0;

    // Sort processes based on arrival time and priority (lower number means higher priority)
    for (int i = 0; i < n - 1; i++) {
        for (int j = i + 1; j < n; j++) {
            if (proc[i].at > proc[j].at || (proc[i].at == proc[j].at && proc[i].pr > proc[j].pr)) {
                struct Process temp = proc[i];
                proc[i] = proc[j];
                proc[j] = temp;
            }
        }
    }

    while (complete < n) {
        int min_index = -1;
        for (int i = 0; i < n; i++) {
            if (proc[i].at <= time && proc[i].ct == 0) {
                if (min_index == -1 || proc[i].pr < proc[min_index].pr) {
                    min_index = i;
                }
            }
        }

        if (min_index != -1) {
            proc[min_index].ct = time + proc[min_index].bt;
            proc[min_index].tat = proc[min_index].ct - proc[min_index].at;
            proc[min_index].wt = proc[min_index].tat - proc[min_index].bt;
            time = proc[min_index].ct;
            complete++;
        } else {
            time++;
        }
    }

    displayResults(proc, n);
}

// Calculate waiting time and turnaround time
void displayResults(struct Process proc[], int n) {
    float total_wt = 0, total_tat = 0;
    printf("\nProcess ID\tBurst Time\tArrival Time\tCompletion Time\tWaiting Time\tTurnaround Time\n");
    for (int i = 0; i < n; i++) {
        total_wt += proc[i].wt;
        total_tat += proc[i].tat;
        printf("%d\t\t%d\t\t%d\t\t%d\t\t%d\t\t%d\n", proc[i].id, proc[i].bt, proc[i].at, proc[i].ct, proc[i].wt, proc[i].tat);
    }

    printf("\nAverage Waiting Time: %.2f\n", total_wt / n);
    printf("Average Turnaround Time: %.2f\n", total_tat / n);
}
