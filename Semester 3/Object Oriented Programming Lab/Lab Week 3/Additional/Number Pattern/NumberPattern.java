public class NumberPattern {
    public static void main(String[] args) {
        int counter = 1; // Initialize the counter

        // Outer loop for rows
        for (int i = 1; i <= 4; i++) {
            // Inner loop for columns
            for (int j = 1; j <= i; j++) {
                System.out.print(counter + " "); // Print the current counter value
                counter++; // Increment the counter
            }
            System.out.println(); // Move to the next line after each row
        }
    }
}
