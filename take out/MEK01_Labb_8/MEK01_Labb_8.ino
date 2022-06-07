int timer = 0; //Elapsed tim
int digitDisp = 0; //Digit to display
int startButton = 1;
int stopButton = 1;
int startButtonPin = 10;
int stopButtonPin = 11;

int digit[10][7] = {
  {1,1,1,1,1,1,0},//0
  {0,1,1,0,0,0,0},//1
  {1,1,0,1,1,0,1},//2
  {1,1,1,1,0,0,1},//3
  {0,1,1,0,0,1,1},//4
  {1,0,1,1,0,1,1},//5
  {1,0,1,1,1,1,1},//6
  {1,1,1,0,0,0,0},//7
  {1,1,1,1,1,1,1},//8
  {1,1,1,1,0,1,1},//9
  };
  
int pins[] = {2,3,4,5,6,7,8};

void setup() {
  Serial.begin(115200); //Begin serial
  pinMode(startButtonPin, INPUT_PULLUP);
  pinMode(stopButtonPin, INPUT_PULLUP);
  for(int i = 0; i < 7; i++){ //Assign pins
    pinMode(pins[i], OUTPUT);
  }
}

void loop() {
  startButton = digitalRead(startButtonPin);
  stopButton = digitalRead(stopButtonPin);
  for(int u = 0; u < 9; u++){
    for(int i = 0; i < 7; i++){
      digitalWrite(pins[i], digit[digitDisp][i]);
      }
    delay(500);
    for(int x = 0; x < 7; x++){
      digitalWrite(pins[x], 0);
     }
     digitDisp = millis() / 1000;
  }

}
