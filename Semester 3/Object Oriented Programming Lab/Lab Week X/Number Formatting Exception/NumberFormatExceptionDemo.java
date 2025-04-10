import java.util.Scanner;
public class NumberFormatExceptionDemo {
    public static void main(String[] args) {
        Scanner sc = new Scanner(System.in);
        try {
            System.out.print("Enter a number: ");
            String input = sc.nextLine();
            int number = Integer.parseInt(input);
            System.out.println("The entered number is: " + number);
        } catch (NumberFormatException e) {
            System.out.println("Invalid input! Please enter a valid number.");
        } finally {
            sc.close();
        }
    }
}
