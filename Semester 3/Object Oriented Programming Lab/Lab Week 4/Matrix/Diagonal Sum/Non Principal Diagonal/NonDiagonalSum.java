import java.util.Scanner;

public class NonDiagonalSum 
{
    public static void main(String[] args) 
    {
        Scanner sc = new Scanner(System.in);

        System.out.print("Enter the size of the square matrix (n x n): ");
        int n = sc.nextInt();

        int[][] mat = new int[n][n];

        System.out.println("Enter the elements of the matrix:");
        for (int i = 0; i < n; i++) 
            for (int j = 0; j < n; j++) 
            {
                System.out.print("Element [" + i + "][" + j + "]: ");
                mat[i][j] = sc.nextInt();
            }

        int sum = 0;

        System.out.println("Non-Diagonal Elements are: ");

        for (int i = 0; i < n; i++) 
            for (int j = 0; j < n; j++) 
                if (i != j && (i + j) != (n - 1)) 
                {
                    System.out.print(mat[i][j] + " ");
                    sum += mat[i][j];
                }

        System.out.println("\nSum of Non-Diagonal Elements: " + sum);
    }
}
