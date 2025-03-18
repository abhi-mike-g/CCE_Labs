import java.util.Scanner;
public class MatrixOperations 
{
    public static void main(String[] args) 
    {
        Scanner sc = new Scanner(System.in);
        System.out.println("Enter the number of rows and columns for Matrix A:");
        int rowsA = sc.nextInt();
        int colsA = sc.nextInt();
        System.out.println("Enter the number of rows and columns for Matrix B:");
        int rowsB = sc.nextInt();
        int colsB = sc.nextInt();
        int[][] A = new int[rowsA][colsA];
        int[][] B = new int[rowsB][colsB];
        System.out.println("Enter the elements of Matrix A:");
        for (int i = 0; i < rowsA; i++) 
            for (int j = 0; j < colsA; j++) 
            {
                System.out.print("A[" + i + "][" + j + "]: ");
                A[i][j] = sc.nextInt();
            }
        System.out.println("Enter the elements of Matrix B:");
        for (int i = 0; i < rowsB; i++) 
            for (int j = 0; j < colsB; j++) 
            {
                System.out.print("B[" + i + "][" + j + "]: ");
                B[i][j] = sc.nextInt();
            }
        if (rowsA == rowsB && colsA == colsB) 
        {
            int[][] sumMatrix = new int[rowsA][colsA];
            System.out.println("Resultant Matrix after Addition:");
            for (int i = 0; i < rowsA; i++) 
            {
                for (int j = 0; j < colsA; j++) 
                {
                    sumMatrix[i][j] = A[i][j] + B[i][j];
                    System.out.print(sumMatrix[i][j] + " ");
                }
                System.out.println();
            }
        } 
        else 
            System.out.println("Matrix addition is not possible because the dimensions do not match.");
        if (colsA == rowsB) 
        {
            int[][] productMatrix = new int[rowsA][colsB];
            System.out.println("Resultant Matrix after Multiplication:");
            for (int i = 0; i < rowsA; i++) 
            {
                for (int j = 0; j < colsB; j++) 
                {
                    productMatrix[i][j] = 0;
                    for (int k = 0; k < colsA; k++) 
                        productMatrix[i][j] += A[i][k] * B[k][j];
                    System.out.print(productMatrix[i][j] + " ");
                }
                System.out.println();
            }
        } 
        else 
            System.out.println("Matrix multiplication is not possible because the number of columns in Matrix A does not equal the number of rows in Matrix B.");
    }
}
