import java.util.Scanner;
interface Product 
{
    double calculateSales();
}
class Hardware implements Product 
{
    private String category;
    private String manufacturer;
    private double[] sales;
    public Hardware(String category, String manufacturer, double[] sales) 
    {
        this.category = category;
        this.manufacturer = manufacturer;
        this.sales = sales;
    }
    @Override
    public double calculateSales() 
    {
        double totalSales = 0;
        for (double sale : sales) 
        {
            totalSales += sale;
        }
        return totalSales;
    }
    public void displayDetails() 
    {
        System.out.println("Hardware Category: " + category);
        System.out.println("Manufacturer: " + manufacturer);
    }
}
class Software implements Product 
{
    private String softwareType;
    private String operatingSystem;
    private double[] sales;
    public Software(String softwareType, String operatingSystem, double[] sales) 
    {
        this.softwareType = softwareType;
        this.operatingSystem = operatingSystem;
        this.sales = sales;
    }
    @Override
    public double calculateSales() 
    {
        double totalSales = 0;
        for (double sale : sales) 
        {
            totalSales += sale;
        }
        return totalSales;
    }
    public void displayDetails() 
    {
        System.out.println("Software Type: " + softwareType);
        System.out.println("Operating System: " + operatingSystem);
    }
}
public class HardwareSoftwareCompany 
{
    public static void main(String[] args) 
    {
        Scanner sc = new Scanner(System.in);
        System.out.print("Enter hardware category: ");
        String hardwareCategory = sc.nextLine();
        System.out.print("Enter hardware manufacturer: ");
        String hardwareManufacturer = sc.nextLine();
        System.out.print("Enter number of sales periods for hardware: ");
        int numHardwareSales = sc.nextInt();
        double[] hardwareSales = new double[numHardwareSales];
        for (int i = 0; i < numHardwareSales; i++) 
        {
            System.out.print("Enter sales for period " + (i + 1) + ": ");
            hardwareSales[i] = sc.nextDouble();
        }
        Hardware hardware = new Hardware(hardwareCategory, hardwareManufacturer, hardwareSales);
        System.out.print("Enter software type: ");
        String softwareType = sc.next();
        System.out.print("Enter operating system: ");
        String operatingSystem = sc.next();
        System.out.print("Enter number of sales periods for software: ");
        int numSoftwareSales = sc.nextInt();
        double[] softwareSales = new double[numSoftwareSales];
        for (int i = 0; i < numSoftwareSales; i++) 
        {
            System.out.print("Enter sales for period " + (i + 1) + ": ");
            softwareSales[i] = sc.nextDouble();
        }
        Software software = new Software(softwareType, operatingSystem, softwareSales);
        hardware.displayDetails();
        System.out.println("Total Sales for Hardware: $" + hardware.calculateSales());
        System.out.println();
        software.displayDetails();
        System.out.println("Total Sales for Software: $" + software.calculateSales());
    }
}