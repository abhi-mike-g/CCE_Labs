import java.util.ArrayList;
import java.util.List;
public class Numtri 
{
    public static void main(String[] args) 
    {
        int rows = 5;
        List<List<Integer>> patternList = new ArrayList<>();
        for (int i = 1; i <= rows; i++) 
        {
            List<Integer> rowList = new ArrayList<>();
            for (int j = 1; j <= i; j++) 
            {
                rowList.add(i);
            }
            patternList.add(rowList);
        }
        for (List<Integer> row : patternList) 
        {
            for (Integer number : row) 
            {
                System.out.print(number + " ");
            }
            System.out.println();
        }
    }
}