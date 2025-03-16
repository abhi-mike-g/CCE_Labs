import java.util.Scanner;
class LargestOfThree 
{
    public static void main(String[] args) 
    {
        Scanner sc = new Scanner(System.in);
       System.out.print("Enter first number: ");
       int n1 = sc.nextInt();
       System.out.print("Enter Second number: ");
       int n2 = sc.nextInt();
       System.out.print("Enter Third number: ");
       int n3 = sc.nextInt();
       int L = (n1>n2)?(n1>n3?n1:n3):(n2>n3?n2:n3);
       int S = (n1<n2)?(n1<n3?n1:n3):(n2<n3?n2:n3);
       System.out.println("Largest: "+L);
       System.out.println("Smallest: "+S);
        sc.close();
    }
}
