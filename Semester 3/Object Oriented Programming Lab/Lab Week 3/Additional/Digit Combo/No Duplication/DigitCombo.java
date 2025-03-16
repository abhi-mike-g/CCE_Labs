public class DigitCombo
{
    public static void main(String[] args) 
{
        int[] digits = {1, 2, 3, 4};
        
        System.out.println("Combinations without duplication:");
        for (int i = 0; i < digits.length; i++) 
{
            for (int j = 0; j < digits.length; j++) 
{
                if (j == i) continue; // Skip if digits are the same
                for (int k = 0; k < digits.length; k++) 
{
                    if (k == i || k == j) continue; // Skip if digits are the same
                    for (int l = 0; l < digits.length; l++) 
{
                        if (l == i || l == j || l == k) continue; // Skip if digits are the same
                        System.out.println("" + digits[i] + digits[j] + digits[k] + digits[l]);
                    }
                }
            }
        }
    }
}
