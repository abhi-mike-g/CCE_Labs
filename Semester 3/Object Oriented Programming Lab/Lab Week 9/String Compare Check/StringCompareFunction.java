import java.util.Scanner;
public class StringCompareFunction {
    public static void compareStrings(String str1, String str2) {
        if (str1.equals(str2)) 
            System.out.println("The strings are equal.");
        else 
            System.out.println("The strings are not equal.");
    }
    public static String convertCase(String str) {
        StringBuilder convertedStr = new StringBuilder();
        for (char c : str.toCharArray()) {
            if (Character.isUpperCase(c)) 
                convertedStr.append(Character.toLowerCase(c));
            else if (Character.isLowerCase(c)) 
                convertedStr.append(Character.toUpperCase(c));
            else 
                convertedStr.append(c);
        }
        return convertedStr.toString();
    }
    public static boolean isSubstring(String str1, String str2) {
        return str1.contains(str2) || str2.contains(str1);
    }
    public static void main(String[] args) {
        Scanner sc = new Scanner(System.in);
        String str1, str2;
        int choice;
        do {
            System.out.println("\nMenu:");
            System.out.println("1. Compare two strings");
            System.out.println("2. Convert uppercase characters to lowercase and vice-versa");
            System.out.println("3. Check if one string is a substring of the other");
            System.out.println("4. Exit");
            System.out.print("Enter your choice (1-4): ");
            choice = sc.nextInt();
            sc.nextLine();
            switch (choice) {
                case 1:
                    System.out.print("Enter the first string: ");
                    str1 = sc.nextLine();
                    System.out.print("Enter the second string: ");
                    str2 = sc.nextLine();
                    compareStrings(str1, str2);
                    break;
                case 2:
                    System.out.print("Enter a string: ");
                    str1 = sc.nextLine();
                    String convertedString = convertCase(str1);
                    System.out.println("String after converting case: " + convertedString);
                    break;
                case 3:
                    System.out.print("Enter the first string: ");
                    str1 = sc.nextLine();
                    System.out.print("Enter the second string: ");
                    str2 = sc.nextLine();
                    if (isSubstring(str1, str2))
                        System.out.println("One string is a substring of the other.");
                     else 
                        System.out.println("Neither string is a substring of the other.");
                    break;
                case 4:
                    System.out.println("Exiting the program...");
                    break;
                default:
                    System.out.println("Invalid choice. Please select a valid option (1-4).");
            }
        } while (choice != 4);
        sc.close();
    }
}
