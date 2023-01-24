#include <ESP8266WiFi.h>
#include <ESP8266HTTPClient.h>
byte nuidPICC[4];
#define SERVER_IP "192.168.1.79"
#include <GyverOLED.h>

#ifndef STASSID

#define STASSID "ALCLB28D68D4"
#define STAPSK  "idatech@#25"
#endif
#include <SPI.h>
#include <MFRC522.h>
 //const String& payload;
 String respons1,respons100="99",connectin;
 
//int led_pin = D4;
int led2_pin = D6;
//int D0_Value = D0;
int buzzler = D8;
int raw_Value = A0;

  WiFiClient client;
    HTTPClient http;
void setup(){
  Serial.begin(9600);
//  pinMode(led_pin, OUTPUT);
  pinMode(led2_pin, OUTPUT);
  pinMode(buzzler, OUTPUT);
//  pinMode(D0_Value, INPUT); // Set pin D8 as digital output
  pinMode(raw_Value, INPUT); //Set pin A0 as an input

  /////////////////////////////////////////////////////////////
  
  Serial.begin(9600);   // Initiate a serial communication
 WiFi.begin(STASSID, STAPSK); 
    
  pinMode(A0, INPUT);
  while (WiFi.status() != WL_CONNECTED) {
    delay(50);
//    connecting="connect...";
    Serial.print(".");
//     party();
  }
   Serial.println("");
//   connecting="connected";
  Serial.print("Connected! IP address: ");
 Serial.println(WiFi.localIP());
  SPI.begin();      // Initiate  SPI bus
  
// party();
   if ((WiFi.status() == WL_CONNECTED)) {
    WiFiClient client;
    HTTPClient http;
    }
  
}

void loop(){
//  int val_digital = digitalRead(D0_Value);
  int val_analog = analogRead(raw_Value );
  Serial.println(val_analog);
  
if(val_analog < 100){
//  Serial.print(raw_Value);
Serial.println(val_analog);
digitalWrite(led2_pin, LOW);
digitalWrite(buzzler, LOW);

  delay(9000);
}else{
  digitalWrite(led2_pin, HIGH);
//digitalWrite(buzzler, HIGH);
delay(9000);
}

}
void dataTranfer() {
  int val_analog;
  
    Serial.print("[HTTP] begin...\n");
    // configure traged server and url
    http.begin(client, "http://" SERVER_IP "/api/sound"); //HTTP
    http.addHeader("Content-Type", "application/json");

    Serial.print("[HTTP] POST...\n");
   
// String httpRequestData = "{\"alcohol\":\""+val_analog+"\",\"identifier\":\"idatechiot\"}";        
int httpCode = http.POST("{\"sound\":\"+val_analog+"}");
   
Serial.println(httpRequestData);
    // httpCode will be negative on error
    if (httpCode > 0) {
     
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
