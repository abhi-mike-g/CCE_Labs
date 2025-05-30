#include <stdio.h>

void Bubble_Sort(int a[], int n){
    int temp;
    for(int i = 1; i < n; i++){
        for(int j = 0; j < n-i-1; j++){
            if(a[j] > a[j+1]){
                temp = a[j];
                a[j] = a[j+1];
                a[j+1] = temp;
            }
        }
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
    Bubble_Sort(a, n);

    printf("Array after Sorting: \n");
    for (int i = 0; i < n; i++)
        printf("%d ", a[i]);

    printf("\n");
    return 0;
}
