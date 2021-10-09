/*
Input: Read potentiometer values
Logic: Map potentiometer integers to LED compatible integers
Output: Send value of mapped potentiometer to corresponding led pin
*/

//Variables for potentiometer values
int pot[] = {0, 0, 0};

//Variables for LED compatible remapped potentiometer values
int mappedPot[] = {0, 0, 0};

//Assign LED pins
int ledPins[] = {6, 10, 11};

//Assign potentiometer pins
int potPins[] = {A1, A2, A3};

void setup() {
    for(int i = 0; i < 3; i++){ //For loop with range 3
    pinMode(ledPins[i], OUTPUT); //Set all led pins to output mode
  }
  Serial.begin(115200); //Set BAUD rate
}

void loop() {
  for (int i = 0; i < 3; i++){ //For loop with range 3

    //Input
    pot[i] = analogRead(potPins[i]); //Step through potentiometers and read each
    
    //Logic
    mappedPot[i] = map(pot[i], 0, 1023, 0, 255); //Map potentiometer values to LED compatible integers. CA LED Method 1: map to 255, 0
    //mappedPot[i] = 255- mappedPot[i]; //Uncomment for CA LED method 2.

    
    //Output:
    analogWrite(ledPins[i], mappedPot[i]); //Output mapped values to LED
    Serial.print(pot[i]); //Print potentiometer setting
    Serial.print("\t");  //Space column period
    Serial.print(mappedPot[i]); //Print LED setting
    Serial.print("\t"); //Space between column
  }
  Serial.print("\n"); //Break line
}