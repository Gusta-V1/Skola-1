int potVal = 0; //Potentiometer value
int potPin = A0; //Potentiometer connected to pin A0
int LEDpin[6] = {3,5,6,9,10,11}; //Set all bar pins
int barVal = 0; //Value for dimmed bar setting
int LEDVal = 0;

void setup() {
  Serial.begin(115200); //Start serial
  pinMode(potPin, INPUT); //Set potPin to input mode
  for(int i = 0; i < 6; i++){ //Loop to set all bar pins to output
    pinMode(LEDpin[i], OUTPUT);
  }
}

void loop() {
  potVal = analogRead(potPin); //potVal gets its value
  barVal = map(potVal, 0, 1023, 0, 255*6);
  for (int i = 0; i < 6; i++){ //Loop to turn on bars
    if (potVal > (i*255)){ 
      barVal = min(LEDVal-(i*255),255);

      Serial.println(LEDVal);
      Serial.print("\t");
      analogWrite(LEDpin[i], barVal);
    }
    else{ //In case of setting being too low for lit bar then turn bar off
      digitalWrite(LEDpin[i], 0);
    }
  }
}
