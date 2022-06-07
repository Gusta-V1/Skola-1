/*
Input: Use analog read to measure voltage between photocell and resistor
Logic: Map LEDstate depending on photocell.
Output: Send LED value to LED, write to serial monitor.
*/

int photo = 0;
int LEDval = 0;
int photoPin = A1;
int LEDpin = 10;
//int min = 420;
//int max = 740;


void setup()
{
    pinMode(LEDpin, OUTPUT); //Set pinmode for LED
    pinMode(photoPin, INPUT); //Set pinmode for photocell
    Serial.begin(115200); //Start serial
}

void loop()
{
    photo = analogRead(photoPin); //Read photocell value
    LEDval = map(photo, 600, 440, 0, 255); //
    LEDval = constrain(LEDval, 0, 255); //LED can only operate between int 0, 255
    analogWrite(LEDpin, LEDval); //Output to LED

    //Prints
    Serial.print(photo);
    Serial.print("\t");
    Serial.print(LEDval);
    Serial.print("\n");
    
    
}
