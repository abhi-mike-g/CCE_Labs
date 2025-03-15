import java.util.Scanner;
public class Calculator 
{
        public static void main(String[] args) 
    {
        char result = 0;
        double a = 0;
        double b = 0;
        double ans = 0;
        do 
        {
            System.out.println("Calculator Program\n");
            System.out.println("Choose how to proceed:\n");
            System.out.println("A. Add\n");
            System.out.println("S. Subtract\n");
            System.out.println("M. Multiply\n");
            System.out.println("D. Divide\n");
            System.out.println("X. Exit\n");
            Scanner sc = new Scanner(System.in);
            result = sc.next().charAt(0); 
            switch (result) 
            {
                    case 'a':
                    case'A': 
                        System.out.println("Please enter the first number: ");
                        a = sc.nextDouble();
                        System.out.println("Please enter the second number: ");
                        a = sc.nextDouble();
                        ans = a + b;
                        System.out.println("Answer: " + a + " + " + b + " = " + ans);
                    case 's':
                    case 'S':    
                        System.out.println("Please enter the first number: ");
                        a = sc.nextDouble();
                        System.out.println("Please enter the second number: ");
                        b = sc.nextDouble();
                        ans = a - b;
                        System.out.println("Answer: " + a + " - " + b + " = " + ans);
                    case 'm':
                    case 'M':
                        System.out.println("Please enter the first number: ");
                        a = sc.nextDouble();
                        System.out.println("Please enter the second number: ");
                        b = sc.nextDouble();
                        ans = a * b;
                        System.out.println("Answer: " + a + " * " + b + " = " + ans);
                    case 'd':
                    case 'D':
                        System.out.println("Please enter the first number: ");
                        a = sc.nextDouble();
                        System.out.println("Please enter the second number: ");
                        b = sc.nextDouble();
                        ans = a / b;
                        System.out.println("Answer: " + a + " / " + b + " = " + ans);
                    case 'x':
                    case 'X':    
                        System.exit(0);
            }
        }
while (result == 'A' || result == 'S'|| result == 'M' || result == 'D' || result == 'a' || result == 's'|| result == 'm' || result == 'd');
    }
}