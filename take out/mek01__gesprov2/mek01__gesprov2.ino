/*
 * INPUT: READ BUTTONS
 * LOGIC: SET BLINK INTERVAL ACCORDING TO WHICH BUTTON WAS PRESSED, IF ON/OFF BUTTON WAS PRESSED TELL SYSTEM TO SWITCH LED ON/OFF
 * OUTPUT: SEND VALUES TO LED
 */

int LEDpin = 2; //LED connected to pin 2
int buttonPins[] = {3,4,5};
int buttonStates[] = {1,1,1}; //All buttons start off
int LEDstate = 0; //LED on or off, start off
int delayTime = 0; //Time between blinks in ms
int onOff = 0; //Start off
unsigned long previousMillis = 0; //To calculate blink interval, time starts at zero
unsigned long currentMillis = millis(); //To calculate blink interval, current time

void setup() {
  Serial.begin(115200); //Start serial
  pinMode(LEDpin, OUTPUT); //Set LED pin to output
  for(int i=0; i<3; i++){ //Set buttons to input pullup
    pinMode(buttonPins[i], INPUT_PULLUP);
    }
  digitalWrite(LEDpin, LEDstate); //Start with LED steady
  Serial.println("start off"); //Print mode
}

void loop() {
  //INPUT
  for(int i=0; i<3; i++){//Read buttons and assign button states
    buttonStates[i] = digitalRead(buttonPins[i]);
    }

   //LOGIC
   if(buttonStates[1] == 0 && onOff == 1){//Fast blink
    delay(200); //For easier press
    delayTime = 300; //Set interval time
    Serial.println("fast"); //Print mode
    
    }
   if(buttonStates[2] == 0 && onOff == 1){//Slow blink
    delay(200); //For easier press
    delayTime = 600; //Set interval time
    Serial.println("slow"); //Print mode
    }

    if(buttonStates[0] == 0){ //Switch on/off if pressed
      delay(200); //For easier press
      onOff = !onOff; //Switch on/off
      Serial.println("Switched on/off"); //Print mode
    }

    currentMillis = millis(); //Update clocked time

    //OUTPUT
    if(onOff == 0){ //If onOff is set to 0 LED should be turned off
        digitalWrite(LEDpin, 0); //If onOff is set to 0 LED should be turned off
        }

    if (onOff == 1 && ((currentMillis - previousMillis) >= delayTime)) { //If system is on AND elapsed time is equal to or more than delayTime switch LED state.
        previousMillis = currentMillis; //Update previous millis
        LEDstate = !LEDstate; //Switch LED state
        digitalWrite(LEDpin, LEDstate); //Output to LED
      }
}
