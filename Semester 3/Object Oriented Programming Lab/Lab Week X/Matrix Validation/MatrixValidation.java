import java.util.InputMismatchException;
import java.util.Scanner;
public class MatrixValidation {
    public static void main(String[] args) {
        Scanner sc = new Scanner(System.in);
        try {
            System.out.print("Enter the number of rows in the matrix: ");
            int rows = sc.nextInt();
            System.out.print("Enter the number of columns in the matrix: ");
            int columns = sc.nextInt();
            if (rows == columns) {
                System.out.println("This is a valid square matrix.");
            } else {
                System.out.println("This is NOT a square matrix.");
            }
        } catch (InputMismatchException e) {
            System.out.println("Invalid input! Please enter valid integers.");
        } finally {
            sc.close();
        }
    }
}
