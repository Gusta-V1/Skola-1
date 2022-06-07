/*
  Input: Read potentiometer state.
  Logic: Convert potentiometer integer to scale compatible with LED.
  Output: Output Integer to LED.
*/

int ledPin = 10; // LED connected to digital pin 9
int pot = 0; //Variable for potentiometer
int mappedPot = 0; //Value adjusted variable of potentiometer

void setup() {
  pinMode(ledPin, OUTPUT); //Set LED pin as output
  Serial.begin(115200); //BAUD rate
}

void loop() {
  pot = analogRead(A0); //Read value of potentiometer
  
  mappedPot = map(pot, 0, 1024, 0, 255); //Convert potentiometer to LED com
  
  analogWrite(ledPin, mappedPot); //Set LED to value from potentiometer
  Serial.print(pot); //Print potentiometer setting to monitor
  Serial.print("\t");
  Serial.println(mappedPot);
}
