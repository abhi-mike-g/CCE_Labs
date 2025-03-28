import java.util.Scanner;
public class PhoneNumberParser 
{
    public static void main(String[] args) 
    {
        Scanner scanner = new Scanner(System.in);
        System.out.print("Enter a phone number in the format (555) 555-5555: ");
        String phoneNumber = scanner.nextLine();
        String areaCode = phoneNumber.substring(phoneNumber.indexOf('(') + 1, phoneNumber.indexOf(')'));
        String firstThreeDigits = phoneNumber.substring(phoneNumber.indexOf(')') + 2, phoneNumber.indexOf('-'));
        String lastFourDigits = phoneNumber.substring(phoneNumber.indexOf('-') + 1);
        System.out.println("Area Code: " + areaCode);
        System.out.println("Phone Number: " + firstThreeDigits + "-" + lastFourDigits);
        scanner.close();
    }
}
