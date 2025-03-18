import java.util.Arrays;
import java.util.Scanner;

public class ArrayOperations 
{
    private int[] array = new int[10];

    public void inputValues() 
    {
        Scanner scanner = new Scanner(System.in);
        System.out.println("Enter 10 integer values:");
        for (int i = 0; i < array.length; i++) 
        {
            System.out.print("Enter value " + (i + 1) + ": ");
            array[i] = scanner.nextInt();
        }
    }

    public void displayValues() 
    {
        System.out.println("Array values:");
        for (int value : array) 
            System.out.print(value + " ");
        System.out.println();
    }

    public void displayLargestValue() 
    {
        int largest = array[0];
        for (int value : array) 
            if (value > largest) 
                largest = value;
        System.out.println("Largest value in the array: " + largest);
    }

    public void displayAverage() 
    {
        int sum = 0;
        for (int value : array) 
            sum += value;
        double average = (double) sum / array.length;
        System.out.println("Average of array values: " + average);
    }

    public void sortArray() 
    {
        Arrays.sort(array);
        System.out.println("Array sorted in ascending order:");
        for (int value : array) 
            System.out.print(value + " ");
        System.out.println();
    }

    public static void main(String[] args) 
    {
        ArrayOperations operations = new ArrayOperations();

        operations.inputValues();

        operations.displayValues();

        operations.displayLargestValue();

        operations.displayAverage();

        operations.sortArray();
    }
}
