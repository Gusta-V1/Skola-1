#include "config.h"

#include <Adafruit_Sensor.h>
#include "Adafruit_LC709203F.h"
#include <Adafruit_AHTX0.h>
#include <Adafruit_INA219.h>

#include <SPI.h>
#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Fonts/FreeMono9pt7b.h>
#include <Adafruit_SSD1306.h>

//ESP32 button mapping
#define BUTTON_A 15
#define BUTTON_B 32
#define BUTTON_C 14

//Ext1 button HEX
#define BUTTON_PIN_BITMASK 0x4000

#define uS_TO_S_FACTOR 1000000  //Conversion factor for micro seconds to seconds

#define LED_BUILTIN 13 //Built in LED (used in blinkLED)

//Initializers
Adafruit_SSD1306 display = Adafruit_SSD1306(128, 32, &Wire);
Adafruit_LC709203F lc;
Adafruit_INA219 ina219;
Adafruit_AHTX0 aht;
sensors_event_t humidityEvent, tempEvent;
esp_sleep_wakeup_cause_t wakeup_reason;

//IO group feed
AdafruitIO_Group *group = io.group("Solcellsdriven WiFi-sensor");

//variables sent to IO feeds
float voltage = 0;
float battPercent = 0;
float thermTemp = 0;
float averageCurrent = 0;
float current_mA = 0;
float temp = 0;
float humidity = 0;

//connectIO variables
RTC_DATA_ATTR int wifiAbort = 0;
int wifiRetry = 0;
int wifiConsecutiveAbort = 0;

//Adafruit IO 'seconds' feed
AdafruitIO_Time *seconds = io.time(AIO_TIME_SECONDS);

// Adafruit IO 'time/ISO-8601' feed
AdafruitIO_Time *iso = io.time(AIO_TIME_ISO);

//sleepTimeCalc variables
int sleepTime = 10;
unsigned long secondsTmDiff = 0;
RTC_DATA_ATTR unsigned long sleepStart = 0;


//handleSecs variable
unsigned long secondsTm = 0;

//handleISO variable
int hoursTm = 0;
bool HandleISOexecute = false;

//blinkLED variables
int times = 0;
int interval = 0; //interval in milliseconds
const int ledPin = LED_BUILTIN;
int ledState = LOW;

int delayCount = 6; //Amount of delay after sleep time is displayed on oled

//Blink led at given amount of times and interval
void blinkLED(int times, int interval) {

  for (int i = 0; i < times; i++) {
    for (int i = 0; i < 2; i++) {
      ledState = ! ledState;
      delay(interval);
      digitalWrite(ledPin, ledState);
    }
  }
}

//Message handler for the seconds feed when deep sleep is intialized by Ext0 wakeup
void handleSecsExt0(char *data, uint16_t len) {
  secondsTm = atoi(data);
  sleepTimeCalcExt0();
}

//Message handler for the seconds feed when deep sleep is intialized by Ext1 wakeup
void handleSecsExt1(char *data, uint16_t len) {
  secondsTm = atoi(data);
  sleepTimeCalcExt1();
}

//Message handler for the seconds feed when deep sleep is intialized by timer
void handleSecsTimer(char *data, uint16_t len) {
  secondsTm = atoi(data);
  sleepTimeCalcTimer();
}

//Message handler for the ISO-8601 feed (only using hours)
void handleISO(char *data, uint16_t len) {
  Serial.print("Hours: ");
  struct tm tm = {0};
  // Convert to tm struct
  strptime(data, "%Y-%m-%dT%H:%M:%SZ", &tm);
  hoursTm = tm.tm_hour;
  Serial.println(tm.tm_hour);
  HandleISOexecute = true;
}

//Calculate time to sleep when intialized by timer
int sleepTimeCalcTimer() {

  //variable sleeptime depending on battery level
  if (battPercent < 3) {
    sleepTime = 30;
  }
  if (3 < battPercent < 4) {
    sleepTime = 20;
  }
  if (4 < battPercent < 6) {
    sleepTime = 15;
  }
  if (6 < battPercent) {
    sleepTime = 10;
  }

  if (HandleISOexecute == true) {

    if (18 < hoursTm or hoursTm < 6) { //Longer sleeptime during nighttime
      sleepTime = 35;
    }

    sleepTime = sleepTime * 60; //Convert to seconds

    sleepStart = secondsTm; //set time of deep sleep initialization

    serialPrintVal();

    HandleISOexecute = false;

    deepSleep();
  }
}

