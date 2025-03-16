import java.util.Scanner;
public class Prime 
{
    public static void main(String[] args) 
    {
        Scanner scanner = new Scanner(System.in);
        System.out.print("Enter the start of the range (n): ");
        int n = scanner.nextInt();
        System.out.print("Enter the end of the range (m): ");
        int m = scanner.nextInt();
        System.out.println("Prime numbers between " + n + " and " + m + ":");
        for (int i = n; i <= m; i++) 
            if (isPrime(i)) 
                System.out.print(i + " ");
    }
    public static boolean isPrime(int num) 
    {
        if (num <= 1) 
            return false; // 1 and numbers below are not prime
        for (int i = 2; i <= Math.sqrt(num); i++) 
            if (num % i == 0) 
                return false; // Found a divisor, not prime
        return true; // No divisors found, it's prime
    }
}
