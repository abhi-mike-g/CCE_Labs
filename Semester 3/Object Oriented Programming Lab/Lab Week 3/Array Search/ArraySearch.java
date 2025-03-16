import java.util.ArrayList;
import java.util.Scanner;

public class ArraySearch
{
    public static void main(String[] args) 
    {
        // Initialize the array
        int[] a = {1, 2, 3, 1, 2, 1, 5, 6, 7};

        // Prompt the user to enter the value to search for
        Scanner scanner = new Scanner(System.in);
        System.out.print("Enter the value to search for: ");
        int searchValue = scanner.nextInt();

        // ArrayList to store the indices where the value is found
        ArrayList<Integer> foundIndices = new ArrayList<>();

        // Search for the value in the array
        int index = 0;
        for (int value : a) 
        {
            if (value == searchValue) 
            {
                foundIndices.add(index);
            }
            index++;
        }

        // Display the results
        if (!foundIndices.isEmpty()) 
        {
            System.out.print("The value is found at locations: ");
            for (int i = 0; i < foundIndices.size(); i++) 
            {
                System.out.print("a[" + foundIndices.get(i) + "]");
                if (i < foundIndices.size() - 1) 
                {
                    System.out.print(", ");
                }
            }
            System.out.println(".");
        } 
        else 
        {
            System.out.println("The value is not found in the array.");
        }
    }
}