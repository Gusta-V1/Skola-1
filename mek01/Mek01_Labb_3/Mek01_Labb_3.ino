/**
  Input: Read buttons
  Logic: Increase or decrease dim setting. If both buttons are pressed, switch on/off state.
  Output: Send dim setting to LED.
 **/

int buttonIncrease = 0; //Variable for state of increase-dim button
int buttonDecrease = 0; //Variable for state of decrease-dim button
int buttonIncreasePin = 2; //Digital pin for increase-button
int buttonDecreasePin = 3; //Digital pin for decrease-button
int delta = 25; //Ammount of time each press changes frequency
int ledPin = 9; //LED on pin 9
int brightness = 0; //Brightness starts at 0
int onOff = 1; //Led starts turned on

//Runs ONCE at start/reset
void setup() {
  pinMode(buttonIncreasePin, INPUT_PULLUP); //Enables pullup to eliminate lag
  pinMode(buttonDecreasePin, INPUT_PULLUP); //Enables pullup to eliminate lag
  pinMode(ledPin, OUTPUT); //Sets LED as putput
  Serial.begin(115200); //Start serial port
}

void loop() {
  //Input:
  buttonIncrease = digitalRead(buttonIncreasePin); //Reads increase-button press
  buttonDecrease = digitalRead(buttonDecreasePin); //Reads decrease-button press
  
  //Logic:
  if (buttonIncrease == 0 && buttonDecrease == 0){ //If both buttons are pressed cycle on off state
    delay(200); //For debounce
    onOff =! onOff ; //Cycle state
    }
   if (onOff == 0){ //If state is set to off this block will run.
    analogWrite(ledPin, 0); //Turn of LED
    return; //Run mainloop again
    }
    
  else{ //If state is on, code program here.
  brightness = constrain(brightness, 0, 255); //Constrain because LED is only compatible with values 0, 255. 

  if(buttonIncrease == 0){ //If increase button is pressed
    brightness += delta; //Add increment to brightness
    delay(200);
  }
  
  if(buttonDecrease == 0){ //If decrease button is pressed
    brightness -= delta; //Subtract increment from brightness
    delay(200);
  }
    
  analogWrite(ledPin, brightness); //Send brightness to LED
  Serial.println(brightness); //Print brightness setting
}
}
