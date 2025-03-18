import java.util.Scanner;
public class MagicSquare 
{
    public static boolean isMagicSquare(int[][] matrix, int n) 
    {
        int sum = 0;
        for (int i = 0; i < n; i++) 
            sum += matrix[0][i];
        for (int i = 1; i < n; i++) 
        {
            int rowSum = 0;
            for (int j = 0; j < n; j++) 
                rowSum += matrix[i][j];
            if (rowSum != sum) 
                return false;
        }
        for (int i = 0; i < n; i++) 
        {
            int colSum = 0;
            for (int j = 0; j < n; j++) 
                colSum += matrix[j][i];
            if (colSum != sum) 
                return false;
        }
        int principalDiagSum = 0;
        for (int i = 0; i < n; i++) 
            principalDiagSum += matrix[i][i];
        if (principalDiagSum != sum) 
            return false;
        int nonPrincipalDiagSum = 0;
        for (int i = 0; i < n; i++) 
            nonPrincipalDiagSum += matrix[i][n - 1 - i];
        if (nonPrincipalDiagSum != sum) 
            return false;
        return true;
    }
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
        if (isMagicSquare(matrix, n)) 
            System.out.println("The matrix is a Magic Square.");
        else
            System.out.println("The matrix is NOT a Magic Square.");
        sc.close();
    }
}
