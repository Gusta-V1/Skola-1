/**
 Input: Read buttons
 Logic: Increase or decrease blink frequency variable depending on input.
 Output: Send blink frequency (variable) to LED.
 **/

int(buttonIncrease) = 0; //Variable for state of increase-blink button
int(buttonDecrease) = 0; //Variable for state of decrease-blink button
int(buttonIncreasePin) = 2; //Digital pin for increase-button
int(buttonDecreasePin) = 3; //Digital pin for decrease-button
int(freq) = 200; //LED frequency
int(delta) = 50; //Ammount of time each press changes frequency

//Runs ONCE at start/reset
void setup() {
  pinMode(buttonIncreasePin, INPUT_PULLUP); //Enables pullup to eliminate lag
  pinMode(buttonDecreasePin, INPUT_PULLUP); //Enables pullup to eliminate lag
  pinMode(LED_BUILTIN, OUTPUT); //Sets LED as putput
  Serial.begin(115200); //Port
}

void loop() {
  buttonIncrease = digitalRead(buttonIncreasePin); //Reads increase-button press
  buttonDecrease = digitalRead(buttonDecreasePin); //Reads decrease-button press
  
  if (buttonIncrease == 0){ //If increase-button is pressed add delta to frequency of blink
    freq += delta;
  }
  if (buttonDecrease == 0){ //If decrease-button is pressed subtract delta from frequency of blink
    freq -= delta;
  }
  freq=constrain(freq, 0, 1000);

  digitalWrite(LED_BUILTIN, HIGH); //Turn LED on
  delay(freq); //Wait this ammount of time, keep current state
  digitalWrite(LED_BUILTIN, LOW); //Turn of LED
  delay(freq); //Wait this ammount of time, keep current state
  Serial.println(freq);
}
