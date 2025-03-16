import java.util.Scanner;

public class SinSeries {
    // Function to calculate the factorial of a number
    public static double factorial(int n) {
        double fact = 1;
        for (int i = 1; i <= n; i++) {
            fact *= i;
        }
        return fact;
    }

    // Function to calculate sin(x) using the series expansion
    public static double sin(double x, int terms) {
        double sinX = 0.0;
        for (int i = 0; i < terms; i++) {
            int sign = (i % 2 == 0) ? 1 : -1;
            sinX += sign * Math.pow(x, 2 * i + 1) / factorial(2 * i + 1);
        }
        return sinX;
    }

    public static void main(String[] args) {
        Scanner scanner = new Scanner(System.in);

        // Input the value of x (in radians)
        System.out.print("Enter the value of x (in radians): ");
        double x = scanner.nextDouble();

        // Input the number of terms in the series
        System.out.print("Enter the number of terms in the series: ");
        int terms = scanner.nextInt();

        // Calculate sin(x) using the series expansion
        double sinX = sin(x, terms);

        // Display the result
        System.out.println("Sin(" + x + ") = " + sinX);

        scanner.close();
    }
}
