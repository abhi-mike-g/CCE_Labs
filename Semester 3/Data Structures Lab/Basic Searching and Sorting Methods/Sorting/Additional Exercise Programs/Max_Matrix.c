#include <stdio.h>
int main(){
    int A[10][10], B[10][10], C[10][10] = {0};
    int n, m, i, j;
    printf("Enter Dimensions of the matrix ([Row_size]*[Column_Size]) : ");
    scanf("%d%d", &m, &n);

    printf("\n");

    printf("Enter elements of Matrix A: \n");
    for(i = 0; i < m; i++)
        for(j = 0; j < n; j++)
            scanf("%d", &A[i][j]);

    printf("\n");

    printf("Enter elements of Matrix B: \n");
    for(i = 0; i < m; i++)
        for(j = 0; j < n; j++)
            scanf("%d", &B[i][j]);

    printf("\n");

    for(i = 0; i < m; i++)
        for(j = 0; j < n; j++)
            if(A[i][j] > B[i][j])
                C[i][j] = A[i][j];
            else
                C[i][j] = B[i][j];


    printf("The Matrix C(i, j) = Max[A(i, j), B(i, j)]: \n");
    for(i = 0; i < m; i++){
        for(j = 0; j < n; j++){
            printf("%d\t", C[i][j]);
        }
        printf("\n");
    }

    return 0;
}
