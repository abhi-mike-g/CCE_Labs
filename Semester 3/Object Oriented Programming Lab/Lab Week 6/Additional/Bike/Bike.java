// Base class Bike
class Bikes {
    // Data member in Bike class
    int speedlimit = 90;
    
    // Method to be overridden
    void run() {
        System.out.println("Bike is running with speed limit: " + speedlimit);
    }
}

// Subclass Splendar that extends Bike
class Splendar extends Bikes {
    // Data member in Splendar class
    int speedlimit = 60;
    
    // Overriding the run method
    @Override
    void run() {
        System.out.println("Splendar is running with speed limit: " + speedlimit);
    }
}

public class Bike {
    public static void main(String[] args) {
        // Creating a reference of Bike, and assigning it to Splendar object (runtime polymorphism)
        Bike bikeRef = new Splendar();
        
        // Calling the run method (runtime polymorphism: the run method of Splendar will be called)
        bikeRef.run();

        // Accessing the data member (This will access the speedlimit from Bike, not Splendar)
        System.out.println("Speed limit of bikeRef: " + bikeRef.speedlimit);
    }
}
