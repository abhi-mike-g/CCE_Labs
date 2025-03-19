import java.util.Scanner;
public class Number 
{
    private double number;
    public Number() {
        this.number = 0;
    } public Number(double number) {
        this.number = number;
    } public boolean isZero() {
        return number == 0;
    } public boolean isPositive() {
        return number > 0;
    } public boolean isNegative() {
        return number < 0;
    } public boolean isOdd() {
        if (number % 1 != 0) {
            return false;
        }
        return (int) number % 2 != 0;
    } public boolean isEven() {
        if (number % 1 != 0) {
            return false; 
        }
        return (int) number % 2 == 0;
    } public boolean isPrime() {
        if (number < 2 || number % 1 != 0) {
            return false;
        }
        int n = (int) number;
        for (int i = 2; i <= Math.sqrt(n); i++) {
            if (n % i == 0) {
                return false;
            }
        }
        return true;
    } public boolean isArmstrong() {
        if (number % 1 != 0 || number < 0) {
            return false;
        }
        int n = (int) number;
        int originalNumber = n;
        int sum = 0;
        int digits = String.valueOf(n).length();
        while (n != 0) {
            int digit = n % 10;
            sum += Math.pow(digit, digits);
            n /= 10;
        }
        return sum == originalNumber;
    }
    public static void main(String[] args) {
        Scanner sc = new Scanner(System.in);
        System.out.print("Enter a number: ");
        double userNumber = sc.nextDouble();
        Number number = new Number(userNumber);
        System.out.println("Is Zero? " + number.isZero());
        System.out.println("Is Positive? " + number.isPositive());
        System.out.println("Is Negative? " + number.isNegative());
        System.out.println("Is Odd? " + number.isOdd());
        System.out.println("Is Even? " + number.isEven());
        System.out.println("Is Prime? " + number.isPrime());
        System.out.println("Is Armstrong? " + number.isArmstrong());
        sc.close();
    }
}