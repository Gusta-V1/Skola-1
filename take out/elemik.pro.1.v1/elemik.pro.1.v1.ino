
#include <SPI.h>
#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>
#include "Adafruit_LC709203F.h"
#include <Adafruit_AHTX0.h>

//#define BUTTON_PIN_BITMASK 0x200000000 // 2^33 in hex for ext1

#define BUTTON_A 15

RTC_DATA_ATTR int bootCount = 0;

/*
Method to print the reason by which ESP32
has been awaken from sleep
*/
void print_wakeup_reason(){
  esp_sleep_wakeup_cause_t wakeup_reason;

  wakeup_reason = esp_sleep_get_wakeup_cause();

  switch(wakeup_reason)
  {
    case ESP_SLEEP_WAKEUP_EXT0 : Serial.println("Wakeup caused by external signal using RTC_IO"); break;
    case ESP_SLEEP_WAKEUP_EXT1 : Serial.println("Wakeup caused by external signal using RTC_CNTL"); break;
    case ESP_SLEEP_WAKEUP_TIMER : Serial.println("Wakeup caused by timer"); break;
    case ESP_SLEEP_WAKEUP_TOUCHPAD : Serial.println("Wakeup caused by touchpad"); break;
    case ESP_SLEEP_WAKEUP_ULP : Serial.println("Wakeup caused by ULP program"); break;
    default : Serial.printf("Wakeup was not caused by deep sleep: %d\n",wakeup_reason); break;
  }
}

void OLED(int volt, int batP, int temp, int hum){
  Adafruit_SSD1306 display = Adafruit_SSD1306(128, 32, &Wire);
  Serial.println("Starting OLED");
  // SSD1306_SWITCHCAPVCC = generate display voltage from 3.3V internally
  display.begin(SSD1306_SWITCHCAPVCC, 0x3C); // Address 0x3C for 128x32

  Serial.println("OLED begun");

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

float getVoltage(){
  Adafruit_LC709203F lc;
  if (!lc.begin()) {
    Serial.println(F("Couldnt find Adafruit LC709203F?\nMake sure a battery is plugged in!"));
    while (1) delay(10);
  }
  Serial.println(F("Found LC709203F"));
  Serial.print("Version: 0x"); Serial.println(lc.getICversion(), HEX);

  lc.setPackSize(LC709203F_APA_1000MAH);

  lc.setAlarmVoltage(3.8);

  return lc.cellVoltage();
  }

int getBatP(){
  Adafruit_LC709203F lc;
  if (!lc.begin()) {
    Serial.println(F("Couldnt find Adafruit LC709203F?\nMake sure a battery is plugged in!"));
    while (1) delay(10);
  }
  Serial.println(F("Found LC709203F"));
  Serial.print("Version: 0x"); Serial.println(lc.getICversion(), HEX);

  lc.setPackSize(LC709203F_APA_1000MAH);

  lc.setAlarmVoltage(3.8);

  return lc.cellPercent();
  }

int getTemp(){
  Adafruit_AHTX0 aht;

  Adafruit_Sensor *aht_temp;

  while (!Serial)
    delay(10); // will pause Zero, Leonardo, etc until serial console opens

  if (!aht.begin()) {
    Serial.println("Failed to find AHT10/AHT20 chip");
    while (1) {
      delay(10);
    }
  }

  aht_temp = aht.getTemperatureSensor();
  //----SETUP LOOP ENDS HERE----

  sensors_event_t temp;
  aht_temp->getEvent(&temp);
  return temp.temperature;
  delay(100);
  }

int getHum(){
  Adafruit_AHTX0 aht;

  Adafruit_Sensor *aht_humidity;

  while (!Serial)
    delay(10); // will pause Zero, Leonardo, etc until serial console opens

  if (!aht.begin()) {
    Serial.println("Failed to find AHT10/AHT20 chip");
    while (1) {
      delay(10);
    }
  }

  aht_humidity = aht.getHumiditySensor();
  //----SETUP LOOP ENDS HERE----

  sensors_event_t humidity;
  aht_humidity->getEvent(&humidity);
  return humidity.relative_humidity;
  delay(100);
  }

//----------------SETUP-------------------
void setup(){
  pinMode(BUTTON_A, INPUT_PULLUP);
  Serial.begin(115200);
  delay(1000); //Take some time to open up the Serial Monitor

  //Increment boot number and print it every reboot
  ++bootCount;
  Serial.println("Boot number: " + String(bootCount));

  //Print the wakeup reason for ESP32
  print_wakeup_reason();

  esp_sleep_enable_ext0_wakeup(GPIO_NUM_15,0); //1 = High, 0 = Low

  //If you were to use ext1, you would use it like
  //esp_sleep_enable_ext1_wakeup(BUTTON_PIN_BITMASK,ESP_EXT1_WAKEUP_ANY_HIGH);

  //Go to sleep now
  Serial.println("Going to sleep now");
  esp_deep_sleep_start();
  Serial.println("This will never be printed");
}


void loop(){
  //This is not going to be called
}
