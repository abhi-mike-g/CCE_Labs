#include <stdio.h>

int main() {
    int a[100], n, key, found = 0; // Added a flag to track if the element is found

    printf("Enter Array Size: ");
    scanf("%d", &n);

    printf("Enter the elements of the array:\n");
    for(int i = 0; i < n; i++) {
        scanf("%d", &a[i]);
    }

    printf("Enter Search Element: ");
    scanf("%d", &key);

    for(int i = 0; i < n; i++) {
        if(a[i] == key) {
            printf("%d found at position %d\n", key, i);
            found = 1; // Set the flag to indicate the element was found
            break; // Exit the loop once the element is found
        }
    }

    if (!found) {
        printf("Element does not exist!\n");
    }

    return 0;
}
