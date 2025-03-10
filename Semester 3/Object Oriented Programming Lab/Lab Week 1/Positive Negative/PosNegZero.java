class PosNegZero
{
    public static void main(String args[])
    {
        int arr[] = new int[10];
        int pos, neg, zero, i;
        pos = 0; neg = 0; zero = 0;
        for(i = 0; i<10; i++)
            arr[i] = Integer.parseInt(args[i]);
        for(i = 0; i<10; i++)
            if(arr[i] > 0)
                pos++;
            else if(arr[i] == 0)
                    zero++;
                else
                    neg++;
        System.out.println("No.of Positive numbers: "+pos);
        System.out.println("No.of Negative numbers: "+neg);
        System.out.println("No.of 0s: "+zero);
    }
}