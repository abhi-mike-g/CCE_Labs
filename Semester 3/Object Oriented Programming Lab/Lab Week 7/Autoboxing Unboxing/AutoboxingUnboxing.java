import java.util.Scanner;
public class AutoboxingUnboxing {
    public static void main(String[] args) {
        Scanner sc = new Scanner(System.in);
        System.out.print("Enter a byte value: ");
        byte bytePrimitive = sc.nextByte();
        Byte byteObject = bytePrimitive;
        System.out.print("Enter a short value: ");
        short shortPrimitive = sc.nextShort();
        Short shortObject = shortPrimitive;
        System.out.print("Enter an int value: ");
        int intPrimitive = sc.nextInt();
        Integer intObject = intPrimitive;
        System.out.print("Enter a long value: ");
        long longPrimitive = sc.nextLong();
        Long longObject = longPrimitive;
        System.out.print("Enter a float value: ");
        float floatPrimitive = sc.nextFloat();
        Float floatObject = floatPrimitive;
        System.out.print("Enter a double value: ");
        double doublePrimitive = sc.nextDouble();
        Double doubleObject = doublePrimitive;
        System.out.print("Enter a char value: ");
        char charPrimitive = sc.next().charAt(0);
        Character charObject = charPrimitive;
        System.out.print("Enter a boolean value (true/false): ");
        boolean boolPrimitive = sc.nextBoolean();
        Boolean boolObject = boolPrimitive;
        byte unboxedByte = byteObject;
        short unboxedShort = shortObject;
        int unboxedInt = intObject;
        long unboxedLong = longObject;
        float unboxedFloat = floatObject;
        double unboxedDouble = doubleObject;
        char unboxedChar = charObject;
        boolean unboxedBool = boolObject;
        System.out.println("\nAutoboxing Examples:");
        System.out.println("Byte Object: " + byteObject);
        System.out.println("Short Object: " + shortObject);
        System.out.println("Integer Object: " + intObject);
        System.out.println("Long Object: " + longObject);
        System.out.println("Float Object: " + floatObject);
        System.out.println("Double Object: " + doubleObject);
        System.out.println("Character Object: " + charObject);
        System.out.println("Boolean Object: " + boolObject);
        System.out.println("\nUnboxing Examples:");
        System.out.println("Unboxed byte: " + unboxedByte);
        System.out.println("Unboxed short: " + unboxedShort);
        System.out.println("Unboxed int: " + unboxedInt);
        System.out.println("Unboxed long: " + unboxedLong);
        System.out.println("Unboxed float: " + unboxedFloat);
        System.out.println("Unboxed double: " + unboxedDouble);
        System.out.println("Unboxed char: " + unboxedChar);
        System.out.println("Unboxed boolean: " + unboxedBool);
        sc.close();
    }
}
