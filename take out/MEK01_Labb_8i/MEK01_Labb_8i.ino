/*
 Input:
 Read buttons
 Logic:
 If start button is pressed and clock is off, start counting.
 If stop button is pressed, pause time, if pressed again reset time.
 Output:
 Send clock time to 7 segment display
*/

int currentTime = 0; //Marked time
int startTime = 0; //Time that runs with millis
int savedTime = 0; //Time that's displayed when paused

int digitDisp = 0; //Digit to display
int startButton = 1; //Button to start time
int stopButton = 1; //Button to pause time, second activation -> reset
int startButtonPin = 10; //Pin for start button
int stopButtonPin = 11; //Pin for pause/reset button
int onOff = 0; //1 if clock is running, 0 if clock is paused/reset

int digit[10][7] = { //7 segment pin activation for number 0 to 9.
  {1, 1, 1, 1, 1, 1, 0}, //0
  {0, 1, 1, 0, 0, 0, 0}, //1
  {1, 1, 0, 1, 1, 0, 1}, //2
  {1, 1, 1, 1, 0, 0, 1}, //3
  {0, 1, 1, 0, 0, 1, 1}, //4
  {1, 0, 1, 1, 0, 1, 1}, //5
  {1, 0, 1, 1, 1, 1, 1}, //6
  {1, 1, 1, 0, 0, 0, 0}, //7
  {1, 1, 1, 1, 1, 1, 1}, //8
  {1, 1, 1, 1, 0, 1, 1}, //9
};

int pins[] = {2, 3, 4, 5, 6, 7, 8}; //Pins going to 7 segment display, order A -> F

void setup() {
  Serial.begin(115200); //Begin serial
  pinMode(startButtonPin, INPUT_PULLUP); //Button pin set to input pull up
  pinMode(stopButtonPin, INPUT_PULLUP); //Button pin set to input pull up
  for (int i = 0; i < 7; i++) { //Set pins to output for 7 segment display
    pinMode(pins[i], OUTPUT);
  }
  for (int i = 0; i < 7; i++) { //Initial displayed number is 0
    digitalWrite(pins[i], digit[0][i]);
  }
}

void loop() {
  startButton = digitalRead(startButtonPin); //Read start button
  stopButton = digitalRead(stopButtonPin); //Read pause/reset button

  if (startButton == 0 && onOff == 0) { //Start count if start button is pressed and clock is stopped
    onOff = 1; //1 means clock is running
    startTime = millis(); //Time where count started
    delay(200); //Delay for easier release
  }

  if (stopButton == 0) { //If stop is pressed this block runs
     if (onOff == 1){ //If clock was running it's supposed to be paused
     onOff = 0;
     savedTime = currentTime; //When time was paused is saved to be able to resume counting if so desired
     }

     else{ //If stop button was pressed but clock was not running, it's supposed to be reset
       for (int i = 0; i < 7; i++) { //Displayed number is reset to 0
          digitalWrite(pins[i], digit[0][i]);
        }
        digitDisp = 0; //Digit to display is reset to 0
        savedTime = 0; //Saved time is reset
     }
     delay(200); //For easier button release
  }

  if (onOff == 1){ //If clock is running time should be updated
    currentTime = ((millis() - startTime) + savedTime); //Current tracked time
    digitDisp = currentTime / 1000; //Update digit to display 
    for (int i = 0; i < 7; i++){ //Write digit to 7 segment display
      digitalWrite(pins[i], digit[digitDisp][i]);
      }
  }
    //Output to serial monitor
    Serial.print(currentTime);
    Serial.print("\t");
    Serial.print(savedTime);
    Serial.print("\t");
    Serial.print(digitDisp);
    Serial.print("\n");
  }
