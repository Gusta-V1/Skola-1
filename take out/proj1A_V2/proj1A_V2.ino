//Includes:
#include "config.h"
#include <SPI.h>
#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>
#include "Adafruit_LC709203F.h"
#include <Adafruit_AHTX0.h>
#include <Adafruit_Sensor.h>
#include <Adafruit_INA219.h>

//Component initialization
Adafruit_SSD1306 display = Adafruit_SSD1306(128, 32, &Wire);
Adafruit_LC709203F lc;
Adafruit_AHTX0 aht;
Adafruit_INA219 ina219;
sensors_event_t temp, humidity;
esp_sleep_wakeup_cause_t wakeup_reason;

//Defines
#define BUTTON_A 15
#define uS_TO_S_FACTOR 1000000ULL  /* Conversion factor for micro seconds to seconds */

//Vars
int connectRetry = 0; //Times connection cycle has repeated
int sleep_time_ms = 0;
int hours = 0; //Hours from feed
float current_mA = 0; //Measured INA219 current
float currentAverageSample = 0; //Average INA219 current from 1000 samples
bool handleISOexecute = false; //ISO feed recieved true/false
bool handleSecsexecute = false; //Seconds feed recieved true/false
bool OLEDexecute = false; //OLED completed full cycle true/false
bool connectExecute = false; //Connection established true/false

//RTC vars
RTC_DATA_ATTR int bootCount = 0; //Times system has booted up from deep sleep
RTC_DATA_ATTR int connectFailCount = 0; //Times system failed to connect to network
RTC_DATA_ATTR int TIME_TO_SLEEP = 10 * 60; // Time ESP32 will go to sleep (in seconds)
static RTC_DATA_ATTR struct timeval sleep_enter_time; //When system started deep sleep

struct timeval now;

AdafruitIO_Group *group = io.group("volt.temp");
// set up the 'time/seconds' topic
AdafruitIO_Time *seconds = io.time(AIO_TIME_SECONDS);
// set up the 'time/ISO-8601' topic
AdafruitIO_Time *iso = io.time(AIO_TIME_ISO);

Adafruit_Sensor *aht_temp;
Adafruit_Sensor *aht_humidity;

// message handler for the seconds feed
void handleSecs(char *data, uint16_t len) {
  Serial.print("Seconds Feed: ");
  Serial.println(data);
  handleSecsexecute = true;
  Serial.print("handleSecs var ");
  Serial.println(handleSecsexecute);
}

// message handler for the ISO-8601 feed
void handleISO(char *data, uint16_t len) {
  Serial.print("Hours: ");
  struct tm tm = {0};
  // Convert to tm struct
  strptime(data, "%Y-%m-%dT%H:%M:%SZ", &tm);
  hours = tm.tm_hour;
  Serial.println(tm.tm_hour);
  handleISOexecute = true;
  Serial.print("handleISO var ");
  Serial.println(handleISOexecute);
}

void blinkLED(int times, int interval) { //Times = times led turns on/off, speed = time between blinks in ms
  for (int i = 0; i < times; i++) {
    digitalWrite(LED_BUILTIN, 1);
    delay(interval);
    digitalWrite(LED_BUILTIN, 0);
    delay(interval);
  }
}

void getSleepTimeTimer() { //Calculate sleep time for when system woke up from timer
  if (getBatP() < 3) { //Battery if:s, first factor is ammount of minutes
    TIME_TO_SLEEP = 30 * 60;
  }

  if (getBatP() < 4) {
    TIME_TO_SLEEP = 20 * 60;
  }

  if (getBatP() < 6) {
    TIME_TO_SLEEP = 15 * 60;
  }
  else {
    TIME_TO_SLEEP = 10 * 60;
  }

  if (handleISOexecute == true && handleSecsexecute == true) {
    if (hours > 18 or 6 > hours) {
      TIME_TO_SLEEP = 35 * 60;
    }

    handleISOexecute = false;
    handleSecsexecute = false;
    goToSleep();
  }
}

