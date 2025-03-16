public class DupDigit 
{
    public static void main(String[] args) 
{
        int[] digits = {1, 2, 3, 4};
        
        System.out.println("Combinations with duplication allowed:");
        for (int i = 0; i < digits.length; i++) 
            for (int j = 0; j < digits.length; j++) 
                for (int k = 0; k < digits.length; k++) 
                    for (int l = 0; l < digits.length; l++) 
                        System.out.println("" + digits[i] + digits[j] + digits[k] + digits[l]);
}
