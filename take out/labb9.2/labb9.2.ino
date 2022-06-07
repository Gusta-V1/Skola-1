#include "Adafruit_VL53L0X.h" //Measurement sensor library

Adafruit_VL53L0X lox = Adafruit_VL53L0X();

long int thrPotVal = 0; //Throttle potentiometer value
int thrPotPin = A0; //Throttle potentiometer pin

long int wheelPotVal = 0; //Steering wheel potentiometer value
int wheelPotPin = A1; //Steering wheel potentiometer pin

int polR = 0; //Polarity right value
int polL = 0; //Polarity left value

long int motorR = 0; //Throttle right value
long int motorL = 0; //Throttle left value

long int gasR = 0;
long int gasL = 0;

int thrPotPinL = 10;
int thrPotPinR = 11;

int polPin1 = 4; //Polarity pin 1
int polPin2 = 5; //Polarity pin 2
int polPin3 = 6; //Polarity pin 3
int polPin4 = 7; //Polarity pin 4
int motorLPin = 10; //Left motor connected to this pin
int motorRPin = 11; //Right motor connected to this pin

void setup() {
  Serial.begin(115200); //Begin serial
  pinMode(thrPotPin, INPUT); //Throttle potentiometer pin is set to input
  pinMode(thrPotPin, INPUT); //Polarity potentiometer pin is set to input
  pinMode(polPin1, OUTPUT); //Sets polarity pin to output
  pinMode(polPin2, OUTPUT); //Sets polarity pin to output
  pinMode(polPin3, OUTPUT); //Sets polarity pin to output
  pinMode(polPin4, OUTPUT); //Sets polarity pin to output
  pinMode(motorLPin, OUTPUT); //Sets left motor pin to output
  pinMode(motorRPin, OUTPUT); //Sets right motor pin to output

  if (!lox.begin()) { //Fail safe if distance measurement sensor cannot be started
    Serial.println(F("Failed to boot VL53L0X"));
    while (1);
  }
  Serial.println( F("VL53L0X API Simple Ranging example\n\n"));

}

void loop() {
  thrPotVal = analogRead(thrPotPin); //Read throttle potentiometer
  wheelPotVal = analogRead(wheelPotPin); //Read polarity potentiometer

  motorL = (min(abs(255 - wheelPotVal), 255) * thrPotVal / 1023);
  motorR = (min(abs(767 - wheelPotVal), 255) * thrPotVal / 1023);


  if (wheelPotVal < 255) {
    polL = -100;
    digitalWrite(4, 0);
    digitalWrite(5, 1);
  }
  else {
    polL = 100;
    digitalWrite(4, 1);
    digitalWrite(5, 0);
  }
  if (768 < wheelPotVal) {
    polR = -100;
    digitalWrite(6, 1);
    digitalWrite(7, 0);
  }
  else {
    polR = 100;
    digitalWrite(6, 0);
    digitalWrite(7, 1);
  }

  //Print graphs
  //Serial.print(thrPotVal);
  //Serial.print("\t");
  //Serial.print(gasPotVal);
  //Serial.print("\t");
  Serial.print(gasR);
  Serial.print("\t");
  Serial.print(gasL);
  Serial.print("\t");
  Serial.print(motorR);
  Serial.print("\t");
  Serial.print(motorL);
  Serial.print("\t");
  Serial.print(polR);
  Serial.print("\t");
  Serial.print(polL); //Last print must be new line (ln)
  Serial.print("\t");

  VL53L0X_RangingMeasurementData_t measure;

  lox.rangingTest(&measure, false); // pass in 'true' to get debug data printout!

  if (measure.RangeStatus != 4) {  // phase failures have incorrect data
    if (measure.RangeMilliMeter < 200) {
      digitalWrite(4, 0);
      digitalWrite(5, 0);
      digitalWrite(6, 0);
      digitalWrite(7, 0);

      motorR = 0;
      motorL = 0;
    }
  }
  Serial.print("Distance (mm): ");
  Serial.println(measure.RangeMilliMeter);
  
  analogWrite(motorLPin, motorL);
  analogWrite(motorRPin, motorR);
}
