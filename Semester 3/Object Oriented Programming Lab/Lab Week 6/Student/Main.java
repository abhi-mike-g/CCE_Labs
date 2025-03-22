import java.util.Scanner;

// Base class Student
class Student {
    protected String registrationNumber;
    protected String name;
    protected int age;

    // Constructor for Student
    public Student(String registrationNumber, String name, int age) {
        this.registrationNumber = registrationNumber;
        this.name = name;
        this.age = age;
    }

    // Method to display common details
    public void displayDetails() {
        System.out.println("Registration Number: " + registrationNumber);
        System.out.println("Name: " + name);
        System.out.println("Age: " + age);
    }
}

// Derived class UGStudent
class UGStudent extends Student {
    private int semester;
    private double fees;
    private static int ugCount = 0; // Static variable to keep track of UG admissions

    // Constructor for UGStudent
    public UGStudent(String registrationNumber, String name, int age, int semester, double fees) {
        super(registrationNumber, name, age);
        this.semester = semester;
        this.fees = fees;
        ugCount++; // Increment UG admission count
    }

    // Method to display UG student details
    @Override
    public void displayDetails() {
        super.displayDetails();
        System.out.println("Semester: " + semester);
        System.out.println("Fees: " + fees);
        System.out.println("Course: Undergraduate");
    }

    // Static method to get UG admission count
    public static int getUGCount() {
        return ugCount;
    }
}

// Derived class PGStudent
class PGStudent extends Student {
    private int semester;
    private double fees;
    private static int pgCount = 0; // Static variable to keep track of PG admissions

    // Constructor for PGStudent
    public PGStudent(String registrationNumber, String name, int age, int semester, double fees) {
        super(registrationNumber, name, age);
        this.semester = semester;
        this.fees = fees;
        pgCount++; // Increment PG admission count
    }

    // Method to display PG student details
    @Override
    public void displayDetails() {
        super.displayDetails();
        System.out.println("Semester: " + semester);
        System.out.println("Fees: " + fees);
        System.out.println("Course: Postgraduate");
    }

    // Static method to get PG admission count
    public static int getPGCount() {
        return pgCount;
    }
}

// Main class to demonstrate functionality
public class Main {
    public static void main(String[] args) {
        Scanner sc = new Scanner(System.in);

        // User input for UG students
        System.out.print("Enter number of UG students: ");
        int ugStudentsCount = sc.nextInt();
        sc.nextLine();  // Consume newline

        UGStudent[] ugStudents = new UGStudent[ugStudentsCount];

        for (int i = 0; i < ugStudentsCount; i++) {
            System.out.println("Enter details for UG student " + (i + 1));
            System.out.print("Registration Number: ");
            String regNo = sc.nextLine();
            System.out.print("Name: ");
            String name = sc.nextLine();
            System.out.print("Age: ");
            int age = sc.nextInt();
            System.out.print("Semester: ");
            int semester = sc.nextInt();
            System.out.print("Fees: ");
            double fees = sc.nextDouble();
            sc.nextLine();  // Consume newline

            ugStudents[i] = new UGStudent(regNo, name, age, semester, fees);
        }

        // User input for PG students
        System.out.print("Enter number of PG students: ");
        int pgStudentsCount = sc.nextInt();
        sc.nextLine();  // Consume newline

        PGStudent[] pgStudents = new PGStudent[pgStudentsCount];

        for (int i = 0; i < pgStudentsCount; i++) {
            System.out.println("Enter details for PG student " + (i + 1));
            System.out.print("Registration Number: ");
            String regNo = sc.nextLine();
            System.out.print("Name: ");
            String name = sc.nextLine();
            System.out.print("Age: ");
            int age = sc.nextInt();
            System.out.print("Semester: ");
            int semester = sc.nextInt();
            System.out.print("Fees: ");
            double fees = sc.nextDouble();
            sc.nextLine();  // Consume newline

            pgStudents[i] = new PGStudent(regNo, name, age, semester, fees);
        }

        // Display UG students details
        System.out.println("\nUG Students:");
        for (UGStudent student : ugStudents) {
            student.displayDetails();
            System.out.println();
        }

        // Display PG students details
        System.out.println("PG Students:");
        for (PGStudent student : pgStudents) {
            student.displayDetails();
            System.out.println();
        }

        // Display total number of UG and PG admissions
        System.out.println("Total UG Admissions: " + UGStudent.getUGCount());
        System.out.println("Total PG Admissions: " + PGStudent.getPGCount());

        sc.close();
    }
}
