import java.util.Scanner;
class Student 
{
    String regNo;
    String firstName;
    String lastName;
    String degree;

    public Student(String regNo, String firstName, String lastName, String degree) 
    {
        this.regNo = regNo;
        this.firstName = firstName;
        this.lastName = lastName;
        this.degree = degree;
    }

    public void displayDetails() 
    {
        System.out.println("Registration No: " + regNo);
        System.out.println("First Name: " + firstName);
        System.out.println("Last Name: " + lastName);
        System.out.println("Degree: " + degree);
        System.out.println("-----------------------------");
    }
}
public class StudentSearch 
{
    public static void main(String[] args) 
    {
        Scanner scanner = new Scanner(System.in);
        Student[] students = new Student[10];
        students[0] = new Student("S101", "John", "Doe", "BSc Computer Science");
        students[1] = new Student("S102", "Jane", "Smith", "BBA");
        students[2] = new Student("S103", "Emily", "Johnson", "BSc Physics");
        students[3] = new Student("S104", "Michael", "Brown", "BA English");
        students[4] = new Student("S105", "Sarah", "Williams", "BCom");
        students[5] = new Student("S106", "David", "Jones", "BTech Mechanical");
        students[6] = new Student("S107", "Emma", "Garcia", "BCA");
        students[7] = new Student("S108", "James", "Martinez", "BBA");
        students[8] = new Student("S109", "Oliver", "Lopez", "BSc Mathematics");
        students[9] = new Student("S110", "Sophia", "Wilson", "BFA");

        System.out.println("Search student by:");
        System.out.println("1. First Name");
        System.out.println("2. Last Name");
        System.out.print("Enter your choice: ");
        int choice = scanner.nextInt();
        scanner.nextLine();

        if (choice == 1) 
        {
            System.out.print("Enter First Name to search: ");
            String firstName = scanner.nextLine();
            searchByFirstName(students, firstName);
        } 
        else if (choice == 2) 
        {
            System.out.print("Enter Last Name to search: ");
            String lastName = scanner.nextLine();
            searchByLastName(students, lastName);
        } 
        else 
            System.out.println("Invalid choice.");
        scanner.close();
    }

    public static void searchByFirstName(Student[] students, String firstName) 
    {
        boolean found = false;
        for (Student student : students) 
            if (student.firstName.equalsIgnoreCase(firstName)) 
            {
                student.displayDetails();
                found = true;
            }
        if (!found) 
            System.out.println("No student found with First Name: " + firstName);
    }
    public static void searchByLastName(Student[] students, String lastName) 
    {
        boolean found = false;
        for (Student student : students) 
            if (student.lastName.equalsIgnoreCase(lastName)) 
            {
                student.displayDetails();
                found = true;
            }
        if (!found)
            System.out.println("No student found with Last Name: " + lastName);
    }
}
