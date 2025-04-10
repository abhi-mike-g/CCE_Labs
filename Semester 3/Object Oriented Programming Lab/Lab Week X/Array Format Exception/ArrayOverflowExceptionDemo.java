import java.util.Scanner;
public class ArrayOverflowExceptionDemo {
    public static void main(String[] args) {
        Scanner sc = new Scanner(System.in);
        try {
            System.out.print("Enter the size of the array: ");
            int size = sc.nextInt();
            int[] arr = new int[size];
            for (int i = 0; i <= size; i++) {
                System.out.println("Enter a number for index " + i + ":");
                arr[i] = sc.nextInt();
            }
        } catch (ArrayIndexOutOfBoundsException e) {
            System.out.println("Array overflow! You are trying to insert more elements than the array size.");
        } finally {
            sc.close();
        }
    }
}
