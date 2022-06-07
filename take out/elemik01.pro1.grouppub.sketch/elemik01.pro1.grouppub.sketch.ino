#include "config.h"

/************************ Example Starts Here *******************************/

// set up the group
AdafruitIO_Group *group = io.group("volt.temp");

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
    Serial.print(".");
    delay(500);
  }

  // we are connected
  Serial.println();
  Serial.println(io.statusText());

}

void loop() {

  // io.run(); is required for all sketches.
  // it should always be present at the top of your loop
  // function. it keeps the client connected to
  // io.adafruit.com, and processes any incoming data.
  io.run();

  group->set("voltage", getVolt());
  group->set("battery-%", getBatP());
  group->set("temp", getTemp());
  group->set("hum", getHum());
  group->save();

  Serial.print("sending example.count-1 -> ");
  Serial.println(count_1);
  Serial.print("sending example.count-2 -> ");
  Serial.println(count_2);

  // wait four seconds (1000 milliseconds == 1 second)
  delay(4000);
}
