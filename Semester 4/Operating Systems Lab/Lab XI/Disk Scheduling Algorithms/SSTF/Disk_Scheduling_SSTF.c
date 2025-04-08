// sstf_menu.c
#include <stdio.h>
#include <stdlib.h>
#include <limits.h>

int abs_diff(int a, int b) {
    return (a > b) ? (a - b) : (b - a);
}

void sstf(int requests[], int n, int head) {
    int seek_sequence[n];
    int seek_count = 0;
    int visited[n];
    int current_head = head;
    int shortest_seek, shortest_index;

    for (int i = 0; i < n; i++) {
        visited[i] = 0;
    }

    for (int i = 0; i < n; i++) {
        shortest_seek = INT_MAX;
        shortest_index = -1;

        for (int j = 0; j < n; j++) {
            if (!visited[j]) {
                int seek = abs_diff(requests[j], current_head);
                if (seek < shortest_seek) {
                    shortest_seek = seek;
                    shortest_index = j;
                }
            }
        }

        seek_sequence[i] = requests[shortest_index];
        seek_count += shortest_seek;
        current_head = requests[shortest_index];
        visited[shortest_index] = 1;
    }

    printf("Seek Sequence: ");
    for (int i = 0; i < n; i++) {
        printf("%d ", seek_sequence[i]);
    }
    printf("\nTotal Seek Count: %d\n", seek_count);
}

int main() {
    int requests[100];
    int n, head;
    int choice;

    while (1) {
        printf("\nDisk Scheduling Algorithm Simulation (SSTF)\n");
        printf("1. Run SSTF Algorithm\n");
        printf("2. Exit\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);

        switch (choice) {
            case 1:
                printf("Enter number of requests: ");
                scanf("%d", &n);

                printf("Enter request sequence: ");
                for (int i = 0; i < n; i++) {
                    scanf("%d", &requests[i]);
                }

                printf("Enter initial head position: ");
                scanf("%d", &head);

                sstf(requests, n, head);
                break;
            case 2:
                printf("Exiting...\n");
                return 0;
            default:
                printf("Invalid choice!\n");
        }
    }

    return 0;
}