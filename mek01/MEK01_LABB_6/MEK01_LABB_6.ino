/*
Input: Use analog read to measure voltage between photocell and resistor
Logic: Set LEDstate depending on photocell.
Output: Send LED value to LED, write to serial monitor.
*/

int photo = 0;
bool LEDstate = 0;

void setup()
{
    pinMode(10, OUTPUT); //Set pinmode for LED
    pinMode(11, INPUT); //Set pinmode for photocell
    Serial.begin(115200); //Set BAUD rate
}

void loop()
{
    photo = analogRead(11);
    Serial.println(photo);
}