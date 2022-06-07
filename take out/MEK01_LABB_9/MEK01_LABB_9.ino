int thrPotVal = 0; //Throttle potentiometer value
int thrPotPin = A0; //Throttle potentiometer pin

int polPotVal = 0; //Polarity potentiometer value
int polPotPin = A1; //Polarity potentiometer pin

int polR = 0; //Polarity right value
int polL = 0; //Polarity left value

int thrR = 0; //Throttle right value
int thrL = 0; //Throttle left value

int lrPinA = 2;
int lrPinB = 3;
int rrPinA = 4;
int rrPinB = 5;

int thrPinL = 10;
int thrPinR = 11;

void setup() {
  Serial.begin(38400); //Begin serial
  pinMode(thrPotPin, INPUT); //Throttle potentiometer pin is set to input
  pinMode(polPotPin, INPUT); //Polarity potentiometer pin is set to input

}

void loop() {
  thrPotVal = analogRead(thrPotPin); //Read throttle potentiometer
  polPotVal = analogRead(polPotPin); //Read polarity potentiometer

  if(thrPotVal < 512){ //Throttle right
    thrR = 255;
    } 
  else{
    if(thrPotVal < 768 && thrPotVal > 512){
      thrR = map(thrPotVal, 512, 768, 255, 0);
      }
      
    if(thrPotVal > 768){
      thrR = map(thrPotVal, 768, 1024, 0, 255);
    }
  }

    if(thrPotVal > 512){ //Throttle left
    thrL = 255;
    } 
  else{
    if(thrPotVal < 512 && thrPotVal > 256){
      thrL = map(thrPotVal, 256, 512, 0, 255);
      }
      
    if(thrPotVal < 256){
      thrL = map(thrPotVal, 0, 256, 255, 0);
    }
  }

  if(polPotVal < 255){ //Polarity right
    polR = -100;
    digitalWrite(lrPinA, 1);
    digitalWrite(lrPinB, 0);
    }
  else{
    polR = 100;
    digitalWrite(lrPinA, 0);
    digitalWrite(lrPinB, 1);
    }

  if(polPotVal > 768){ //Polarity left
    polL = -100;
    digitalWrite(rrPinA, 0);
    digitalWrite(rrPinB, 1);
    }
  else{
    polL = 100;
    digitalWrite(rrPinA, 1);
    digitalWrite(rrPinB, 0);
    }

   analogWrite(thrPinL, thrL);
   analogWrite(thrPinR, thrR);
   
   /*digitalWrite(5, thrL);
   digitalWrite(5, thrL);
   digitalWrite(5, thrL);
   digitalWrite(5, thrL);*/

//Print graphs
  Serial.print(thrPotVal);
  Serial.print("\t");
  Serial.println(polPotVal);
  Serial.print("\t");
  Serial.print(thrR);
  Serial.print("\t");
  Serial.print(thrL);
  Serial.print("\t");
  Serial.print(polR);
  Serial.print("\t");
  Serial.println(polL); //Last print must be new line (ln)
}
