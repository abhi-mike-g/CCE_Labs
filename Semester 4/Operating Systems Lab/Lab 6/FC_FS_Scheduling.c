#include <stdio.h>

struct Process {
    int id;         // Process ID
    int bt;         // Burst time
    int ct;         // Completion time
    int wt;         // Waiting time
    int tat;        // Turnaround time
};

void findCompletionTime(struct Process proc[], int n);
void findWaitingTime(struct Process proc[], int n);
void findTurnAroundTime(struct Process proc[], int n);
void displayResults(struct Process proc[], int n);

int main() {
    int n;
    
    // Input number of processes
    printf("Enter the number of processes: ");
    scanf("%d", &n);
    
    struct Process proc[n];
    
    // Input burst time for each process
    for (int i = 0; i < n; i++) {
        proc[i].id = i + 1;
        printf("Enter burst time for Process %d: ", proc[i].id);
        scanf("%d", &proc[i].bt);
    }

    // FCFS Scheduling Algorithm
    findCompletionTime(proc, n);
    findTurnAroundTime(proc, n);
    findWaitingTime(proc, n);
    displayResults(proc, n);

    return 0;
}

// Function to calculate Completion Time for each process
void findCompletionTime(struct Process proc[], int n) {
    proc[0].ct = proc[0].bt;  // First process completes after its burst time
    for (int i = 1; i < n; i++) {
        proc[i].ct = proc[i - 1].ct + proc[i].bt;  // Completion time = Previous completion time + burst time
    }
}

// Function to calculate Turnaround Time (TAT)
void findTurnAroundTime(struct Process proc[], int n) {
    for (int i = 0; i < n; i++) {
        proc[i].tat = proc[i].ct;  // TAT = Completion time (since arrival time is 0)
    }
}

// Function to calculate Waiting Time (WT)
void findWaitingTime(struct Process proc[], int n) {
    for (int i = 0; i < n; i++) {
        proc[i].wt = proc[i].tat - proc[i].bt;  // WT = TAT - Burst time
    }
}

// Function to display the results (Completion Time, Waiting Time, Turnaround Time)
void displayResults(struct Process proc[], int n) {
    float total_wt = 0, total_tat = 0;
    printf("\nProcess ID\tBurst Time\tCompletion Time\tWaiting Time\tTurnaround Time\n");
    for (int i = 0; i < n; i++) {
        total_wt += proc[i].wt;
        total_tat += proc[i].tat;
        printf("%d\t\t%d\t\t%d\t\t%d\t\t%d\n", proc[i].id, proc[i].bt, proc[i].ct, proc[i].wt, proc[i].tat);
    }

    printf("\nAverage Waiting Time: %.2f\n", total_wt / n);
    printf("Average Turnaround Time: %.2f\n", total_tat / n);
}
