import java.util.Scanner;
public class SymmetricMatrix 
{
    public static void main(String[] args) 
    {
        Scanner sc = new Scanner(System.in);
        System.out.print("Enter the size of the square matrix (n x n): ");
        int n = sc.nextInt();
        int[][] matrix = new int[n][n];
        System.out.println("Enter the elements of the matrix:");
        for (int i = 0; i < n; i++) 
            for (int j = 0; j < n; j++) 
            {
                System.out.print("Element [" + i + "][" + j + "]: ");
                matrix[i][j] = sc.nextInt();
            }
        boolean isSymmetric = true;
        for (int i = 0; i < n; i++) 
        {
            for (int j = 0; j < n; j++) 
                if (matrix[i][j] != matrix[j][i]) 
                {
                    isSymmetric = false;
                    break;
                }
            if (!isSymmetric) break;
        }
        if (isSymmetric) 
            System.out.println("The given matrix is symmetric.");
        else 
            System.out.println("The given matrix is not symmetric.");
    }
}
