import java.util.Scanner;
public class PrincipalDiagonalSum 
{
    public static void main(String[] args) 
    {
        Scanner sc = new Scanner(System.in);
        System.out.print("Enter the size of the square matrix (n x n): ");
        int n = sc.nextInt();
        int[][] matrix = new int[n][n];
        System.out.println("Enter the elements of the matrix:");
        for (int i = 0; i < n; i++) 
        {
            for (int j = 0; j < n; j++) 
            {
                System.out.print("Element [" + i + "][" + j + "]: ");
                matrix[i][j] = sc.nextInt();
            }
        }
        int sum = 0;
        System.out.println("Principal Diagonal Elements are: ");
        for (int i = 0; i < n; i++) 
        {
            System.out.print(matrix[i][i] + " ");
            sum += matrix[i][i];
        }
        System.out.println("\nSum of Principal Diagonal Elements: " + sum);
    }
}
