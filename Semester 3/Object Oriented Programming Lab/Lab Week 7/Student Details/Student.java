import java.util.Scanner;
class Student_Detail {
    String name;
    String id;
    String college_name;
    Student_Detail(String name, String id, String college_name) {
        this.name = name;
        this.id = id;
        this.college_name = college_name;
    }
    void display_details() {
        System.out.println("Student Name: " + name);
        System.out.println("Student ID: " + id);
        System.out.println("College Name: " + college_name);
    }
}
public class Student {
    public static void main(String[] args) {
        Scanner sc = new Scanner(System.in);
        System.out.print("Enter the number of students: ");
        int numOfStudents = sc.nextInt();
        sc.nextLine();
        Student_Detail[] students = new Student_Detail[numOfStudents];
        for (int i = 0; i < numOfStudents; i++) {
            System.out.println("\nEnter details for Student " + (i + 1) + ":");
            System.out.print("Enter Name: ");
            String name = sc.nextLine();
            System.out.print("Enter ID: ");
            String id = sc.nextLine();
            students[i] = new Student_Detail(name, id, "MIT");
        }
        System.out.println("\n--- Student Details ---");
        for (int i = 0; i < numOfStudents; i++) {
            System.out.println("\nStudent " + (i + 1) + " Details:");
            students[i].display_details();
        }
        sc.close();
    }
}
