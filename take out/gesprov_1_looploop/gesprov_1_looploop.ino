/*
 * INPUT: Read button
 * LOGIC: If button is pressed and cycle is not running start LED cycle
 * OUTPUT: Send values to LED:s
 */

int LED[][7] = { //2D Array for LED configs
    {0,0,1,1,0}, //0, Cars green, peds red
    {0,1,0,1,0}, //1, Cars orange, peds red
    {1,0,0,1,0}, //2, Cars red, peds red
    {1,0,0,0,1}, //3, Cars red, peds green
    {1,0,0,1,0}, //4, Cars red, peds red
    {1,1,0,1,0}, //5. Cars red + orange, peds red
    {0,0,1,1,0}}; //6, Cars green, peds red

int pins[] = {2,3,4,5,6}; //Pins used for LEDs
int delayTime[] = {0, 1000, 2000, 3000, 2000, 1000, 0}; //Delays between stages (between row change in 2D array)
int button = 1; //Button state, starts off
int buttonPin = 7; //Button connected to pin 7

void setup() {
  Serial.begin(115200); //Start serial
  pinMode(buttonPin, INPUT_PULLUP); //Set button pin to input pullup
  
  for(int i = 0; i<5; i++){ //Set LED pin modes and assign initial condition
    pinMode(pins[i], OUTPUT); //Set pinmodes
    digitalWrite(pins[i], LED[0][i]); //Assign initial condition
    };
}

void loop() {
  button = digitalRead(buttonPin); //Read button state and assign to variable

  if(button == 0){ //Start cycle if button is pressed and no cycle is currently running
    delay(200); //For easier button release
    
    for(int u = 0; u<7; u++){ //Nestled for loop, u indicates stage number, stage = row in 2D array
      for(int i = 0; i<5; i++){ //Loop to output to LED:s; i cycles through all five LED:s and gives them correct value from correct row in 2D array
         digitalWrite(pins[i], LED[u][i]); //Output to LED
        }
      delay(delayTime[u]); //Get delay time from array, delay is relevant to current stage of cycle, therfore u is used
    }
   /*
   //For debug
   Serial.print(button);
   Serial.print("\t");
   Serial.println(cycleRun);
   */
  }
};
