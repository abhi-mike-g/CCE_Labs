import java.util.Scanner;
public class TextAnalyzer 
{
    public static int countVowels(String input) {
        int vowelCount = 0;
        String vowels = "aeiouAEIOU";
        for (char ch : input.toCharArray()) {
            if (vowels.indexOf(ch) != -1) 
                vowelCount++;
        }
        return vowelCount;
    }
    public static void main(String[] args) {
        Scanner sc = new Scanner(System.in);
        System.out.println("Enter a string (multi-line supported, type 'exit' to finish input):");
        StringBuilder inputBuilder = new StringBuilder();
        String line;
        while (!(line = sc.nextLine()).equalsIgnoreCase("exit")) {
            inputBuilder.append(line).append("\n");
        }
        String input = inputBuilder.toString();
        int characterCount = input.replace("\n", "").length();
        String[] words = input.trim().split("\\s+");
        int wordCount = words.length;
        String[] lines = input.split("\n");
        int lineCount = lines.length;
        int vowelCount = countVowels(input);
        System.out.println("\nAnalysis of the inputted text:");
        System.out.println("Number of characters: " + characterCount);
        System.out.println("Number of words: " + wordCount);
        System.out.println("Number of lines: " + lineCount);
        System.out.println("Number of vowels: " + vowelCount);
        sc.close();
    }
}
