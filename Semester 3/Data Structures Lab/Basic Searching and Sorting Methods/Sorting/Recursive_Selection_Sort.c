#include <stdio.h>

void swap(int *a, int *b) {
    int temp = *a;
    *a = *b;
    *b = temp;
}

void recursiveSelectionSort(int arr[], int n, int index) {
    if (index >= n - 1) {
        return;
    }

    int minIndex = index;
    for (int j = index + 1; j < n; j++) {
        if (arr[j] < arr[minIndex]) {
            minIndex = j;
        }
    }

    swap(&arr[index], &arr[minIndex]);

    recursiveSelectionSort(arr, n, index + 1);
}

void printArray(int arr[], int n) {
    for (int i = 0; i < n; i++) {
        printf("%d ", arr[i]);
    }
    printf("\n");
}

int main() {
    int arr[100], n;

    printf("Enter the size of the array: ");
    scanf("%d", &n);

    printf("Enter Array Elements: \n");
    for(int i = 0; i < n; i++)
        scanf("%d", &arr[i]);

    printf("Original array: \n");
    printArray(arr, n);

    recursiveSelectionSort(arr, n, 0);

    printf("Sorted array: \n");
    printArray(arr, n);

    return 0;
}
