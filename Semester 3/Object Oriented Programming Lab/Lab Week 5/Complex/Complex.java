import java.util.Scanner;

public class Complex 
{
    private double real;
    private double imaginary;

    public Complex(double real, double imaginary) 
    {
        this.real = real;
        this.imaginary = imaginary;
    }

    public Complex add(int realPart) 
    {
        return new Complex(this.real + realPart, this.imaginary);
    }

    public Complex add(Complex other) 
    {
        return new Complex(this.real + other.real, this.imaginary + other.imaginary);
    }

    public void display() 
    {
        System.out.println(real + " + " + imaginary + "i");
    }

    public static void main(String[] args) 
    {
        Scanner sc = new Scanner(System.in);

        System.out.println("Enter the real and imaginary parts of the first complex number:");
        double real1 = sc.nextDouble();
        double imaginary1 = sc.nextDouble();
        Complex complex1 = new Complex(real1, imaginary1);

        System.out.println("Enter the real and imaginary parts of the second complex number:");
        double real2 = sc.nextDouble();
        double imaginary2 = sc.nextDouble();
        Complex complex2 = new Complex(real2, imaginary2);

        System.out.print("First Complex Number: ");
        complex1.display();
        System.out.print("Second Complex Number: ");
        complex2.display();

        System.out.println("Enter an integer to add to the first complex number:");
        int integerToAdd = sc.nextInt();
        Complex result1 = complex1.add(integerToAdd);
        System.out.print("Result after adding integer to first complex number: ");
        result1.display();

        Complex result2 = complex1.add(complex2);
        System.out.print("Result after adding the two complex numbers: ");
        result2.display();

        sc.close();
    }
}