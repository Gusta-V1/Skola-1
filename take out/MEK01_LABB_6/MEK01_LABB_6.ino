/*
Input: Use analog read to measure voltage between photocell and resistor. Read button pin
Logic: If button is pressed assign levels. Map LEDval depending on levels.
Output: Send LED value to LED, write to serial monitor.
*/

int photo = 0; //Variable for photocell
int LEDval = 0; //Variable for LED
int photoPin = A1; //Photocell connected to pin A1
int LEDpin = 10; //LED connected to pin 10
int buttonPin = 13; //Button connected to pin 13
int buttonState = 1; //Button state binary
int minL = 5000; //Minimum level to assign
int maxL = 0; //Maximum level to assign
int buffert = 20; //Buffert for mapping

void setup(){
    Serial.begin(115200); //Start serial
    pinMode(buttonPin, INPUT_PULLUP); //Sets button pin to input pullup
    pinMode(LEDpin, OUTPUT); //Set pinmode for LED pin
    pinMode(photoPin, INPUT); //Set pinmode for analog photocell pin
}

void loop(){
    photo = analogRead(photoPin); //Read photocell value
    buttonState = digitalRead(buttonPin); //Read button state, binary
    
    if(buttonState == 0){ //Activate if button is pressed
      minL = min(minL, photo); //Set minimum level from photocell
      maxL = max(maxL, photo); //Set maximum level from photocell

      //Print set levels (when button is pressed)
      Serial.print(minL);
      Serial.print("\t");
      Serial.print(maxL);
      Serial.print("\n");
      }
      
    else{ //Logic runs when button is not pressed
    LEDval = map(photo, maxL-buffert, minL+buffert, 0, 255); //map levels to LED
    LEDval = constrain(LEDval, 0, 255); //LED can only operate between int 0, 255
    analogWrite(LEDpin, LEDval); //Output to LED

    //Prints
    Serial.print(photo);
    Serial.print("\t");
    Serial.print(LEDval);
    Serial.print("\n");
    }
}
