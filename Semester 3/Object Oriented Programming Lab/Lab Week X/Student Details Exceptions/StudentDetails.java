import java.util.Scanner;
public class StudentDetails {
    public static void main(String[] args) {
        Scanner sc = new Scanner(System.in);
        try {
            System.out.print("Enter Student's Name: ");
            String name = sc.nextLine();
            System.out.print("Enter Roll Number: ");
            String rollNumber = sc.nextLine();
            System.out.print("Enter marks for Subject 1: ");
            int m1 = Integer.parseInt(sc.nextLine());
            System.out.print("Enter marks for Subject 2: ");
            int m2 = Integer.parseInt(sc.nextLine());
            System.out.print("Enter marks for Subject 3: ");
            int m3 = Integer.parseInt(sc.nextLine());
            int totalMarks = m1 + m2 + m3;
            double percentage = (totalMarks / 3.0);
            char grade;
            if (percentage >= 90) {
                grade = 'A';
            } else if (percentage >= 80) {
                grade = 'B';
            } else if (percentage >= 70) {
                grade = 'C';
            } else if (percentage >= 60) {
                grade = 'D';
            } else {
                grade = 'F';
            }
            System.out.println("\n--- Student Result ---");
            System.out.println("Name: " + name);
            System.out.println("Roll Number: " + rollNumber);
            System.out.println("Total Marks: " + totalMarks);
            System.out.println("Percentage: " + percentage + "%");
            System.out.println("Grade: " + grade);
        } catch (NumberFormatException e) {
            System.out.println("Invalid input! Please enter valid numeric marks.");
        } finally {
            sc.close();
        }
    }
}
