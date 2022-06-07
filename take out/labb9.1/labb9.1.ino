int motorVal = 0; //Throttle potentiometer value
int motorPotPin = A0; //Throttle potentiometer pin

int polPotVal = 0; //Polarity potentiometer value
int polPotPin = A1; //Polarity potentiometer pin

int polR = 0; //Polarity right value
int polL = 0; //Polarity left value

int motorR = 0; //Throttle right value
int motorL = 0; //Throttle left value

int motorPotPinL = 10;
int motorPotPinR = 11;

void setup() {
  Serial.begin(38400); //Begin serial
  pinMode(motorPotPin, INPUT); //Throttle potentiometer pin is set to input
  pinMode(motorPotPin, INPUT); //Polarity potentiometer pin is set to input
  pinMode(2, OUTPUT);
  pinMode(3, OUTPUT);
  pinMode(4, OUTPUT);
  pinMode(5, OUTPUT);
  pinMode(10, OUTPUT);
  pinMode(11, OUTPUT);
}

void loop() {
  motorVal = analogRead(motorPotPin); //Read throttle potentiometer
  polPotVal = analogRead(polPotPin); //Read polarity potentiometer

  motorL = min(abs(map(motorVal, 0, 512, -255, 255)), 255);
  motorR = min(abs(map(motorVal, 512, 1023, -255, 255)), 255);

  if (polPotVal < 255) {
    polL = -100;
    digitalWrite(2, 0);
    digitalWrite(3, 1);
  }
  else {
    polL = 100;
    digitalWrite(2, 1);
    digitalWrite(3, 0);
  }
  if (768 < polPotVal) {
    polR = -100;
    digitalWrite(4, 1);
    digitalWrite(5, 0);
  }
  else {
    polR = 100;
    digitalWrite(4, 0);
    digitalWrite(5, 1);
  }

  analogWrite(10, motorL);
  analogWrite(11, motorR);

  //Print graphs
  //Serial.print(thrPotVal);
  //Serial.print("\t");
  //Serial.print(polPotVal);
  //Serial.print("\t");
  Serial.print(motorR);
  Serial.print("\t");
  Serial.print(motorL);
  Serial.print("\t");
  Serial.print(polR);
  Serial.print("\t");
  Serial.println(polL); //Last print must be new line (ln)
}
