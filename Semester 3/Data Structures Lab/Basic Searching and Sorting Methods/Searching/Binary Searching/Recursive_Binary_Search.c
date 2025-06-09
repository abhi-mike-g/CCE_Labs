#include <stdio.h>

int recursiveBinarySearch(int a[], int left, int right, int target) {
    if (left > right) {
        return -1;
    }

    int mid = left + (right - left) / 2;

    if (a[mid] == target) {
        return mid;
    }

    if (a[mid] > target) {
        return recursiveBinarySearch(a, left, mid - 1, target);
    }

    return recursiveBinarySearch(a, mid + 1, right, target);
}

int main() {
    int a[100], n, ele;

    printf("Enter the size of the array: ");
    scanf("%d", &n);

    printf("Enter %d array elements: \n", n);
    for(int i = 0; i < n; i++)
        scanf("%d", &a[i]);

    printf("Enter the search element: ");
    scanf("%d", &ele);

    int result = recursiveBinarySearch(a, 0, n - 1, ele);

    if (result != -1) {
        printf("Element found at index: %d\n", result);
    } else {
        printf("Element not found in the array.\n");
    }

    return 0;
}
