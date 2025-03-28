import java.util.HashSet;
import java.util.Scanner;
public class ReplaceRepeatingCharacters {
    public static void main(String[] args) {
        Scanner sc = new Scanner(System.in);
        System.out.print("Enter a word: ");
        String inputWord = sc.nextLine();
        System.out.print("Enter the word to replace repeating characters: ");
        String replaceWord = sc.nextLine();
        HashSet<Character> seenChars = new HashSet<>();
        StringBuilder result = new StringBuilder();
        for (int i = 0; i < inputWord.length(); i++) {
            char currentChar = inputWord.charAt(i);
            if (seenChars.contains(currentChar)) {
                result.append(replaceWord);
            } else {
                result.append(currentChar);
                seenChars.add(currentChar);
            }
        }
        System.out.println("Output: " + result.toString());
        sc.close();
    }
}
