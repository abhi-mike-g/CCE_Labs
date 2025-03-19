import java.util.Scanner;
public class Employee 
{
    private String name;
    private String city;
    private double basicSalary;
    private double daPerc; // DA%
    private double hraPerc; // HRA%
    public void getData() 
    {
        Scanner sc = new Scanner(System.in);
        System.out.print("Enter employee name: ");
        name = sc.nextLine();
        System.out.print("Enter city: ");
        city = sc.nextLine();
        System.out.print("Enter basic salary: ");
        basicSalary = sc.nextDouble();
        System.out.print("Enter DA percentage: ");
        da = sc.nextDouble();
        System.out.print("Enter HRA percentage: ");
        hra = sc.nextDouble();
        sc.close();

    }
    public double calculate() 
    {
        double da = basicSalary * daPerc / 100;
        double hra = basicSalary * hraPerc / 100;
        return basicSalary + da + hra;
    }
    public void display() 
    {
        double CTC = calculate();
        System.out.println("\nEmployee Name: " + name);
        System.out.println("City: " + city);
        System.out.println("Basic Salary: " + basicSalary);
        System.out.println("DA Percentage: " + daPerc + "%");
        System.out.println("HRA Percentage: " + hraPerc + "%");
        System.out.println("Total Salary: " + CTC);
    }
    public static void main(String[] args) 
    {
        Employee emp = new Employee();
        emp.getData();
        emp.display();
    }
}