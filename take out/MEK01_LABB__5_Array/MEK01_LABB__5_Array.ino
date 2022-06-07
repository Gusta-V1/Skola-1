/*
Input: Read potentiometer values
Logic: Map potentiometer integers to LED compatible integers
Output: Send value of potentiometer to corresponding pin
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
    for(int i = 0; i < 3; i++){
    pinMode(ledPins[i], OUTPUT)
  }
  Serial.begin(115200); //Set BAUD rate
}

void loop() {
  for (int i = 0; i < 3; i++){
    pot[i] = analogRead(potPin[i])
    mappedPot[i] = map(pot[i], 0, 1024, 0, 255)
    analogWrite(ledPin[i], mappedPot[i])
  }
}
