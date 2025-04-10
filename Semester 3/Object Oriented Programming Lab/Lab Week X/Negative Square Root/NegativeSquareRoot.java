import java.util.Scanner;
class NegativeNumberException extends Exception {
    public NegativeNumberException(String message) {
        super(message);
    }
}
public class NegativeSquareRoot {
    public static void main(String[] args) {
        Scanner sc = new Scanner(System.in);
        double num = 0;
        System.out.print("Enter a number: ");
        try {
            num = sc.nextDouble();
            if (num < 0) {
                throw new NegativeNumberException("You entered a negative number: " + num);
            }
            double sqrtValue = Math.sqrt(num);
            System.out.println("The square root of " + num + " is: " + sqrtValue);
        } catch (NegativeNumberException e) {
            System.out.println(e.getMessage());
            double sqrtValue = Math.sqrt(Math.abs(num));
            System.out.println("The square root of the negative number is: " + sqrtValue + "i (imaginary number)");
        } catch (Exception e) {
            System.out.println("Invalid input. Please enter a valid number.");
        } finally {
            sc.close();
        }
    }
}
