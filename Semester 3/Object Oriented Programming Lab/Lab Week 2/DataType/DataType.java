import java.util.Scanner;
public class DataType
{
    public static void main(String[] args) 
    {
        Scanner scanner = new Scanner(System.in);
        System.out.print("Enter an integer: ");
        int intValue = scanner.nextInt();
        System.out.print("Enter a double: ");
        double doubleValue = scanner.nextDouble();
        System.out.print("Enter a character: ");
        char charValue = scanner.next().charAt(0);
        byte intToByte = (byte) intValue;
        int charToInt = (int) charValue;
        byte doubleToByte = (byte) doubleValue;
        int doubleToInt = (int) doubleValue;
        System.out.println("Conversions:");
        System.out.println("int to byte: " + intToByte);
        System.out.println("char to int: " + charToInt);
        System.out.println("double to byte: " + doubleToByte);
        System.out.println("double to int: " + doubleToInt);
    }
}
