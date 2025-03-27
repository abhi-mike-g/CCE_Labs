import java.util.Scanner;
interface Shape {
    double calculateArea();
}
class Rectangle implements Shape {
    private double length;
    private double width;
    public Rectangle(double length, double width) {
        this.length = length;
        this.width = width;
    }
    @Override
    public double calculateArea() {
        return length * width;
    }
}
class Circle implements Shape {
    private double radius;
    public Circle(double radius) {
        this.radius = radius;
    }
    @Override
    public double calculateArea() {
        return Math.PI * radius * radius;
    }
}
public class InterfaceShapeMain {
    public static void main(String[] args) {
        Scanner sc = new Scanner(System.in);
        System.out.print("Enter the length of the rectangle: ");
        double length = sc.nextDouble();
        System.out.print("Enter the width of the rectangle: ");
        double width = sc.nextDouble();
        System.out.print("Enter the radius of the circle: ");
        double radius = sc.nextDouble();
        Shape rectangle = new Rectangle(length, width);
        Shape circle = new Circle(radius);
        System.out.println("Area of the rectangle: " + rectangle.calculateArea());
        System.out.println("Area of the circle: " + circle.calculateArea());
    }
}