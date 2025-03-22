// Base class Bank
class Bank {
    public double getROI() {
        return 0.0;
    }
}
class SBI extends Bank {
    @Override
    public double getROI() {
        return 8.0;
    }
}

class ICICI extends Bank {
    @Override
    public double getROI() {
        return 7.0;
    }
}
class AXIS extends Bank {
    @Override
    public double getROI() {
        return 9.0;
    }
}
public class Main {
    public static void main(String[] args) {
        Bank sbi = new SBI();
        Bank icici = new ICICI();
        Bank axis = new AXIS();
        System.out.println("Rate of Interest for SBI: " + sbi.getROI() + "%");
        System.out.println("Rate of Interest for ICICI: " + icici.getROI() + "%");
        System.out.println("Rate of Interest for AXIS: " + axis.getROI() + "%");
    }
}
