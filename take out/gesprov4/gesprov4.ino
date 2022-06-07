int buttonSelect[4] = {0,0,0,0}; //Button values are stored in array
int levelSelect = 0; //Selected level to transfer to (0-3)
int currentLevel = 0; //Level that elevator starts transfering from (0-3)
int ledPins[4] = {2,3,4,5}; //LEDs connected to these pins
int buttonPins[4] = {6,7,8,9}; //Buttons connected to these pins

void setup() {
  Serial.begin(115200); //Start serial
  for(int i=0;i< 4; i++){ //Assign pinmodes
    pinMode(ledPins[i], OUTPUT); //Led pins are set to output
    pinMode(buttonPins[i], INPUT_PULLUP); //Buttons input pullup, negative logic
    }
}

void loop() {
  for(int i=0; i<4; i++){ //Read buttons and assign button values
    buttonSelect[i] = digitalRead(buttonPins[i]); 
    Serial.print(buttonSelect[i]); //Print current button values
    }
    Serial.print("\t");

  if(buttonSelect[0] == 0){ //Set selected level
    levelSelect = 0;
    }
  if(buttonSelect[1] == 0){ //Set selected level
    levelSelect = 1;
    }
  if(buttonSelect[2] == 0){ //Set selected level
    levelSelect = 2;
    }
  if(buttonSelect[3] == 0){ //Set selected level
    levelSelect = 3;
    }

  Serial.print("levelSelect = "); //Print selected level
  Serial.println(levelSelect);

  if(levelSelect > currentLevel){ //Level transfer up
    for(int i=currentLevel; i<= levelSelect; i++){ //Loop steps up
      digitalWrite(ledPins[i], 1); //Turn level light on
      delay(1000); //Wait 1s between level
      digitalWrite(ledPins[i], 0); //Turn level light off in order to move on to next level
      }
  }
  
  if(levelSelect < currentLevel){ //Level transfer down
    for(int i=currentLevel; i>= levelSelect; i--){ //Loop steps down
      digitalWrite(ledPins[i], 1); //Turn level light on
      delay(1000); //Wait 1s between level
      digitalWrite(ledPins[i], 0); //Turn level light off in order to move on to next level
      }
  }

  currentLevel = levelSelect; //Update current level when transfer is complete
  
  digitalWrite(ledPins[currentLevel], 1); //Display current level when not in transfer
}
