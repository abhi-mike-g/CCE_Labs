public class Pascal 
{    
    public static void main(String args[])
    {
        int i, j, n;
        n = Integer.parseInt(args[0]);
        i = n;
        for(i = 1; i<=n; i++)
        {
            for(j=0; j<=i; j++)
            {
                System.out.println(i);
            }
        }
    }
}