#include <ESP8266WiFi.h>
#include <ESP8266HTTPClient.h>
byte nuidPICC[4];
#define SERVER_IP "192.168.1.79"
#include <GyverOLED.h>
GyverOLED<SSH1106_128x64> oled;
#ifndef STASSID
//#define STASSID "jesus"
//#define STAPSK  "jesus12345"

#define STASSID "ALCLB28D68D4"
#define STAPSK  "idatech@#25"
#endif
#include <SPI.h>
#include <MFRC522.h>
 //const String& payload;
 String respons1,respons100="99",connecting;
 int led_pin =D8;
//int led2_pin =D1;
int mq3 = A0;
#define SS_PIN D3
#define RST_PIN D4
MFRC522 mfrc522(SS_PIN, RST_PIN);   // Create MFRC522 instance.
 String mycard;
 String mycard2;
 int val_analog;
 int sensorValue;
  WiFiClient client;
    HTTPClient http;
void setup() 
{
  Serial.begin(9600);   // Initiate a serial communication
 WiFi.begin(STASSID, STAPSK);
 oled.init();   
    
  pinMode(A0, INPUT);
  while (WiFi.status() != WL_CONNECTED) {
    delay(50);
    connecting="connect...";
    Serial.print(".");
     party();
  }
   Serial.println("");
   connecting="connected";
  Serial.print("Connected! IP address: ");
 Serial.println(WiFi.localIP());
  SPI.begin();      // Initiate  SPI bus
  mfrc522.PCD_Init();   // Initiate MFRC522
  Serial.println("Approximate your card to the reader...");
  Serial.println();
 party();
   if ((WiFi.status() == WL_CONNECTED)) {
    WiFiClient client;
    HTTPClient http;
    }
  
}
void loop() 
{
 
 cardReaded();
 delay(1000);
} 

void dataTranfer() {
  
    Serial.print("[HTTP] begin...\n");
    // configure traged server and url
    http.begin(client, "http://" SERVER_IP "/api/"); //HTTP
    http.addHeader("Content-Type", "application/json");

    Serial.print("[HTTP] POST...\n");
    // start connection and send HTTP header and body
//    String httpRequestData = "{[ card:\""+mycard2+"\",identifier:\"idatechiot\",alcohol:"+sensorValue+"]}";   
String httpRequestData = "{\"card\":\""+mycard2+"\",\"alcohol\":\""+sensorValue+"\",\"identifier\":\"idatechiot\"}";        
int httpCode = http.POST("{\"card\":\""+mycard2+"\",\"alcohol\":\""+sensorValue+"\",\"identifier\":\"idatechiot\"}");
//http.POST("{\"card\":\""+mycard2+"\",\"alcohol\":"+sensorValue+",\"identifier\":\"idatechiot\"}");   
Serial.println(httpRequestData);
    // httpCode will be negative on error
    if (httpCode > 0) {
      // HTTP header has been send and Server response header has been handled
      Serial.printf("[HTTP] POST... code: %d\n", httpCode);

      // file found at server
      if (httpCode == HTTP_CODE_OK) {
        const String& payload = http.getString();
        Serial.println("received payload:\n<<");
        Serial.println(payload);
        Serial.println(">>");

        respons1=payload;
        respons100="1";
      }
    } else {
      respons100="880";
      Serial.printf("[HTTP] POST... failed, error: %s\n", http.errorToString(httpCode).c_str());
    }
}

void party() {
  oled.clear();
  uint32_t tmr = millis();
  oled.setScale(1);
  oled.setCursor(1, 1);
 oled.print("IDATECH LTD");
  oled.setScale(2);
  oled.setCursor(-1,3);
  oled.print("SMART CLASS");
  oled.setScale(1);
  oled.setCursor(110, 7);
  oled.print("IOT");
  
  oled.setCursor(1, 7);
  oled.print(connecting);
  oled.update();
  for (;;) {
    oled.invertDisplay(false);
    delay(200);
    if (millis() - tmr > 4000) return;
  }
}

