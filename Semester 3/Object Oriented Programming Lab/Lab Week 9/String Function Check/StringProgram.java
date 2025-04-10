import java.util.Arrays;
import java.util.Scanner;
public class StringProgram {
    public static boolean isPalindrome(String str) {
        String reversedStr = new StringBuilder(str).reverse().toString();
        return str.equals(reversedStr);
    }
    public static String sortStringAlphabetically(String str) {
        char[] chars = str.toCharArray();
        Arrays.sort(chars);
        return new String(chars);
    }
    public static String reverseString(String str) {
        return new StringBuilder(str).reverse().toString();
    }
    public static String concatenateOriginalAndReversed(String str) {
        String reversedStr = reverseString(str);
        return str + reversedStr;
    }
    public static void main(String[] args) {
        Scanner sc = new Scanner(System.in);
        String inputString;
        System.out.print("Enter a string: ");
        inputString = sc.nextLine();
        int choice;
        do {
            System.out.println("\nMenu:");
            System.out.println("1. Check whether the string is a palindrome");
            System.out.println("2. Sort the string alphabetically");
            System.out.println("3. Reverse the string");
            System.out.println("4. Concatenate original and reversed string");
            System.out.println("5. Exit");
            System.out.print("Enter your choice (1-5): ");
            choice = sc.nextInt();
            sc.nextLine();
            switch (choice) {
                case 1:
                    if (isPalindrome(inputString)) 
                        System.out.println("The string is a palindrome.");
                    else 
                        System.out.println("The string is not a palindrome.");
                    break;
                case 2:
                    String sortedString = sortStringAlphabetically(inputString);
                    System.out.println("String after sorting alphabetically: " + sortedString);
                    break;
                case 3:
                    String reversedString = reverseString(inputString);
                    System.out.println("Reversed string: " + reversedString);
                    break;
                case 4:
                    String concatenatedString = concatenateOriginalAndReversed(inputString);
                    System.out.println("Concatenated string: " + concatenatedString);
                    break;
                case 5:
                    System.out.println("Exiting program...");
                    break;
                default:
                    System.out.println("Invalid choice. Please select an option between 1 and 5.");
            }
        } 
        while (choice != 5);
        sc.close();
    }
}
