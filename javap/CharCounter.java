//Min mapp heter detta
//package javap;

import java.util.Scanner;

//2 inmatningar: Först en mening. Sedan ett och endast ett tecken. Utmatning: Skriver ut längd av mening, antal förekomster av tecken i mening, första och sista indexplats av tecken i mening. 
public class CharCounter {

    public static void main(String[] args) {

        try (Scanner scanner = new Scanner(System.in)) {
            System.out.print("Skriv in en mening: ");

            String sentence = null;
            while (sentence == null || sentence.length() <= 1) {
                System.out.print("Skriv in en mening: ");
                sentence = scanner.nextLine();
            }
            String letter = null;
            while (letter == null || letter.length() != 1) {
                System.out.print("Skriv in ett tecken: ");
                letter = scanner.nextLine();
            }

            System.out.println("Meningen har totalt " + sentence.length() + " tecken.");
            System.out.println("Tecknet " + letter + " förekommer " + countOccurrences(sentence, letter) + " gånger.");

            int idx = sentence.indexOf(letter);
            if (idx != -1) {
                System.out.println("Första gången på indexplats " + sentence.indexOf(letter) + ".");
                System.out.println("Sista gången på indexplats " + sentence.lastIndexOf(letter) + ".");
            } else {
                System.out.println("Tecknet har ingen indexplats");
            }
        }
    }

    // Denna räknar (och returnerar) hur många gånger tecken förekommer i mening
    // iterativt
    public static int countOccurrences(String sentence, String letter) {
        int count = 0;
        int index = 0;

        while ((index = sentence.indexOf(letter, index)) != -1) {
            count++;
            index += letter.length();
        }

        return count;
    }
}
