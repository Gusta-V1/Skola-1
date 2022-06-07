// Adafruit IO Group Publish Example
//
// Adafruit invests time and resources providing this open source code.
// Please support Adafruit and open source hardware by purchasing
//
// Written by Todd Treece for Adafruit Industries
// Copyright (c) 2016 Adafruit Industries
// Licensed under the MIT license.
//
// All text above must be included in any redistribution.

/************************** Configuration ***********************************/

// edit the config.h tab and enter your Adafruit IO credentials
// and any additional configuration needed for WiFi, cellular,
// or ethernet clients.
#include "config.h"
#include "Adafruit_LC709203F.h"
#include <Adafruit_AHTX0.h>

Adafruit_LC709203F lc;
Adafruit_AHTX0 aht;

Adafruit_Sensor *aht_humidity, *aht_temp;

// set up the group
AdafruitIO_Group *group = io.group("volt.temp");

int voltage = 0;
int temp = 0;

void setup() {

  // start the serial connection
  Serial.begin(115200);

  // wait for serial monitor to open
  while(! Serial);

  // connect to io.adafruit.com
  Serial.print("Connecting to Adafruit IO");
  io.connect();

  // we are connected
  Serial.println();
  Serial.println(io.statusText());

//----LC graj----
  if (!lc.begin()) {
    Serial.println(F("Couldnt find Adafruit LC709203F?\nMake sure a battery is plugged in!"));
    while (1) delay(10);
  }
  Serial.println(F("Found LC709203F"));
  Serial.print("Version: 0x"); Serial.println(lc.getICversion(), HEX);

  lc.setThermistorB(3950);
  Serial.print("Thermistor B = "); Serial.println(lc.getThermistorB());

  lc.setPackSize(LC709203F_APA_500MAH);

  lc.setAlarmVoltage(3.8);

//----AHT20----
  if (!aht.begin()) {
    Serial.println("Failed to find AHT10/AHT20 chip");
    while (1) {
      delay(10);
    }
  }
  Serial.println("AHT10/AHT20 Found!");
  aht_temp = aht.getTemperatureSensor();
  aht_temp->printSensorDetails();

  aht_humidity = aht.getHumiditySensor();
  aht_humidity->printSensorDetails();
}

void loop() {

  // io.run(); is required for all sketches.
  // it should always be present at the top of your loop
  // function. it keeps the client connected to
  // io.adafruit.com, and processes any incoming data.
  io.run();

//---AHT20---
  sensors_event_t humidity;
  sensors_event_t temp;
  aht_humidity->getEvent(&humidity);
  aht_temp->getEvent(&temp);

//Group
  group->set("voltage", voltage);
  group->set("temp", temp);
  group->save();

  Serial.print("sending voltage -> ");
  Serial.println(voltage);
  Serial.print("sending temp -> ");
  Serial.println(temp);

  // increment the count_1 by 1
  voltage += 1;
  // increment the count_2 by 2
  temp += 2;

  // wait four seconds (1000 milliseconds == 1 second)
  delay(4000);

//----LC fg prints----
  Serial.print("Batt Voltage: "); Serial.println(lc.cellVoltage(), 3);
  Serial.print("Batt Percent: "); Serial.println(lc.cellPercent(), 1);
  Serial.print("Batt Temp: "); Serial.println(lc.getCellTemperature(), 1);

//Assigning variables
  voltage = lc.cellVoltage();
  temp = lc.getCellTemperature();

  delay(2000);  // dont query too often!
}
