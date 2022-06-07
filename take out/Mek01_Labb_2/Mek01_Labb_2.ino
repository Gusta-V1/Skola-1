/**
  Input: Read buttons
  Logic: Increase or decrease blink frequency variable depending on input.
  Output: Send blink frequency (variable) to LED.
 **/

//Variables
int(buttonIncrease) = 0; //Variable for state of increase-blink button
int(buttonDecrease) = 0; //Variable for state of decrease-blink button
int(buttonIncreasePin) = 2; //Digital pin for increase-button
int(buttonDecreasePin) = 3; //Digital pin for decrease-button
int(freq) = 200; //LED frequency
int(delta) = 50; //Step size of each press to change frequency
const int ledPin = LED_BUILTIN; //Built in LED on pin 13
int ledState = LOW; //LED starts at off, LEDState is either on or off
unsigned long previousMillis = 0; //To calculate blink frequency, time starts at zero
unsigned long currentMillis = millis(); //To calculate blink frequency, current time

//Runs ONCE at start/reset
void setup() {
  pinMode(buttonIncreasePin, INPUT_PULLUP); //Pin set to input, enables pullup to eliminate lag
  pinMode(buttonDecreasePin, INPUT_PULLUP); //Pin set to input, enables pullup to eliminate lag
  pinMode(ledPin, OUTPUT); //Sets LED as output
  Serial.begin(115200); //Start serial port
}

//Program loop
void loop() {
  buttonIncrease = digitalRead(buttonIncreasePin); //Reads increase-button press
  buttonDecrease = digitalRead(buttonDecreasePin); //Reads decrease-button press

  if (buttonIncrease == 0) { //If increase-button is pressed add delta to frequency of blink
    freq += delta;
    delay(200); //For debounce
  }
  if (buttonDecrease == 0) { //If decrease-button is pressed subtract delta from frequency of blink
    freq -= delta;
    delay(200); //For debounce
  }
  freq = constrain(freq, 0, 1000); //Limits frequency of blink between 0 and 1000ms
  currentMillis = millis(); //Updates clocked time
 
  if (currentMillis - previousMillis >= freq) { //If elapsed time is equal to or more than desired frequency then switch LED state.
    previousMillis = currentMillis; //Update previous millis
    ledState =! ledState; //Switch LED state
  
  digitalWrite(ledPin, ledState); //Output to LED
  Serial.println(freq); //Print selected blink frequency
}
