import java.util.Scanner;

public class Time 
{
    private int hours;
    private int minutes;
    private int seconds;

    public Time() 
    {
        this.hours = 0;
        this.minutes = 0;
        this.seconds = 0;
    }

    public Time(int hours, int minutes, int seconds) 
    {
        this.hours = hours;
        this.minutes = minutes;
        this.seconds = seconds;
    }

    public void displayTime() 
    {
        System.out.printf("%02d:%02d:%02d\n", hours, minutes, seconds);
    }

    public static Time addTimes(Time t1, Time t2) 
    {
        int totalSeconds = t1.seconds + t2.seconds;
        int totalMinutes = t1.minutes + t2.minutes + (totalSeconds / 60);
        int totalHours = t1.hours + t2.hours + (totalMinutes / 60);

        int finalSeconds = totalSeconds % 60;
        int finalMinutes = totalMinutes % 60;
        int finalHours = totalHours % 24;  // Assuming a 24-hour format

        return new Time(finalHours, finalMinutes, finalSeconds);
    }

    public static void main(String[] args) 
    {
        Scanner scanner = new Scanner(System.in);

        System.out.println("Enter time 1 (hours minutes seconds): ");
        int hours1 = scanner.nextInt();
        int minutes1 = scanner.nextInt();
        int seconds1 = scanner.nextInt();

        Time time1 = new Time(hours1, minutes1, seconds1);

        System.out.println("Enter time 2 (hours minutes seconds): ");
        int hours2 = scanner.nextInt();
        int minutes2 = scanner.nextInt();
        int seconds2 = scanner.nextInt();

        Time time2 = new Time(hours2, minutes2, seconds2);

        System.out.print("Time 1: ");
        time1.displayTime();
        System.out.print("Time 2: ");
        time2.displayTime();

        Time sumTime = Time.addTimes(time1, time2);
        System.out.print("Sum of Time 1 and Time 2: ");
        sumTime.displayTime();

        scanner.close();
    }
}