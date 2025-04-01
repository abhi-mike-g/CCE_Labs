#include <stdio.h>
#include <stdlib.h>
#include <limits.h>

// Function to find the absolute difference
int abs_diff(int a, int b) {
    return (a > b) ? (a - b) : (b - a);
}

// SSTF Algorithm
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

// SCAN Algorithm
void scan(int requests[], int n, int head, int disk_size, char direction) {
    int seek_sequence[n + 2];
    int seek_count = 0;
    int left[n], right[n];
    int left_count = 0, right_count = 0;

    for (int i = 0; i < n; i++) {
        if (requests[i] <= head) {
            left[left_count++] = requests[i];
        } else {
            right[right_count++] = requests[i];
        }
    }

    // Sort left and right arrays
    for (int i = 0; i < left_count - 1; i++) {
        for (int j = 0; j < left_count - i - 1; j++) {
            if (left[j] < left[j + 1]) {
                int temp = left[j];
                left[j] = left[j + 1];
                left[j + 1] = temp;
            }
        }
    }

    for (int i = 0; i < right_count - 1; i++) {
        for (int j = 0; j < right_count - i - 1; j++) {
            if (right[j] > right[j + 1]) {
                int temp = right[j];
                right[j] = right[j + 1];
                right[j + 1] = temp;
            }
        }
    }

    int seq_index = 0;
    if (direction == 'l') {
        for (int i = 0; i < left_count; i++) {
            seek_sequence[seq_index++] = left[i];
            seek_count += abs_diff(head, left[i]);
            head = left[i];
        }
        seek_count += head;
        head = 0;
        for (int i = 0; i < right_count; i++) {
            seek_sequence[seq_index++] = right[i];
            seek_count += abs_diff(head, right[i]);
            head = right[i];
        }
    } else {
        for (int i = 0; i < right_count; i++) {
            seek_sequence[seq_index++] = right[i];
            seek_count += abs_diff(head, right[i]);
            head = right[i];
        }
        seek_count += abs_diff(head, disk_size - 1);
        head = disk_size - 1;
        for (int i = left_count - 1; i >= 0; i--) {
            seek_sequence[seq_index++] = left[i];
            seek_count += abs_diff(head, left[i]);
            head = left[i];
        }
    }

    printf("Seek Sequence: ");
    for (int i = 0; i < seq_index; i++) {
        printf("%d ", seek_sequence[i]);
    }
    printf("\nTotal Seek Count: %d\n", seek_count);
}

// C-SCAN Algorithm
void cscan(int requests[], int n, int head, int disk_size, char direction) {
    int seek_sequence[n + 2];
    int seek_count = 0;
    int left[n], right[n];
    int left_count = 0, right_count = 0;

    for (int i = 0; i < n; i++) {
        if (requests[i] <= head) {
            left[left_count++] = requests[i];
        } else {
            right[right_count++] = requests[i];
        }
    }

    // Sort left and right arrays
    for (int i = 0; i < left_count - 1; i++) {
        for (int j = 0; j < left_count - i - 1; j++) {
            if (left[j] < left[j + 1]) {
                int temp = left[j];
                left[j] = left[j + 1];
                left[j + 1] = temp;
            }
        }
    }

    for (int i = 0; i < right_count - 1; i++) {
        for (int j = 0; j < right_count - i - 1; j++) {
            if (right[j] > right[j + 1]) {
                int temp = right[j];
                right[j] = right[j + 1];
                right[j + 1] = temp;
            }
        }
    }

    int seq_index = 0;
    if (direction == 'l') {
        for (int i = 0; i < left_count; i++) {
            seek_sequence[seq_index++] = left[i];
            seek_count += abs_diff(head, left[i]);
            head = left[i];
        }
        seek_count += head;
        head = disk_size -1;
        for (int i = right_count -1; i>=0; i--){
            seek_sequence[seq_index++] = right[i];
            seek_count += abs_diff(head, right[i]);
            head = right[i];
        }

    } else {
        for (int i = 0; i < right_count; i++) {
            seek_sequence[seq_index++] = right[i];
            seek_count += abs_diff(head, right[i]);
            head = right[i];
        }
        seek_count += abs_diff(head, disk_size - 1);
        head = 0;
        for (int i = 0; i < left_count; i++) {
            seek_sequence[seq_index++] = left[i];
            seek_count += abs_diff(head, left[i]);
            head = left[i];
        }
    }

    printf("Seek Sequence: ");
    for (int i = 0; i < seq_index; i++) {
        printf("%d ", seek_sequence[i]);
    }
    printf("\nTotal Seek Count: %d\n", seek_count);
}

