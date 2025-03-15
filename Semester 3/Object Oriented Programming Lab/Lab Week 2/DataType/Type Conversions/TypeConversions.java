import java.util.Scanner;
public class TypeConversions 
{
    public static void main(String[] args) 
    {
        Scanner scanner = new Scanner(System.in);
        System.out.print("Enter an int number: ");
        int intNumber = scanner.nextInt();
        System.out.print("Enter a double number: ");
        double doubleNumber = scanner.nextDouble();
        System.out.print("Enter a char: ");
        char charValue = scanner.next().charAt(0);
        byte intToByte = (byte) intNumber;
        System.out.println("Int to byte: " + intToByte);
        int charToInt = (int) charValue;
        System.out.println("Char to int: " + charToInt);
        byte doubleToByte = (byte) doubleNumber;
        System.out.println("Double to byte: " + doubleToByte);
        int doubleToInt = (int) doubleNumber;
        System.out.println("Double to int: " + doubleToInt);
    }
}
