#include <SPI.h>
#include "Adafruit_GFX.h"
#include "Adafruit_HX8357.h"
#include <Fonts/FreeSans12pt7b.h>
#include <Adafruit_STMPE610.h>

//Variables
int pageSelect = 1; //Current selected page

// Color definitions "Shortcuts"
#define BLACK    0x0000
#define BLUE     0x001F
#define RED      0xF800
#define GREEN    0x07E0
#define CYAN     0x07FF
#define MAGENTA  0xF81F
#define YELLOW   0xFFE0 
#define WHITE    0xFFFF

#ifdef ESP8266
   #define STMPE_CS 16
   #define TFT_CS   0
   #define TFT_DC   15
   #define SD_CS    2
#elif defined(ESP32) && !defined(ARDUINO_ADAFRUIT_FEATHER_ESP32S2)
   #define STMPE_CS 32
   #define TFT_CS   15
   #define TFT_DC   33
   #define SD_CS    14
#elif defined(TEENSYDUINO)
   #define TFT_DC   10
   #define TFT_CS   4
   #define STMPE_CS 3
   #define SD_CS    8
#elif defined(ARDUINO_STM32_FEATHER)
   #define TFT_DC   PB4
   #define TFT_CS   PA15
   #define STMPE_CS PC7
   #define SD_CS    PC5
#elif defined(ARDUINO_NRF52832_FEATHER)  /* BSP 0.6.5 and higher! */
   #define TFT_DC   11
   #define TFT_CS   31
   #define STMPE_CS 30
   #define SD_CS    27
#elif defined(ARDUINO_MAX32620FTHR) || defined(ARDUINO_MAX32630FTHR)
   #define TFT_DC   P5_4
   #define TFT_CS   P5_3
   #define STMPE_CS P3_3
   #define SD_CS    P3_2
#else
    // Anything else, defaults!
   #define STMPE_CS 6
   #define TFT_CS   9
   #define TFT_DC   10
   #define SD_CS    5
#endif

#define TFT_RST -1

// Init screen on hardware SPI, HX8357D type:
Adafruit_HX8357 tft = Adafruit_HX8357(TFT_CS, TFT_DC, TFT_RST);
Adafruit_STMPE610 ts = Adafruit_STMPE610(STMPE_CS);

#define TS_MINX 3800
#define TS_MAXX 100
#define TS_MINY 100
#define TS_MAXY 3750

void page1(){
  // PAGE 1/2
  pageSelect = 1;
  
  //Initialize grid
  tft.fillScreen(GREEN);
  tft.setRotation(3);
  //Horizontal lines
  tft.drawFastHLine(0,160,480,BLACK);
  tft.drawFastHLine(0,240,240,BLACK);
  //Vertical lines
  tft.drawFastVLine(240,160,160,BLACK);

  //Text
  tft.setFont(&FreeSans12pt7b);
  tft.setTextColor(BLACK);
  tft.setCursor(30,125);
  tft.setTextSize(5);
  tft.print("AoA: "); tft.print("func");

  tft.setCursor(30,215);
  tft.setTextSize(2);
  tft.print("GS: "); tft.print("func");

  tft.setCursor(30,295);
  tft.setTextSize(2);
  tft.print("1/2");

  tft.setRotation(1);
  }

void page2(){
  //Page 2/2
  pageSelect = 2;

  tft.fillScreen(CYAN);
  tft.setRotation(3);
  tft.setTextColor(BLACK);
  tft.setTextSize(2);
  tft.setFont(&FreeSans12pt7b);

  //Horizontal lines
  tft.drawFastHLine(0,80,480,BLACK);
  tft.drawFastHLine(0,160,480,BLACK);
  tft.drawFastHLine(0,240,480,BLACK);

  //Vertical lines
  tft.drawFastVLine(240,0,320,BLACK);

  //Text
  tft.setCursor(15,60);
  tft.print("AoA: "); tft.print("func");
  tft.setCursor(15,140);
  tft.print("GS: "); tft.print("func");
  tft.setCursor(15,220);
  tft.print("Sat: "); tft.print("func");
  tft.setCursor(15,290);
  tft.print("2/2");
  
  tft.setCursor(255,60);
  tft.print("Pitch: "); tft.print("func");
  tft.setCursor(255,140);
  tft.print("Vane: "); tft.print("func");
  tft.setCursor(255,220);
  tft.print("Fix: "); tft.print("func");
  tft.setCursor(255,290);
  tft.print("Normal: "); tft.print("func");

  tft.setRotation(1);
  }

void setup() {
  Serial.begin(115200); 
  if (!ts.begin()) {
    Serial.println("Couldn't start touchscreen controller");
    while (1);}
  tft.begin();
  page1();
/*
  // read diagnostics (optional but can help debug problems)
  uint8_t x = tft.readcommand8(HX8357_RDPOWMODE);
  Serial.print("Display Power Mode: 0x"); Serial.println(x, HEX);
  x = tft.readcommand8(HX8357_RDMADCTL);
  Serial.print("MADCTL Mode: 0x"); Serial.println(x, HEX);
  x = tft.readcommand8(HX8357_RDCOLMOD);
  Serial.print("Pixel Format: 0x"); Serial.println(x, HEX);
  x = tft.readcommand8(HX8357_RDDIM);
  Serial.print("Image Format: 0x"); Serial.println(x, HEX);
  x = tft.readcommand8(HX8357_RDDSDR);
  Serial.print("Self Diagnostic: 0x"); Serial.println(x, HEX); 
  Serial.println(F("Benchmark                Time (microseconds)"));
*/
  }
  
void loop(void){
  // Retrieve a point  
  TS_Point p = ts.getPoint();

  // Scale from ~0->4000 to tft.width using the calibration #'s
  p.x = map(p.x, TS_MINX, TS_MAXX, tft.width(), 0);
  p.y = map(p.y, TS_MINY, TS_MAXY, 0, tft.height());
  Serial.print("X = "); Serial.print(p.x); Serial.print("\tY = "); Serial.print(p.y);  Serial.print("\tPressure = "); Serial.println(p.z); 

  if(p.x < 480 && p.x > 360 && p.y < 320 && p.y > 160){//Switch between pages
    if(pageSelect == 1){
      page2();
      }
      else{
        page1();
        }
    }
    delay(1000); //For easier press

    if(pageSelect == 1){
      page1();
      }
     else{
       page2();
       }
  }
