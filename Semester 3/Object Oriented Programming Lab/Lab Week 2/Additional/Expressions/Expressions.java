import java.util.Scanner;
public class Expressions
{
    public static void main(String[] args) 
    {
        Scanner sc = new Scanner(System.in);
        System.out.print("Enter value for a: ");
        int a = sc.nextInt();
        System.out.print("Enter value for b: ");
        int b = sc.nextInt();
        int a1 = (a << 2) + (b >> 2);
        boolean a2 = (b > 0);
        int a3 = (a + b * 100) / 10;
        int a4 = a & b;
        System.out.println("Result of (a << 2) + (b >> 2): " + a1);
        System.out.println("Result of (b > 0): " + a2);
        System.out.println("Result of (a + b * 100) / 10: " + a3);
        System.out.println("Result of a & b: " + a4);
        sc.close();
    }
}