void getSleepTimeButton() { //Calculate sleep time for when system woke up from button press
  gettimeofday(&now, NULL);
  sleep_time_ms = (now.tv_sec - sleep_enter_time.tv_sec) * 1000 + (now.tv_usec - sleep_enter_time.tv_usec) / 1000;
  TIME_TO_SLEEP = TIME_TO_SLEEP - sleep_time_ms / 1000;
  goToSleep();
}

void OLED() { //Cycle to display all sensor values on OLED display
  
  Serial.println("Starting OLED");
  display.begin(SSD1306_SWITCHCAPVCC, 0x3C); // Address 0x3C for 128x32
  Serial.println("OLED begun");

  // Clear the buffer.
  display.clearDisplay();
  display.display();

  // text display voltage
  display.setTextSize(2);
  display.setTextColor(SSD1306_WHITE);
  display.setCursor(0, 0);
  display.println("Voltage: ");
  display.print(getVoltage());
  display.print(" V");
  display.display(); // actually display all of the above
  delay(2000);
  display.clearDisplay();

  // text display current
  display.setTextSize(2);
  display.setTextColor(SSD1306_WHITE);
  display.setCursor(0, 0);
  display.println("Current : ");
  display.print(getCurrent());
  display.print(" mA");
  display.display(); // actually display all of the above
  delay(2000);
  display.clearDisplay();
  display.display();

  // text display %
  display.setTextSize(2);
  display.setTextColor(SSD1306_WHITE);
  display.setCursor(0, 0);
  display.println("Battery %:");
  display.print(getBatP());
  display.print(" %");
  display.display(); // actually display all of the above
  delay(2000);
  display.clearDisplay();

  // text display temp
  display.setTextSize(2);
  display.setTextColor(SSD1306_WHITE);
  display.setCursor(0, 0);
  display.println("Temp: ");
  display.print(getTemp());
  display.print(" c");
  display.display(); // actually display all of the above
  delay(2000);
  display.clearDisplay();

  // text display humidity
  display.setTextSize(2);
  display.setTextColor(SSD1306_WHITE);
  display.setCursor(0, 0);
  display.println("Humid : ");
  display.print(getHum());
  display.print(" %");
  display.display(); // actually display all of the above
  delay(2000);
  display.clearDisplay();
  display.display();

  OLEDexecute = true; //Cycle has completed
}

float getVoltage() { //Returns votage
  return lc.cellVoltage();
}

int getBatP() { //Returns bat %
  return lc.cellPercent();
}

int getTemp() { //Returns temperature
  aht_temp = aht.getTemperatureSensor();
  aht_temp->getEvent(&temp);
  return temp.temperature;
}

int getHum() { Returns humidity
  aht_humidity = aht.getHumiditySensor();
  aht_humidity->getEvent(&humidity);
  return humidity.relative_humidity;
  delay(100);
}

float getCurrent() { //Returns average current sample
  uint32_t currentFrequency;
  for(int i=0, i < 1000, i++){ //Add 1000 samples
    current_mA += ina219.getCurrent_mA();
    }
    currentAverageSample = (current_mA / 1000); //Divide 1000 samples to get average
  return currenAverageSample;
}

void pub() {
  group->set("voltage", getVoltage());
  group->set("battery-%", getBatP());
  group->set("temp", getTemp());
  group->set("hum", getHum());
  group->set("current", getCurrent());
  group->set("connect-fails", connectFailCount);
  group->save();

  Serial.print("sending voltage ");
  Serial.println(getVoltage());
  Serial.print("sending battery-% ");
  Serial.println(getBatP());
  Serial.print("sending temp ");
  Serial.println(getTemp());
  Serial.print("sending hum ");
  Serial.println(getHum());
  Serial.print("sending current ");
  Serial.println(getCurrent());
  Serial.print("sending connect-fails ");
  Serial.println(connectFailCount);
  Serial.println("GROUP PUBLISH COMPLETE");

  connectFailCount = 0; //Reset network fail counter
  getSleepTimeTimer();
}

