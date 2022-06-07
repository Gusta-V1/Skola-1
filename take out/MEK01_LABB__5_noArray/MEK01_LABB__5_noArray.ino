/*
Input: Read potentiometer values.
Logic: Map potentiometer integers to LED compatible integers.
Output: Send value of potentiometer to corresponding pin.
*/

//Variables for potentiometer values
int(pot1) = 0;
int(pot2) = 0;
int(pot3) = 0;

//Variables for LED compatible remapped potentiometer values
int(mappedPot1) = 0;
int(mappedPot2) = 0;
int(mappedPot3) = 0;

//Assign LED pins
int(ledPin1) = 6
int(ledPin2) = 10
int(ledPin3) = 11

//Assign potentiometer pins
int(potPin1) = A1
int(potPin2) = A2
int(potPin3) = A3

void setup() {
  pinMode(ledPin1, OUTPUT); //Set LED 1 pin as output
  pinMode(ledPin2, OUTPUT); //Set LED 2 pin as output
  pinMode(ledPin3, OUTPUT); //Set LED 3 pin as output
  Serial.begin(115200); //Set BAUD rate
}

void loop() {
  //Read potentiometer settings
  analogRead(potPin1)
  analogRead(potPin2)
  analogRead(potPin3)

  //Remap potentiometer settings to LED comaptibels integers
  mappedPot1 = map(pot1, 0, 1024, 0, 255)
  mappedPot2 = map(pot2, 0, 1024, 0, 255)
  mappedPot3 = map(pot3, 0, 1024, 0, 255)

  //Write out each potentiometer set value to corresponding pin
  analogWrite(potPin1, mappedPotpin1)
  analogWrite(potPin2, mappedPotpin2)
  analogWrite(potPin3, mappedPotpin3)

  
}
