#include "Adafruit_VL53L0X.h" //Measurement sensor library

Adafruit_VL53L0X lox = Adafruit_VL53L0X();

int polPin1 = 4; //Polarity pin 1
int polPin2 = 5; //Polarity pin 2
int polPin3 = 6; //Polarity pin 3
int polPin4 = 7; //Polarity pin 4
int motorLPin = 10; //Left motor connected to this pin
int motorRPin = 11; //Right motor connected to this pin
int thrPotPin = A0; //Throttle potentiometer pin
int wheelPotPin = A1; //Steering wheel potentiometer pin

long int thrPotVal = 0; //Throttle potentiometer value
long int wheelPotVal = 0; //Steering wheel potentiometer value

int polR = 0; //Polarity right value
int polL = 0; //Polarity left value

long int motorR = 0; //Throttle right value
long int motorL = 0; //Throttle left value

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

  if (!lox.begin()) { //Fail safe if distance measurement sensor cannot be initialized
    Serial.println(F("Failed to boot VL53L0X"));
    while (1);
  }
}

void loop() {
  thrPotVal = analogRead(thrPotPin); //Read throttle potentiometer
  wheelPotVal = analogRead(wheelPotPin); //Read polarity potentiometer

  motorL = (min(abs(255 - wheelPotVal), 255) * thrPotVal / 1023); //Calcualte power value to send to left motor
  motorR = (min(abs(767 - wheelPotVal), 255) * thrPotVal / 1023); //Calcualte power value to send to right motor


  if (wheelPotVal < 255) { //If steering wheel is turned to the left corresponding digital signals should be sent to H-bridge
    polL = -100; //For use in serial plotter
    digitalWrite(polPin1, 0);
    digitalWrite(polPin2, 1);
  }
  else { //If steering wheel is turned to the right corresponding digital signals should be sent to H-bridge
    polL = 100; //For use in serial plotter
    digitalWrite(polPin1, 1);
    digitalWrite(polPin2, 0);
  }
  if (768 < wheelPotVal) { //If steering wheel is turned to the right corresponding digital signals should be sent to H-bridge
    polR = -100; //For use in serial plotter
    digitalWrite(polPin3, 1);
    digitalWrite(polPin4, 0);
  }
  else { //If steering wheel is turned to the left corresponding digital signals should be sent to H-bridge
    polR = 100; //For use in serial plotter
    digitalWrite(polPin3, 0);
    digitalWrite(polPin4, 1);
  }

//Serial plotter/monitor prints, must be separated with tab to show in plotter
  Serial.print(motorR);
  Serial.print("\t");
  Serial.print(motorL);
  Serial.print("\t");
  Serial.print(polR);
  Serial.print("\t");
  Serial.print(polL);
  Serial.print("\t");

  VL53L0X_RangingMeasurementData_t measure; //Required for measurment

  lox.rangingTest(&measure, false); // pass in 'true' to get debug data printout!

  if (measure.RangeStatus != 4) {  // phase failures have incorrect data
    if (measure.RangeMilliMeter < 200) { //Brake/stop if object is sensed less than 20 cm from distance sensor
      digitalWrite(polPin1, 0);
      digitalWrite(polPin2, 0);
      digitalWrite(polPin3, 0);
      digitalWrite(polPin4, 0);

      motorR = 0; //Shuts power to right engine
      motorL = 0; //Shuts power to left engine
    }
  }
  
  //Serial plotter/monitor prints
  Serial.print(motorR);
  Serial.print("\t");
  Serial.print(motorL);
  Serial.print("\t");
  Serial.print(polR);
  Serial.print("\t");
  Serial.print(polL);
  Serial.print("\t");
  Serial.print("Distance (mm): "); 
  Serial.println(measure.RangeMilliMeter);
  
  analogWrite(motorLPin, motorL); //Output power to left engine
  analogWrite(motorRPin, motorR); //Output power to right engine
}
