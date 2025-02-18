#include <stdio.h>
#include <stdlib.h>

struct Process {
    int id;         // Process ID
    int bt;         // Burst time
    int at;         // Arrival time
    int ct;         // Completion time
    int wt;         // Waiting time
    int tat;        // Turnaround time
};

void findCompletionTime(struct Process proc[], int n);
void findWaitingTime(struct Process proc[], int n);
void findTurnAroundTime(struct Process proc[], int n);
void displayResults(struct Process proc[], int n);
void sortByArrivalTime(struct Process proc[], int n);
void sortByBurstTime(struct Process proc[], int n, int current_time);

int main() {
    int n;

    // Input number of processes
    printf("Enter the number of processes: ");
    scanf("%d", &n);

    struct Process proc[n];

    // Input burst time and arrival time for each process
    for (int i = 0; i < n; i++) {
        proc[i].id = i + 1;
        printf("Enter burst time and arrival time for Process %d: ", proc[i].id);
        scanf("%d%d", &proc[i].bt, &proc[i].at);
    }

    // Sorting processes based on arrival time
    sortByArrivalTime(proc, n);

    // Non-Preemptive SJF Scheduling
    findCompletionTime(proc, n);
    findTurnAroundTime(proc, n);
    findWaitingTime(proc, n);
    displayResults(proc, n);

    return 0;
}

// Function to sort processes based on arrival time
void sortByArrivalTime(struct Process proc[], int n) {
    for (int i = 0; i < n - 1; i++) {
        for (int j = i + 1; j < n; j++) {
            if (proc[i].at > proc[j].at) {
                struct Process temp = proc[i];
                proc[i] = proc[j];
                proc[j] = temp;
            }
        }
    }
}

// Function to sort processes based on burst time for the current time
void sortByBurstTime(struct Process proc[], int n, int current_time) {
    for (int i = 0; i < n - 1; i++) {
        for (int j = i + 1; j < n; j++) {
            if (proc[i].at <= current_time && proc[j].at <= current_time && proc[i].bt > proc[j].bt) {
                struct Process temp = proc[i];
                proc[i] = proc[j];
                proc[j] = temp;
            }
        }
    }
}

// Function to calculate Completion Time for each process
void findCompletionTime(struct Process proc[], int n) {
    int current_time = 0;
    for (int i = 0; i < n; i++) {
        if (proc[i].at > current_time) {
            current_time = proc[i].at;
        }

        // Sort processes by burst time at the current time
        sortByBurstTime(proc, n, current_time);

        // The process with the shortest burst time gets executed
        current_time += proc[i].bt;
        proc[i].ct = current_time;
    }
}

// Function to calculate Turnaround Time (TAT)
void findTurnAroundTime(struct Process proc[], int n) {
    for (int i = 0; i < n; i++) {
        proc[i].tat = proc[i].ct - proc[i].at;  // TAT = Completion time - Arrival time
    }
}

// Function to calculate Waiting Time (WT)
void findWaitingTime(struct Process proc[], int n) {
    for (int i = 0; i < n; i++) {
        proc[i].wt = proc[i].tat - proc[i].bt;  // WT = Turnaround time - Burst time
    }
}

// Function to display the results (Completion Time, Waiting Time, Turnaround Time)
void displayResults(struct Process proc[], int n) {
    float total_wt = 0, total_tat = 0;
    printf("\nProcess ID\tArrival Time\tBurst Time\tCompletion Time\tWaiting Time\tTurnaround Time\n");
    for (int i = 0; i < n; i++) {
        total_wt += proc[i].wt;
        total_tat += proc[i].tat;
        printf("%d\t\t%d\t\t%d\t\t%d\t\t%d\t\t%d\n", proc[i].id, proc[i].at, proc[i].bt, proc[i].ct, proc[i].wt, proc[i].tat);
    }

    printf("\nAverage Waiting Time: %.2f\n", total_wt / n);
    printf("Average Turnaround Time: %.2f\n", total_tat / n);
}
