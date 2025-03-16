import java.util.Scanner;

public class SumSeries {
    // Function to calculate the sum of the series
    public static double sumSeries(int terms) {
        double sum = 1.0;
        for (int i = 2; i <= terms; i++) {
            sum += Math.pow((1.0 / i), i);
        }
        return sum;
    }

    public static void main(String[] args) {
        Scanner scanner = new Scanner(System.in);

        // Input the number of terms in the series
        System.out.print("Enter the number of terms in the series: ");
        int terms = scanner.nextInt();

        // Calculate the sum of the series
        double sum = sumSeries(terms);

        // Display the result
        System.out.println("Sum of the series = " + sum);

        scanner.close();
    }
}