void goToSleep() {
  ina219.powerSave(true);  //INA goes to sleep

  TIME_TO_SLEEP = max(TIME_TO_SLEEP, 1); //Fail safe against negative sleep time
  esp_sleep_enable_timer_wakeup(TIME_TO_SLEEP * uS_TO_S_FACTOR);
  Serial.println("Setup ESP32 to sleep for " + String(TIME_TO_SLEEP) + " seconds");
  //Go to sleep now
  Serial.println("Going to sleep now");
  Serial.flush();
  gettimeofday(&sleep_enter_time, NULL);
  esp_deep_sleep_start();
}

void connectNetwork() {
  //_____NETWORK_____
  Serial.println("Connecting to Adafruit IO");
  io.connect();

  // wait for a connection
  while (io.status() < AIO_CONNECTED && connectRetry <= 20) {
    Serial.println(io.statusText());
    ++connectRetry;
    delay(500);
    blinkLED(5, 100); //LED blinks fast five times when waiting for connection
  }

  if(connectRetry > 20 && connectFailCount <= 3){ //Stage 1 connection fail
    ++connectFailCount;
    blinkLED(5, 2000); //Indicate stage 1 fail with LED
    Serial.println("Stage 1 fail, failed to connect, will sleep for 1 minute and retry");
    TIME_TO_SLEEP = 1 * 60; //1 minute
    goToSleep();
    }

  if(connectFailCount > 3){ //Stage 2 connection fail
    blinkLED(1, 6000); //Indicate stage 2 fail with LED
    Serial.println("Stage 2 fail, failed to connect, will sleep for 30 minutes and retry");
    TIME_TO_SLEEP = 30 * 60; //30 minutes
    goToSleep();
    }

  //We are connected
  Serial.println(io.statusText());
  connectExecute = true;
  blinkLED(3, 1000); //LED blinks slow 3 times when connection is established

  // attach message handler for the seconds feed
  seconds->onMessage(handleSecs);
  // attach a message handler for the ISO feed
  iso->onMessage(handleISO);

  io.run();
}

//----------------SETUP-------------------
void setup() {
  Serial.begin(115200);
  pinMode(BUTTON_A, INPUT_PULLUP);
  pinMode(LED_BUILTIN, OUTPUT);
  
  //_______Component begins________
  //LC
  if (!lc.begin()) {
    Serial.println(F("Couldnt find Adafruit LC709203F?\nMake sure a battery is plugged in!"));
    while (1) delay(10);
  }
  Serial.println(F("Found LC709203F"));
  Serial.print("Version: 0x"); Serial.println(lc.getICversion(), HEX);

  lc.setPackSize(LC709203F_APA_1000MAH);
  lc.setAlarmVoltage(3.8);

  //AHT
  if (!aht.begin()) {
    Serial.println("Failed to find AHT10/AHT20 chip");
    while (1) {
      delay(10);
    }
  }

  //INA219
  if (! ina219.begin()) {
    Serial.println("Failed to find INA219 chip");
    while (1) {
      delay(10);
    }
  }

  //Button init
  esp_sleep_enable_ext0_wakeup(GPIO_NUM_15, 0); //1 = High, 0 = Low //Button A

  //Increment boot number and print it every reboot
  ++bootCount;
  Serial.println("Boot number: " + String(bootCount));

  ina219.powerSave(false);  //INA wakes up
}

void loop() {

  wakeup_reason = esp_sleep_get_wakeup_cause();

  switch (wakeup_reason)
  {
    case ESP_SLEEP_WAKEUP_EXT0 : //If button is pressed
      Serial.println("Wakeup caused by external signal using RTC_IO");
      if (OLEDexecute == false) {
        OLED();
      }
      getSleepTimeButton();
      break;

    default :
      if (bootCount == 1) {//If reset was pressed values shall be displayed and then published
        OLED();
      }

      if (connectExecute == false) {
        connectNetwork();
      }
      
      io.run();

      Serial.println("Waiting for time feed");

      if (handleISOexecute == true && handleSecsexecute == true) {
        pub();
      }
      break;
  }
}