void valueDisplayy()
{
  oled.clear();
  alcoholDetect();
  uint32_t tmr = millis();
  oled.setScale(1);
  oled.setCursor(1, 1);
  oled.print("CARD IS TAPED ");
  oled.setScale(1);
  oled.setCursor(0,3);
  oled.print("ID :");
  oled.setCursor(70,2);
  oled.print(mycard2);
  oled.setCursor(0,4);
  oled.print("===========================");
  oled.setScale(2);
  oled.setCursor(1,6);
  oled.print("HUHA HO !!!");
  oled.setCursor(60,7);
//  oled.print();
alcoholDetect();
  oled.update();
  for (;;) {

    oled.invertDisplay(false);
    delay(200);
    if (millis() - tmr > 4000) return;
  }
}

void cardReaded()
{
  // Look for new cards
  if ( ! mfrc522.PICC_IsNewCardPresent()) 
  {
    return;
  }
  // Select one of the cards
  if ( ! mfrc522.PICC_ReadCardSerial()) 
  {
    return;
  }
  //Show UID on serial monitor
  Serial.print("UID tag :");
  String content= "";
  byte letter;
  for (byte i = 0; i < mfrc522.uid.size; i++) 
  {
     Serial.print(mfrc522.uid.uidByte[i] < 0x10 ? " 0" : " ");
     Serial.print(mfrc522.uid.uidByte[i], HEX);
     content.concat(String(mfrc522.uid.uidByte[i] < 0x10 ? " 0" : " "));
     content.concat(String(mfrc522.uid.uidByte[i], HEX));
  }
  Serial.println();
  Serial.print("Message : ");
  content.toUpperCase();
  mycard=content.substring(1);
  Serial.println(mycard);
  mycard2=mycard;
  Serial.println(mycard2);
  valueDisplayy();

  dataTranfer();
   AtteeDispla();
  
}
void alcoholDetect()
{
    sensorValue = analogRead(mq3);
 
  if(sensorValue>=200){
    digitalWrite(led_pin, HIGH);
    Serial.print("this your alcohol is over 200: ");
    Serial.println(sensorValue);

  }else{
    digitalWrite(led2_pin, HIGH);
     Serial.print("this your alcohol is less than 200: ");
    Serial.println(sensorValue);

  }
}

void AtteeDispla()
{
   oled.clear();

  uint32_t tmr = millis();
  oled.setScale(2);
  oled.setCursor(1, 1);
  oled.print("TAPED CARD");
  oled.setScale(1);
  oled.setCursor(13,2);
//  oled.print("Your identity:");
   oled.setCursor(0,3);
  oled.print("_________");
  oled.setCursor(11,5);
  oled.print(respons1);
   oled.setCursor(0,6);
  oled.print("_________");
  if(respons100=="1")
  {
      oled.setCursor(1,7);
     oled.print("AlC : ");
    oled.setCursor(30,7);
//  oled.setCursor(40,);
  oled.print(sensorValue);
    oled.setCursor(90,7);
    oled.print("SUCCESS");
   
  }
  else{
  oled.setCursor(1,7);
     oled.print("AlC : ");
    oled.setCursor(30,7);
//  oled.setCursor(40,7);
  oled.print(sensorValue);
     oled.setCursor(90,7);
     oled.print("ERROR");
 
  }

  oled.update();
  for (;;) {

    oled.invertDisplay(true);
    delay(200);
    if (millis() - tmr > 5000) return;
  }
} 

void alcdisplay()
{
  alcoholDetect();
   oled.clear();
  alcoholDetect();
  uint32_t tmr = millis();
  oled.setScale(1);
  oled.setCursor(1, 1);
  oled.print("CARD IS TAPED ");
  oled.setScale(1);
  oled.setCursor(0,5);
  oled.print("Alcohol");
  
  oled.setCursor(40,5);
  oled.print(sensorValue);

  oled.update();
  for (;;) {

    oled.invertDisplay(false);
    delay(200);
    if (millis() - tmr > 4000) return;
  }

}
