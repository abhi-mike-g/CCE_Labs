import java.util.Scanner;

abstract class Shape {
    abstract double computeArea();
}

class Square extends Shape {
    private double side;

    public Square(double side) {
        this.side = side;
    }

    @Override
    double computeArea() {
        return side * side;
    }
}

class Triangle extends Shape {
    private double base;
    private double height;

    public Triangle(double base, double height) {
        this.base = base;
        this.height = height;
    }

    @Override
    double computeArea() {
        return 0.5 * base * height;
    }
}

public class AbstractArea {
    public static void main(String[] args) {
        Scanner scanner = new Scanner(System.in);

        System.out.print("Enter the type of shape (Square/Triangle): ");
        String shapeType = scanner.next();

        Shape shape = null;

        if (shapeType.equalsIgnoreCase("Square")) {
            System.out.print("Enter the side of the square: ");
            double side = scanner.nextDouble();
            shape = new Square(side);
        } else if (shapeType.equalsIgnoreCase("Triangle")) {
            System.out.print("Enter the base of the triangle: ");
            double base = scanner.nextDouble();
            System.out.print("Enter the height of the triangle: ");
            double height = scanner.nextDouble();
            shape = new Triangle(base, height);
        } else {
            System.out.println("Invalid shape type. Please try again.");
            return;
        }

        System.out.println("Area of " + shapeType + ": " + shape.computeArea());
    }
}
