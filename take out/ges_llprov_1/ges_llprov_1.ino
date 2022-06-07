/*
 * INPUT: Read button
 * LOGIC: If button is pressed and cycle is not running start LED cycle
 * OUTPUT: Send values to LED:s
 */

int LED[][6] = { //2D Array for LED configs
    {0,0,1,1,0}, //0, Cars green, peds red
    {0,1,0,1,0}, //1, Cars orange, peds red
    {1,0,0,1,0}, //2, Cars red, peds red
    {1,0,0,0,1}, //3, Cars red, peds green
    {1,0,0,1,0}, //4, Cars red, peds red
    {1,1,0,1,0}}; //5. Cars red + orange, peds red

int pins[] = {2,3,4,5,6}; //Pins used for LEDs
int button = 1; //Button state, starts off
int buttonPin = 7; //Button connected to pin 7
int cycleRun = 0; //If  cycle is active button should not have any input, cycleRun indicates if a cycle is running, starts off

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

  if(button == 0 && cycleRun == 0){ //Start cycle if button is pressed and no cycle is currently running
  
    cycleRun = 1; //1 indicates that cycle is running, this prevents button inputs when cycle is running
    
    delay(200); //For easier button release
    
    for(int u = 0; u<5; u++){ //Cars orange, peds red
    digitalWrite(pins[u], LED[1][u]); //Output to LED
    }
    delay(1000); //Wait this time until next change

    for(int u = 0; u<5; u++){ //Cars red, peds red
    digitalWrite(pins[u], LED[2][u]); //Output to LED
    }
    delay(2000); //Wait this time until next change

    for(int u = 0; u<5; u++){ //Cars red, peds green
    digitalWrite(pins[u], LED[3][u]); //Output to LED
    }
    delay(3000); //Wait this time until next change

    for(int u = 0; u<5; u++){ //Cars red, peds red
    digitalWrite(pins[u], LED[4][u]); //Output to LED
    }
    delay(2000); //Wait this time until next change

    for(int u = 0; u<5; u++){ //Cars red + orange, peds red
    digitalWrite(pins[u], LED[5][u]); //Output to LED
    }
    delay(1000); //Wait this time until next change

    for(int u = 0; u<5; u++){ //Cars green, peds red
    digitalWrite(pins[u], LED[0][u]); //Output to LED
    }

    cycleRun = 0; //Cycle is done, ready to be activated again
   }
   /*
   //For debug
   Serial.print(button);
   Serial.print("\t");
   Serial.println(cycleRun);
   */
};
