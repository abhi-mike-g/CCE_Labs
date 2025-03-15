import java.util.Scanner;
public class BitwiseOperations 
{
    public static void main(String[] args) 
    {
        Scanner scanner = new Scanner(System.in);
        System.out.print("Enter a number: ");
        int num = scanner.nextInt();
        int mb2 = num << 1;
        System.out.println("Multiplying the number by 2 using bitwise operator: " + mb2);
        int db2 = num >> 1;
        System.out.println("Dividing the number by 2 using bitwise operator: " + db2);

        scanner.close();
    }
}
