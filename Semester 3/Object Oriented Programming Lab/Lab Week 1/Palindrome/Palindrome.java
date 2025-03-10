class Palindrome
{
    public static void main(String args[])
    {
        int num, rev = 0, rem, n, real;
        num = Integer.parseInt(args[0]);
        real = num;
        while(num!=0)
        {
            rem = num%10;
            rev = (rev * 10)+rem;
            num = num/10;
        }
        if(real == rev)
            System.out.println(real+" is a Palindrome");
        else
            System.out.println(real+" is not a palindrome");
    }
}