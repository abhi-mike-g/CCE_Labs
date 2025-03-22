// Base class
class Games {
    // Base class method
    void type() {
        System.out.println("Indoor & Outdoor games");
    }
}

// Subclass of Game: Cricket
class Cricket extends Games {
    // Overriding the type method
    void type() {
        System.out.println("Cricket is an outdoor game");
    }
}

// Subclass of Game: Chess
class Chess extends Games {
    // Overriding the type method
    void type() {
        System.out.println("Chess is an indoor game");
    }
}

public class Game {
    public static void main(String[] args) {
        // Reference of Game, and objects of subclasses
        
        Game gameRef;  // A reference variable of type Game
        
        // Object of Cricket
        gameRef = new Cricket();
        gameRef.type();  // Calls Cricket's type method
        
        // Object of Chess
        gameRef = new Chess();
        gameRef.type();  // Calls Chess's type method
    }
}
