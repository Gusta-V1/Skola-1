#include <SPI.h>
#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>

void OLED(int volt, int batP, int temp, int hum){
  Adafruit_SSD1306 display = Adafruit_SSD1306(128, 32, &Wire);
  Serial.println("Starting OLED");
  // SSD1306_SWITCHCAPVCC = generate display voltage from 3.3V internally
  display.begin(SSD1306_SWITCHCAPVCC, 0x3C); // Address 0x3C for 128x32

  Serial.println("OLED begun");

  // Show image buffer on the display hardware.
  // Since the buffer is intialized with an Adafruit splashscreen
  // internally, this will display the splashscreen.
  //display.display();
  //delay(1000);

  // Clear the buffer.
  display.clearDisplay();
  display.display();

  Serial.println("IO test");

  // text display voltage
  display.setTextSize(2);
  display.setTextColor(SSD1306_WHITE);
  display.setCursor(0,0);
  display.println("Voltage: ");
  display.print(volt);
  display.display(); // actually display all of the above
  delay(2000);
  display.clearDisplay();

  // text display %

  display.setTextColor(SSD1306_WHITE);
  display.setCursor(0,0);
  display.println("Battery %:");
  display.print(batP);  
  display.display(); // actually display all of the above
  delay(2000);
  display.clearDisplay();

  // text display temp

  display.setTextColor(SSD1306_WHITE);
  display.setCursor(0,0);
  display.println("Temp: ");
  display.print(temp);
  display.display(); // actually display all of the above
  delay(2000);
  display.clearDisplay();

  // text display humidity

  display.setTextColor(SSD1306_WHITE);
  display.setCursor(0,0);
  display.println("Humid %: ");
  display.print(hum);
  display.display(); // actually display all of the above
  delay(2000);
  display.clearDisplay();
  display.display();
  }

void setup() {
  Serial.begin(115200);
  

}

void loop() {
  OLED(4, 97, 25, 37);
}