// C-LOOK Algorithm
void clook(int requests[], int n, int head, char direction) {
    int seek_sequence[n];
    int seek_count = 0;
    int left[n], right[n];
    int left_count = 0, right_count = 0;

    for (int i = 0; i < n; i++) {
        if (requests[i] <= head) {
            left[left_count++] = requests[i];
        } else {
            right[right_count++] = requests[i];
        }
    }

    // Sort left and right arrays
    for (int i = 0; i < left_count - 1; i++) {
        for (int j = 0; j < left_count - i - 1; j++) {
            if (left[j] < left[j + 1]) {
                int temp = left[j];
                left[j] = left[j + 1];
                left[j + 1] = temp;
            }
        }
    }

    for (int i = 0; i < right_count - 1; i++) {
        for (int j = 0; j < right_count - i - 1; j++) {
            if (right[j] > right[j + 1]) {
                int temp = right[j];
                right[j] = right[j + 1];
                right[j + 1] = temp;
            }
        }
    }

    int seq_index = 0;
    if (direction == 'l') {
        for (int i = 0; i < left_count; i++) {
            seek_sequence[seq_index++] = left[i];
            seek_count += abs_diff(head, left[i]);
            head = left[i];
        }
        for (int i = right_count -1; i>=0; i--){
            seek_sequence[seq_index++] = right[i];
            seek_count += abs_diff(head, right[i]);
            head = right[i];
        }
    } else {
        for (int i = 0; i < right_count; i++) {
            seek_sequence[seq_index++] = right[i];
            seek_count += abs_diff(head, right[i]);
            head = right[i];
        }
        for (int i = 0; i < left_count; i++) {
            seek_sequence[seq_index++] = left[i];
            seek_count += abs_diff(head, left[i]);
            head = left[i];
        }
    }

    printf("Seek Sequence: ");
    for (int i = 0; i < seq_index; i++) {
        printf("%d ", seek_sequence[i]);
    }
    printf("\nTotal Seek Count: %d\n", seek_count);
}

int main() {
    int requests[100];
    int n, head, disk_size;
    char direction;
    int choice;

    while (1) {
        printf("\nDisk Scheduling Algorithms Simulation\n");
        printf("1. SSTF\n");
        printf("2. SCAN\n");
        printf("3. C-SCAN\n");
        printf("4. C-LOOK\n");
        printf("5. Exit\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);

        if (choice == 5) {
            break;
        }

        printf("Enter number of requests: ");
        scanf("%d", &n);

        printf("Enter request sequence: ");
        for (int i = 0; i < n; i++) {
            scanf("%d", &requests[i]);
        }

        printf("Enter initial head position: ");
        scanf("%d", &head);

        switch (choice) {
            case 1:
                sstf(requests, n, head);
                break;
            case 2:
                printf("Enter disk size: ");
                scanf("%d", &disk_size);
                printf("Enter direction (l/r): ");
                scanf(" %c", &direction);
                scan(requests, n, head, disk_size, direction);
                break;
            case 3:
                printf("Enter disk size: ");
                scanf("%d", &disk_size);
                printf("Enter direction (l/r): ");
                scanf(" %c", &direction);
                cscan(requests, n, head, disk_size, direction);
                break;
            case 4:
                printf("Enter direction (l/r): ");
                scanf(" %c", &direction);
                clook(requests, n, head, direction);
                break;
            default:
                printf("Invalid choice!\n");
        }
    }

    return 0;
}