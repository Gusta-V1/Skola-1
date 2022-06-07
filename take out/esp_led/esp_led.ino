void blinkLED(int times, int interval) { //Times = times led turns on/off, speed = time between blinks in ms
  for (int i = 0; i < times; i++) {
    digitalWrite(LED_BUILTIN, 1);
    delay(interval);
    digitalWrite(LED_BUILTIN, 0);
    delay(interval);
  }
}

void setup() {
  Serial.begin(115200);
  digitalWrite(LED_BUILTIN, HIGH);
}

void loop() {
  // put your main code here, to run repeatedly:

}
