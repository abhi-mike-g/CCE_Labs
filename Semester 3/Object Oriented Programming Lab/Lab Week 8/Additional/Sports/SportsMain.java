import java.util.Scanner;

interface Sports {
    int getNumberOfGoals(String teamName);
    void dispTeam(String team1, String team2);
}

class Hockey implements Sports {
    private int team1Goals;
    private int team2Goals;

    public Hockey(int team1Goals, int team2Goals) {
        this.team1Goals = team1Goals;
        this.team2Goals = team2Goals;
    }

    @Override
    public int getNumberOfGoals(String teamName) {
        if (teamName.equalsIgnoreCase("Team1")) {
            return team1Goals;
        } else if (teamName.equalsIgnoreCase("Team2")) {
            return team2Goals;
        } else {
            return 0;
        }
    }

    @Override
    public void dispTeam(String team1, String team2) {
        System.out.println("Hockey Match Results:");
        System.out.println(team1 + " scored " + getNumberOfGoals("Team1") + " goals.");
        System.out.println(team2 + " scored " + getNumberOfGoals("Team2") + " goals.");

        if (team1Goals > team2Goals) {
            System.out.println("Winner: " + team1);
        } else if (team1Goals < team2Goals) {
            System.out.println("Winner: " + team2);
        } else {
            System.out.println("The match is a draw.");
        }
    }
}

class Football implements Sports {
    private int team1Goals;
    private int team2Goals;

    public Football(int team1Goals, int team2Goals) {
        this.team1Goals = team1Goals;
        this.team2Goals = team2Goals;
    }

    @Override
    public int getNumberOfGoals(String teamName) {
        if (teamName.equalsIgnoreCase("Team1")) {
            return team1Goals;
        } else if (teamName.equalsIgnoreCase("Team2")) {
            return team2Goals;
        } else {
            return 0;
        }
    }

    @Override
    public void dispTeam(String team1, String team2) {
        System.out.println("Football Match Results:");
        System.out.println(team1 + " scored " + getNumberOfGoals("Team1") + " goals.");
        System.out.println(team2 + " scored " + getNumberOfGoals("Team2") + " goals.");

        if (team1Goals > team2Goals) {
            System.out.println("Winner: " + team1);
        } else if (team1Goals < team2Goals) {
            System.out.println("Winner: " + team2);
        } else {
            System.out.println("The match is a draw.");
        }
    }
}

public class SportsMain {
    public static void main(String[] args) {
        Scanner scanner = new Scanner(System.in);

        System.out.println("Enter the type of sport (Hockey or Football): ");
        String sportType = scanner.nextLine();

        System.out.println("Enter the goals for Team1: ");
        int team1Goals = scanner.nextInt();

        System.out.println("Enter the goals for Team2: ");
        int team2Goals = scanner.nextInt();

        System.out.println("Enter the name of Team1: ");
        String team1Name = scanner.next();

        System.out.println("Enter the name of Team2: ");
        String team2Name = scanner.next();

        if (sportType.equalsIgnoreCase("Hockey")) {
            Hockey hockeyMatch = new Hockey(team1Goals, team2Goals);
            hockeyMatch.dispTeam(team1Name, team2Name);
        } else if (sportType.equalsIgnoreCase("Football")) {
            Football footballMatch = new Football(team1Goals, team2Goals);
            footballMatch.dispTeam(team1Name, team2Name);
        } else {
            System.out.println("Invalid sport type. Please enter Hockey or Football.");
        }
    }
}