//Calculate time to sleep when intialized by Ext wakeup
int sleepTimeCalcExt0() {

  if (battPercent < 3) {
    sleepTime = 30;
  }
  if (3 < battPercent < 4) {
    sleepTime = 20;
  }
  if (4 < battPercent < 6) {
    sleepTime = 15;
  }
  if (6 < battPercent) {
    sleepTime = 10;
  }

  if (HandleISOexecute == true) {

    if (18 < hoursTm or hoursTm < 6) { //Longer sleeptime during nighttime
      sleepTime = 35;
    }

    sleepTime = sleepTime * 60; //Convert to seconds

    secondsTmDiff = (secondsTm - sleepStart); //Calculate how much time has passed since deep sleep was started by timer

    sleepTime -= (secondsTmDiff);

    sleepTime = sleepTime - (5 * 3); //compensate for delays used in following displayVal functions
    if (sleepTime < 1) { //If the variable becomes negative the program sets it to zero in order to maintain functional deep sleep
      sleepTime = 1;
    }

    serialPrintVal();

    displayVal("Batt %", battPercent, 2, "");
    displayVal("Voltage", voltage, 2, " V");
    displayVal("Current", averageCurrent, 2, " mA");
    displayVal("Sleep time", sleepTime, 0, " sec");
    displayVal("IO Fail", wifiAbort, 0, "");
    display.display(); //Clear display

    HandleISOexecute = false;

    deepSleep();
  }
}

//Calculate time to sleep when intialized by Ext wakeup
int sleepTimeCalcExt1() {

  if (battPercent < 3) {
    sleepTime = 30;
  }
  if (3 < battPercent < 4) {
    sleepTime = 20;
  }
  if (4 < battPercent < 6) {
    sleepTime = 15;
  }
  if (6 < battPercent) {
    sleepTime = 10;
  }

  if (HandleISOexecute == true) {

    if (18 < hoursTm or hoursTm < 6) { //Longer sleeptime during nighttime
      sleepTime = 35;
    }

    sleepTime = sleepTime * 60; //Convert to seconds

    secondsTmDiff = (secondsTm - sleepStart); //Calculate how much time has passed since deep sleep was started by timer

    sleepTime -= (secondsTmDiff);

    sleepTime = sleepTime - (4 * 3); //compensate for delays used in following displayVal functions
    if (sleepTime < 1) { //If the variable becomes negative the program sets it to zero in order to maintain functional deep sleep
      sleepTime = 1;
    }

    serialPrintVal();

    displayVal("Temp", temp, 2, " C");
    displayVal("Humidity", humidity, 2, " %");
    displayVal("Sleep time", sleepTime, 0, " sec");
    displayVal("IO Fail", wifiAbort, 0, "");
    display.display(); //Clear display

    HandleISOexecute = false;

    deepSleep();
  }
}

//Setup (pinmode, serial, sensors detection, battery settings)
void setupCode() {

  Serial.begin(115200);

  setCpuFrequencyMhz(80);

  pinMode(BUTTON_A, INPUT_PULLUP);
  pinMode(BUTTON_B, INPUT_PULLUP);
  pinMode(BUTTON_C, INPUT_PULLUP);

  pinMode(LED_BUILTIN, OUTPUT);

  Serial.println();
  Serial.println("Power up sensors");
  Serial.println();
  blinkLED(2, 500);

  //lc.setPowerMode(LC709203F_POWER_OPERATE);

  ina219.powerSave(false); //Reactivate INA sensor

  sensorControl(); //Check if all sensors are connected

  //LC setup
  lc.setPackSize(LC709203F_APA_1000MAH);

  lc.setAlarmVoltage(3.7);
}

//Connect to IO
void connectIO() {

  Serial.println("Connecting to Adafruit IO");

  io.connect();
  blinkLED(5, 200);

  while (io.status() < AIO_NET_CONNECTED && wifiRetry < 20) {
    Serial.println(io.statusText());
    wifiRetry++;
    delay(500);
  }

  if (wifiRetry >= 20) { //couldnt connect to wifi
    wifiAbort++;
    wifiConsecutiveAbort++;
    blinkLED(2, 1000);
    if (wifiConsecutiveAbort > 3) {
      esp_sleep_enable_timer_wakeup(600 * uS_TO_S_FACTOR);
    }

    else {
      esp_sleep_enable_timer_wakeup(30 * uS_TO_S_FACTOR);
    }
    Serial.println();
    Serial.println("WiFi connection failed!");
    Serial.println("ESP going to deep sleep!");
    Serial.println();
    esp_deep_sleep_start();
  }

  // attach a message handler for the ISO feed
  iso->onMessage(handleISO);

  // wait for an MQTT connection
  while (io.mqttStatus() < AIO_CONNECTED) {
    Serial.println(io.statusText());
    delay(500);
  }

  wifiConsecutiveAbort = 0;

  Serial.println();
  Serial.println(io.statusText());
  Serial.println();
  blinkLED(3, 100);
}

