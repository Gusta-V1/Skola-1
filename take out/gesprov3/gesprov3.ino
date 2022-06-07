//INPUT: Read potentiometer
//LOGIC: Turn on LED according to potentiometer setting, turn off all other LED:s
//OUTPUT: Send values to LED:s


int potVal = 0; //Potentiometer value
int potPin = A0; //Potentiometer connected to pin A0
int LEDpin[8] = {2,3,4,5,6,7,8,9}; //Set all LED pins
int i = 0;

void setup() {
  Serial.begin(115200); //Start serial
  pinMode(potPin, INPUT); //Set potPin to input mode
  for(int i = 0; i < 8; i++){ //Set LED pins to output
    pinMode(LEDpin[i], OUTPUT);
  }
}

void loop() {
  potVal = analogRead(potPin); //potVal gets its value
  potVal = constrain(potVal, 100, 1000);
  Serial.println(potVal); //Print setting
  for (int i = 0; i < 8; i++){
    if (potVal > (i)*1023/8 && potVal < (i+1)*1023/8){
      digitalWrite(LEDpin[i], 1);
    }
    else{
      digitalWrite(LEDpin[i], 0);
    }
  }
}
