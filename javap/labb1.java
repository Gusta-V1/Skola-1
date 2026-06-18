package javap;
import java.util.Scanner;

public class labb1 { //Read knots, and print conversion to km/h

    public static void main(String[] args) {
        double ktspeed, speed_coeff = 1.852; //Declare vars, conversion coeff can be directly set to value
        try (Scanner scanner = new Scanner(System.in)) {
            System.out.print("Speed in kts: "); //Read input
            ktspeed = scanner.nextInt(); //Assign scanned entry to var
            System.out.println(ktspeed + " kts is apprx "+ktspeed*speed_coeff+" km/h"); //Print output and converts
        }
    }
}
