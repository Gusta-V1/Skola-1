#include "config.h"

// analog pin 0
#define VBATTPIN A13

float voltage = 0;

// set up the 'analog' feed
AdafruitIO_Feed *analog = io.feed("analog");

void setup() {

  // start the serial connection
  Serial.begin(115200);

  // wait for serial monitor to open
  while(! Serial);

  // connect to io.adafruit.com
  Serial.print("Connecting to Adafruit IO");
  io.connect();

  // wait for a connection
  while(io.status() < AIO_CONNECTED) {
    Serial.println(io.statusText());
    delay(500);
  }
  // we are connected
  Serial.println(io.statusText());
}

void loop() {

  // io.run(); is required for all sketches.
  // it should always be present at the top of your loop
  // function. it keeps the client connected to
  // io.adafruit.com, and processes any incoming data.
  io.run();

  voltage = analogRead(VBATTPIN);
  voltage = voltage*3.3*2.0*1.1/4095.0;

  // save the current state to the analog feed
  Serial.print("sending -> ");
  Serial.println(voltage);
  analog->save(voltage);

  // wait three seconds (1000 milliseconds == 1 second)
  //
  // because there are no active subscriptions, we can use delay()
  // instead of tracking millis()
  delay(5000);
}
