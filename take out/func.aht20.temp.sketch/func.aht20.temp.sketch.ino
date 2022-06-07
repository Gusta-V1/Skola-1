// Demo for getting individual unified sensor data from the AHT Humidity and Temperature sensor

#include <Adafruit_AHTX0.h>


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

void setup(void) {
  Serial.begin(115200);
}

void loop() {
  Serial.println(getTemp());

}
