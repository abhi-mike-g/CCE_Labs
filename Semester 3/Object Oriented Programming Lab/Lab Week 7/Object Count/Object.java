import java.util.Scanner;
class ObjectCounter {
    static int count = 0;
    ObjectCounter() {
        count++;
    }
    static void displayObjectCount() {
        System.out.println("Number of objects created: " + count);
    }
}
public class Object {
    public static void main(String[] args) {
        Scanner sc = new Scanner(System.in);
        System.out.print("Enter the number of objects to create: ");
        int numberOfObjects = sc.nextInt();
        for (int i = 0; i < numberOfObjects; i++) {
            new ObjectCounter();
        }
        ObjectCounter.displayObjectCount();
        sc.close();
    }
}
