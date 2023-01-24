#include <ESP8266WiFi.h>
//#define WLAN_SSID "jesus"
//#define WLAN_PASS "jesus12345"

#define WLAN_SSID "ALCLB28D68D4"
#define WLAN_PASS  "idatech@#25"

WiFiClient client;

//const char* host = "elder.hss.rw";
const char* host =" 192.168.1.68";

int led2_pin = D6;
//int D0_Value = D0;
int buzzler = D8;
int raw_Value = A0;

void setup() {
  
  Serial.begin(9600);
    pinMode(led2_pin, OUTPUT);
  pinMode(buzzler, OUTPUT);
//  pinMode(D0_Value, INPUT); // Set pin D8 as digital output
  pinMode(raw_Value, INPUT); 
  
  Serial.print("Connecting to ");
  Serial.println(WLAN_SSID);
  WiFi.begin(WLAN_SSID, WLAN_PASS);
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  Serial.println();

  Serial.println("WiFi connected");
  Serial.println("IP address: ");
  Serial.println(WiFi.localIP());

}

void calculateSound()
{
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
void loop()
{ 
//  delay(2000);
// 
//  displaySound();
 
//  }
//  void displaySound()
//   {
//    calculateSound();
//   Serial.print("Connecting to ");
//   Serial.println( host);
//   const int httpPort = 80;
//   if(!client.connect(host, httpPort)){
//     Serial.println("connection Failed");
//     return;
//   }
//
//String url = "api/idatechiot/sound/:+val_analog+";
//  url += "eng=";
//  url += "";
//   Serial.print("Requesting URL :");
//  Serial.println(url);
// 
//
//  //code for insertion of data
//client.print(String("GET /") + url + "HTTP/1.0 \r\n" +
//               "HOST :" + host + "\r\n" +
//               "Connection: close \r\n\r\n");
//               
//unsigned long timeout =millis();            
//  while(client.available() == 0){
//     if(millis() - timeout > 5000){
//      Serial.println(">>>Client Timeout");
//      client.stop();
//      return;
//      }
//
//  while(client.available())
//  {
//     String line = client.readStringUntil('\r');
//     Serial.print(line);
//  }
//  Serial.println();
//  Serial.println("Closing Connection");
// delay(5000);
//  }
//    delay(3000); //3000 = 3 seconds
//  Serial.println();
int sum=00;

 for( int i=0; i<=60; i++){
  Serial.println(raw_Value);
  sum=(raw_Value+raw_Value);
  max_val=sum/10;
  delay(1000);
 }
 Serial.println(max_val);
 }
}
