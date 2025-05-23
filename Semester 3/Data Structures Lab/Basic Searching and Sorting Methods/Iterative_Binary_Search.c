#include <stdio.h>
#include <stdlib.h>

int main() {
    int a[100], n, mid, beg, ele, end;

    printf("Enter number of elements in the array: ");
    scanf("%d", &n);

    printf("Enter the elements in sorted order:\n");
    for(int i = 0; i < n; i++) {
        scanf("%d", &a[i]);
    }

    printf("Enter the search element: ");
    scanf("%d", &ele);

    beg = 0;
    end = n - 1; // Corrected to n - 1

    while(beg <= end) {
        mid = (beg + end) / 2;

        if(a[mid] == ele) {
            printf("Element %d found at position %d\n", ele, mid);
            exit(0);
        } else if(ele < a[mid]) {
            end = mid - 1;
        } else {
            beg = mid + 1;
        }
    }

    printf("Element does not exist!\n");
    return 0;
}
