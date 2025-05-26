#include <stdio.h>

void Selection_Sort(int a[], int n) {
    int index, smallest, i, j;
    for (i = 0; i < n - 1; i++) {
        index = i;
        smallest = a[i];
        for (j = i + 1; j < n; j++) {
            if (a[j] < smallest) {
                smallest = a[j];
                index = j;
            }
        }
        if (index != i) {
            int temp = a[i];
            a[i] = a[index];
            a[index] = temp;
        }
    }}

int main() {
    int a[100], n;

    printf("Enter Array Size: ");
    scanf("%d", &n);

    printf("Enter Array Elements: \n");
    for (int i = 0; i < n; i++)
        scanf("%d", &a[i]);

    printf("Array before Sorting: \n");
    for (int i = 0; i < n; i++)
        printf("%d ", a[i]);

    printf("\n");
    Selection_Sort(a, n);

    printf("Array after Sorting: \n");
    for (int i = 0; i < n; i++)
        printf("%d ", a[i]);

    printf("\n");
    return 0;
}
