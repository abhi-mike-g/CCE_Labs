class MyCustomException extends Exception {
    public MyCustomException(String message) {
        super(message);
    }
}
public class CustomExceptionDemo {
    public static void main(String[] args) {
        try {
            throw new MyCustomException("This is a custom error message.");
        } catch (MyCustomException e) {
            System.out.println("Caught Exception: " + e.getMessage());
        }
    }
}
