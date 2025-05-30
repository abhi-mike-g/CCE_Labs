#include <stdio.h>

void Insertion_Sort(int a[], int n){
    for(int i = 1; i<n; i++){
        int key = a[i];
        int j = i-1;
    while(j >= 0 && a[j] > key){
        a[j+1] = a[j];
        j--;
    }
    a[j+1] = key;
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
    Insertion_Sort(a, n);

    printf("Array after Sorting: \n");
    for (int i = 0; i < n; i++)
        printf("%d ", a[i]);

    printf("\n");
    return 0;
}
