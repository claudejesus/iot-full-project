#include <GyverOLED.h>
GyverOLED<SSH1106_128x64> oled;
void setup() {
  Serial.begin(9600);
  oled.init();   
    party();

  delay(2000);
}

void loop() 
{

  valueDisplayy();
  
}
void party() {
  oled.clear();
  uint32_t tmr = millis();
  oled.setScale(1);
  oled.setCursor(1, 1);
 oled.print("IDATECH LTD");
  oled.setScale(2);
  oled.setCursor(0,3);
  oled.print("SMART CLASS");
  oled.setScale(1);
  oled.setCursor(110, 7);
  oled.print("IOT");
  oled.update();
  for (;;) {
    oled.invertDisplay(false);
    delay(200);
    if (millis() - tmr > 5000) return;
  }
}

void valueDisplayy() {
  oled.clear();
  uint32_t tmr = millis();
  oled.setScale(1);
  oled.setCursor(1, 1);
    oled.print("IDATECH LTD");
   oled.setScale(1);
  oled.setCursor(0,3);
  oled.print("Alcohol :");
   oled.setCursor(70,3);
   oled.print("93 db");
     oled.setCursor(0,5);
  oled.print("Noise :");
   oled.setCursor(70,5);
  oled.print("93 db");
oled.setCursor(1,7);
    oled.print("S Card :");
   oled.setCursor(80,7);
   oled.print("9543");
  oled.update();
  for (;;) {
    //oled.invertDisplay(true);
//delay(200);
    oled.invertDisplay(false);
    delay(200);
    if (millis() - tmr > 5000) return;
  }
}