//Sensor control (make sure all sensors are connected)
void sensorControl() {
  if (!lc.begin()) {
    Serial.println(F("Couldnt find Adafruit LC709203F?\nMake sure a battery is plugged in!"));
    while (1) delay(10);
  }
  Serial.println(F("Found LC709203F"));

  if (! aht.begin()) {
    Serial.println("Could not find AHT? Check wiring");
    while (1) delay(10);
  }

  Serial.println("AHT10 or AHT20 found");

  if (! ina219.begin()) {
    Serial.println("Failed to find INA219 chip");
    while (1) {
      delay(10);
    }
  }

  Serial.println("Found INA219");
}

//Print all values into serial
void serialPrintVal() {
  Serial.print("Voltage: ");
  Serial.print(voltage);
  Serial.println(" V");
  Serial.print("Current: ");
  Serial.print(averageCurrent);
  Serial.println(" mA");
  Serial.print("Battery percentage: ");
  Serial.print(battPercent);
  Serial.println(" %");
  Serial.print("Connection failures: ");
  Serial.println(wifiAbort);
  Serial.print("Temperature: ");
  Serial.print(temp);
  Serial.println(" C");
  Serial.print("Humidity: ");
  Serial.print(humidity);
  Serial.println(" %");
  Serial.print("Time to sleep is ");
  Serial.print(sleepTime);
  Serial.println(" seconds");
}

//Publish all values to IO
void groupPub() {
  group->set("AIO connect fail", wifiAbort);
  group->set("Battery percentage", battPercent);
  group->set("Voltage", voltage);
  group->set("Current", averageCurrent);
  group->set("Temperature", temp);
  group->set("Humidity", humidity);

  group->save();
}

//Display given value onto OLED
void displayVal(char* title, float value, int len, char* unitType) {
  display.setCursor(0, 11);
  display.println(title);
  display.print(value, len);
  display.print(unitType);
  display.display();
  delay (3000);
  display.clearDisplay();
}

//Collect all values
void collectValues() {
  voltage = lc.cellVoltage(), 3;
  battPercent = lc.cellPercent(), 1;
  aht.getEvent(&humidityEvent, &tempEvent);
  temp = tempEvent.temperature;
  humidity = humidityEvent.relative_humidity;

  for (int i = 0; i < 1000; i++) {
    current_mA += ina219.getCurrent_mA();
  }
  averageCurrent =  current_mA / 1000;
}

void deepSleep() {
  Serial.println();
  Serial.println("ESP going to deep sleep!");
  Serial.println();

  //lc.setPowerMode(LC709203F_POWER_SLEEP); //Shut down lc

  ina219.powerSave(true); //Shut down INA

  if (sleepTime < 1) { //Failsafe to make sure timer always work
    esp_sleep_enable_timer_wakeup(1 * uS_TO_S_FACTOR);
  }

  else {
    esp_sleep_enable_timer_wakeup(sleepTime * uS_TO_S_FACTOR);
  }

  esp_sleep_enable_ext0_wakeup(GPIO_NUM_15, 0);

  esp_sleep_enable_ext1_wakeup(BUTTON_PIN_BITMASK, ESP_EXT1_WAKEUP_ALL_LOW);

  esp_deep_sleep_start();
}

void setup() {
  setupCode();

  connectIO();
}

void loop() {

  collectValues();

  wakeup_reason = esp_sleep_get_wakeup_cause();
  switch (wakeup_reason)
  {
    case 2:
      Serial.println();
      Serial.println("Wakeup caused by external signal using RTC_IO (EXT0)");
      Serial.println();

      // attach message handler for the seconds feed
      seconds->onMessage(handleSecsExt0);

      display.begin(SSD1306_SWITCHCAPVCC, 0x3C); // Address 0x3C for 128x32
      display.clearDisplay();
      display.setFont(&FreeMono9pt7b);
      display.setTextSize(1);
      display.setTextColor(SSD1306_WHITE);

      io.run();

      break;

    case 3:

      Serial.println();
      Serial.println("Wakeup caused by external signal using RTC_IO (EXT1)");
      Serial.println();

      // attach message handler for the seconds feed
      seconds->onMessage(handleSecsExt1);

      display.begin(SSD1306_SWITCHCAPVCC, 0x3C); // Address 0x3C for 128x32
      display.clearDisplay();
      
      display.setFont(&FreeMono9pt7b);
      display.setTextSize(1);
      display.setTextColor(SSD1306_WHITE);

      io.run();

      break;

    default :
      Serial.println();
      Serial.println("Wakeup caused by timer");
      Serial.println();

      // attach message handler for the seconds feed
      seconds->onMessage(handleSecsTimer);

      groupPub();

      io.run();

      break;
  }
}
