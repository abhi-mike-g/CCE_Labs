#include <stdio.h>
#include <stdbool.h>

bool isMagicSquare(int matrix[][10], int n) {
    int magicConstant = n * (n * n + 1) / 2;

    for (int i = 0; i < n; i++) {
        int rowSum = 0;
        for (int j = 0; j < n; j++) {
            rowSum += matrix[i][j];
        }
        if (rowSum != magicConstant) {
            return false;
        }
    }

    for (int j = 0; j < n; j++) {
        int colSum = 0;
        for (int i = 0; i < n; i++) {
            colSum += matrix[i][j];
        }
        if (colSum != magicConstant) {
            return false;
        }
    }

    int diag1Sum = 0, diag2Sum = 0;
    for (int i = 0; i < n; i++) {
        diag1Sum += matrix[i][i];
        diag2Sum += matrix[i][n - 1 - i];
    }
    if (diag1Sum != magicConstant || diag2Sum != magicConstant) {
        return false;
    }

    bool found[100] = {false};
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            if (matrix[i][j] < 1 || matrix[i][j] > n * n || found[matrix[i][j]]) {
                return false;
            }
            found[matrix[i][j]] = true;
        }
    }

    return true;
}

int main() {
    int A[10][10], B[10][10], SUM[10][10], PROD[10][10], n;

    printf("Enter the dimensions of Matrix (n x n): ");
    scanf("%d", &n);

    printf("\nEnter the elements of Matrix A:\n");
    for (int i = 0; i < n; i++)
        for (int j = 0; j < n; j++)
            scanf("%d", &A[i][j]);

    printf("\nEnter the elements of Matrix B:\n");
    for (int i = 0; i < n; i++)
        for (int j = 0; j < n; j++)
            scanf("%d", &B[i][j]);

    for (int i = 0; i < n; i++)
        for (int j = 0; j < n; j++)
            SUM[i][j] = A[i][j] + B[i][j];

    for (int i = 0; i < n; i++)
        for (int j = 0; j < n; j++) {
            PROD[i][j] = 0;
            for (int k = 0; k < n; k++) {
                PROD[i][j] += A[i][k] * B[k][j];
            }
        }

    printf("\n");

    printf("SUM Matrix (A + B):\n");
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            printf("%d\t", SUM[i][j]);
        }
        printf("\n");
    }

    printf("\nProduct Matrix (A * B):\n");
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            printf("%d\t", PROD[i][j]);
        }
        printf("\n");
    }

    printf("\n");

    if (isMagicSquare(A, n))
        printf("Matrix A is a magic square\n");
    else
        printf("Matrix A is NOT a magic square\n");

    printf("\n");

    if (isMagicSquare(B, n))
        printf("Matrix B is a magic square\n");
    else
        printf("Matrix B is NOT a magic square\n");

    printf("\n");

    if (isMagicSquare(SUM, n))
        printf("The Sum Matrix is a magic square\n");
    else
        printf("The Sum Matrix is NOT a magic square\n");

    printf("\n");

    if (isMagicSquare(PROD, n))
        printf("The Product Matrix is a magic square\n");
    else
        printf("The Product Matrix is NOT a magic square\n");

    return 0;
}
