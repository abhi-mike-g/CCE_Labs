class Statement
{
    public static void main(String args[])
    {
        int x =10;
        double y = x; 
        System.out.println(y); 
        
        // double x = 10.5; 
        //int y = x;
        //System.out.println(y);
        //The above snippet outputs an error due to improper conversion of float to int

        double a=10.5;
        int b = (int) a;
        System.out.println(b);
    }
}