import java.util.Scanner;

// Base class Account
class Account {
    protected String customerName;
    protected String accountNumber;
    protected String accountType;
    protected double balance;

    // Constructor to initialize Account
    public Account(String customerName, String accountNumber, String accountType, double balance) {
        this.customerName = customerName;
        this.accountNumber = accountNumber;
        this.accountType = accountType;
        this.balance = balance;
    }

    // Method to accept deposit and update balance
    public void deposit(double amount) {
        if (amount > 0) {
            balance += amount;
            System.out.println("Deposited: " + amount);
            displayBalance();
        } else {
            System.out.println("Invalid deposit amount");
        }
    }

    // Method to display balance
    public void displayBalance() {
        System.out.println("Current Balance: " + balance);
    }
}

// Derived class SavingsAccount
class SavingsAccount extends Account {
    private double interestRate;

    // Constructor to initialize SavingsAccount
    public SavingsAccount(String customerName, String accountNumber, double balance, double interestRate) {
        super(customerName, accountNumber, "Savings", balance);
        this.interestRate = interestRate;
    }

    // Method to compute and deposit interest
    public void computeAndDepositInterest() {
        double interest = balance * (interestRate / 100);
        deposit(interest);
        System.out.println("Interest of " + interest + " has been added to your account.");
    }
}

// Derived class CurrentAccount
class CurrentAccount extends Account {
    private double minimumBalance;
    private double penaltyAmount;

    // Constructor to initialize CurrentAccount
    public CurrentAccount(String customerName, String accountNumber, double balance, double minimumBalance, double penaltyAmount) {
        super(customerName, accountNumber, "Current", balance);
        this.minimumBalance = minimumBalance;
        this.penaltyAmount = penaltyAmount;
    }

    // Method to permit withdrawal and update balance
    public void withdraw(double amount) {
        if (amount > 0 && balance >= amount) {
            balance -= amount;
            System.out.println("Withdrew: " + amount);
            displayBalance();
            checkMinimumBalance();
        } else {
            System.out.println("Insufficient balance or invalid withdrawal amount.");
        }
    }

    // Method to check for minimum balance and impose penalty if necessary
    private void checkMinimumBalance() {
        if (balance < minimumBalance) {
            System.out.println("Balance is below the minimum required balance. A penalty will be imposed.");
            balance -= penaltyAmount;
            displayBalance();
        }
    }
}

// Main class to test the Account classes
public class Main {
    public static void main(String[] args) {
        Scanner scanner = new Scanner(System.in);
        
        // User inputs for SavingsAccount
        System.out.println("Enter customer name for Savings Account:");
        String savingsName = scanner.nextLine();
        System.out.println("Enter account number for Savings Account:");
        String savingsAccNumber = scanner.nextLine();
        System.out.println("Enter initial balance for Savings Account:");
        double savingsBalance = scanner.nextDouble();
        System.out.println("Enter interest rate for Savings Account:");
        double interestRate = scanner.nextDouble();
        
        SavingsAccount savings = new SavingsAccount(savingsName, savingsAccNumber, savingsBalance, interestRate);
        savings.displayBalance();
        
        // Depositing into savings account
        System.out.println("Enter deposit amount for Savings Account:");
        double depositAmount = scanner.nextDouble();
        savings.deposit(depositAmount);
        
        // Compute interest
        savings.computeAndDepositInterest();

        // User inputs for CurrentAccount
        System.out.println("Enter customer name for Current Account:");
        scanner.nextLine();  // Clear the buffer
        String currentName = scanner.nextLine();
        System.out.println("Enter account number for Current Account:");
        String currentAccNumber = scanner.nextLine();
        System.out.println("Enter initial balance for Current Account:");
        double currentBalance = scanner.nextDouble();
        System.out.println("Enter minimum balance for Current Account:");
        double minimumBalance = scanner.nextDouble();
        System.out.println("Enter penalty amount for Current Account:");
        double penaltyAmount = scanner.nextDouble();

        CurrentAccount current = new CurrentAccount(currentName, currentAccNumber, currentBalance, minimumBalance, penaltyAmount);
        current.displayBalance();
        
        // Depositing into current account
        System.out.println("Enter deposit amount for Current Account:");
        depositAmount = scanner.nextDouble();
        current.deposit(depositAmount);

        // Withdraw from current account
        System.out.println("Enter withdrawal amount for Current Account:");
        double withdrawAmount = scanner.nextDouble();
        current.withdraw(withdrawAmount);

        // Withdraw again to check minimum balance
        System.out.println("Enter another withdrawal amount for Current Account:");
        withdrawAmount = scanner.nextDouble();
        current.withdraw(withdrawAmount);

        scanner.close();
    }
}
