#include <stdio.h>
#include <stdlib.h>

void merge(int a[], int left, int mid, int right) {
    int n1 = mid - left + 1;
    int n2 = right - mid;

    int *L = (int *)malloc(n1 * sizeof(int));
    int *R = (int *)malloc(n2 * sizeof(int));

    for (int i = 0; i < n1; i++)
        L[i] = a[left + i];
    for (int j = 0; j < n2; j++)
        R[j] = a[mid + 1 + j];

    int i = 0, j = 0, k = left;
    while (i < n1 && j < n2) {
        if (L[i] <= R[j])
            a[k++] = L[i++];
        else
            a[k++] = R[j++];
    }

    while (i < n1)
        a[k++] = L[i++];

    while (j < n2)
        a[k++] = R[j++];

    free(L);
    free(R);
}

void Merge_Sort(int a[], int left, int right) {
    if (left < right) {
        int mid = left + (right - left) / 2;
        Merge_Sort(a, left, mid);
        Merge_Sort(a, mid + 1, right);
        merge(a, left, mid, right);
    }
}

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
    Merge_Sort(a, 0, n - 1);

    printf("Array after Sorting: \n");
    for (int i = 0; i < n; i++)
        printf("%d ", a[i]);

    printf("\n");
    return 0;
}
