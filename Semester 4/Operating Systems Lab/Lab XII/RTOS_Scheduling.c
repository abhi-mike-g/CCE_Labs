#include <stdio.h>
#include <stdlib.h>

#define MAX_TASKS 10

// Task structure
typedef struct {
    int id;                 // Task identifier
    int period;             // Task period (arrival interval)
    int execution;          // Execution time required within each period
    int remaining;          // Remaining execution time for the current period
    int next_arrival;       // Next arrival time of the task (release time)
    int absolute_deadline;  // Absolute deadline for the current instance (arrival + period)
} Task;

// Function to simulate Rate Monotonic Scheduling (RMS)
// In RMS, fixed priorities are assigned according to the task period (shorter period gets higher priority)
void simulate_RMS(Task tasks[], int num_tasks, int sim_time) {
    printf("Simulating Rate Monotonic Scheduling (RMS)\n");
    for (int time = 0; time < sim_time; time++) {
        // Check for task arrivals and refresh tasks that are released at time 'time'
        for (int i = 0; i < num_tasks; i++) {
            if (time == tasks[i].next_arrival) {
                tasks[i].remaining = tasks[i].execution;             // Reset the remaining execution time
                tasks[i].absolute_deadline = time + tasks[i].period;     // New absolute deadline = arrival + period
                tasks[i].next_arrival += tasks[i].period;                // Schedule next arrival
            }
        }

        // Among all ready tasks (with remaining execution time > 0), select the one with the highest priority
        // For RMS, tasks with a smaller period have a higher priority.
        int selected = -1;
        for (int i = 0; i < num_tasks; i++) {
            if (tasks[i].remaining > 0) {
                if (selected == -1 || tasks[i].period < tasks[selected].period) {
                    selected = i;
                }
            }
        }

        // Execute the selected task for one time unit; if no task is ready, the CPU idles.
        if (selected != -1) {
            tasks[selected].remaining--;
            printf("Time %2d: Running Task %d (RMS)\n", time, tasks[selected].id);
        } else {
            printf("Time %2d: Idle (RMS)\n", time);
        }
    }
    printf("\n");
}

// Function to simulate Earliest Deadline First Scheduling (EDF)
// In EDF, the task with the closest (earliest) absolute deadline is chosen.
void simulate_EDF(Task tasks[], int num_tasks, int sim_time) {
    printf("Simulating Earliest Deadline First Scheduling (EDF)\n");
    for (int time = 0; time < sim_time; time++) {
        // Check for task arrivals and update tasks accordingly
        for (int i = 0; i < num_tasks; i++) {
            if (time == tasks[i].next_arrival) {
                tasks[i].remaining = tasks[i].execution;
                tasks[i].absolute_deadline = time + tasks[i].period;
                tasks[i].next_arrival += tasks[i].period;
            }
        }

        // Among ready tasks, select the one with the earliest absolute deadline.
        int selected = -1;
        for (int i = 0; i < num_tasks; i++) {
            if (tasks[i].remaining > 0) {
                if (selected == -1 || tasks[i].absolute_deadline < tasks[selected].absolute_deadline) {
                    selected = i;
                }
            }
        }

        // Execute the selected task, or idle if no task is ready.
        if (selected != -1) {
            tasks[selected].remaining--;
            printf("Time %2d: Running Task %d (EDF)\n", time, tasks[selected].id);
        } else {
            printf("Time %2d: Idle (EDF)\n", time);
        }
    }
    printf("\n");
}

int main() {
    // Example setup: three periodic tasks.
    // You can modify these tasks as needed.
    int num_tasks = 3;
    Task tasks[MAX_TASKS];

    // Task 1: period = 4, execution time = 1
    tasks[0].id = 1;
    tasks[0].period = 4;
    tasks[0].execution = 1;
    tasks[0].next_arrival = 0;
    tasks[0].remaining = 0;

    // Task 2: period = 5, execution time = 2
    tasks[1].id = 2;
    tasks[1].period = 5;
    tasks[1].execution = 2;
    tasks[1].next_arrival = 0;
    tasks[1].remaining = 0;

    // Task 3: period = 20, execution time = 5
    tasks[2].id = 3;
    tasks[2].period = 20;
    tasks[2].execution = 5;
    tasks[2].next_arrival = 0;
    tasks[2].remaining = 0;

    // Total simulation time (in time units)
    int sim_time = 30;

    // To simulate both RMS and EDF separately, we need to work on independent copies of the task set.
    Task tasks_RMS[MAX_TASKS], tasks_EDF[MAX_TASKS];
    for (int i = 0; i < num_tasks; i++) {
        tasks_RMS[i] = tasks[i];
        tasks_EDF[i] = tasks[i];
    }

    // Run RMS simulation
    simulate_RMS(tasks_RMS, num_tasks, sim_time);

    // Run EDF simulation
    simulate_EDF(tasks_EDF, num_tasks, sim_time);

    return 0;
}
