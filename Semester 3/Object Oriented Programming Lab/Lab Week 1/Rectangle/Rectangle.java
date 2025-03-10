class Rectangle
{
    public static void main(String args[])
    {
        int l, b, a, p;
        l = Integer.parseInt(args[0]);
        b = Integer.parseInt(args[1]);
        p = 2*(l+b);
        a = l*b;
        System.out.println("Perimeter = "+p);
        System.out.println("Area = "+a);
    }
}