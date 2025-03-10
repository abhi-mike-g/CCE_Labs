class OddFifty
{
    public static void main(String args[])
    {
        int i;
        i = 2;
        System.out.print(1+" ");
        while(i<=100)
        {
            if(i%2 != 0)
                System.out.print(" "+i+" ");
            i = i + 1;
        }
    }
}