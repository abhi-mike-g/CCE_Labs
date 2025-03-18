class Stack 
{
    private int maxSize;
    private int[] stackArray;
    private int top;

    public Stack(int size) 
    {
        this.maxSize = size;
        this.stackArray = new int[maxSize];
        this.top = -1;
    }

    public void push(int value) 
    {
        if (isFull()) 
            System.out.println("Stack is full. Cannot push " + value);
        else 
        {
            stackArray[++top] = value;
            System.out.println("Pushed " + value + " onto the stack.");
        }
    }

    public int pop() {
        if (isEmpty()) {
            System.out.println("Stack is empty. Cannot pop.");
            return -1;
        } else {
            int poppedValue = stackArray[top--];
            System.out.println("Popped " + poppedValue + " from the stack.");
            return poppedValue;
        }
    }

    public int peek() {
        if (isEmpty()) {
            System.out.println("Stack is empty. Cannot peek.");
            return -1; // Return -1 if the stack is empty
        } else {
            return stackArray[top];
        }
    }

    // Method to check if the stack is empty
    public boolean isEmpty() {
        return (top == -1);
    }

    // Method to check if the stack is full
    public boolean isFull() {
        return (top == maxSize - 1);
    }

    // Method to display the elements of the stack
    public void display() {
        if (isEmpty()) {
            System.out.println("Stack is empty.");
        } else {
            System.out.println("Stack elements:");
            for (int i = top; i >= 0; i--) {
                System.out.println(stackArray[i]);
            }
        }
    }

    // Main method for testing
    public static void main(String[] args) {
        Stack stack = new Stack(5); // Create a stack of size 5

        // Performing stack operations
        stack.push(10);
        stack.push(20);
        stack.push(30);
        stack.display(); // Display the stack elements
        stack.pop();
        stack.peek();
        stack.push(40);
        stack.push(50);
        stack.push(60);
        stack.push(70); // This push will show stack overflow
        stack.display(); // Display the stack elements
    }
}
