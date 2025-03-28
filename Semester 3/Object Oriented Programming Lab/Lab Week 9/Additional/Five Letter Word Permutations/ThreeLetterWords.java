import java.util.Scanner;
public class ThreeLetterWords 
{
    public static void generateThreeLetterWords(String word) 
    {
        int n = word.length();
        for (int i = 0; i < n; i++) 
            for (int j = 0; j < n; j++) 
                for (int k = 0; k < n; k++) 
                    if (i != j && j != k && i != k) 
                        System.out.println("" + word.charAt(i) + word.charAt(j) + word.charAt(k));
    }
    public static void main(String[] args) 
    {
        Scanner scanner = new Scanner(System.in);
        System.out.print("Enter a five-letter word: ");
        String word = scanner.next();
        if (word.length() != 5) 
            System.out.println("Please enter a valid five-letter word.");
        else 
        {
            System.out.println("All possible three-letter words:");
            generateThreeLetterWords(word);
        }
        scanner.close();
    }
}
