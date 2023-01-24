#include <ESP8266WiFi.h>
#include <ESP8266HTTPClient.h>
#include <WiFiClient.h>
//
//const char* ssid = "ALCLB28D68D4";
//const char* password = "idatech@#25";


const char* ssid = "CANALBOX68D4";
const char* password = "idatech@#25";
int raw_Value = A0;
int led1 = D7;
int buzzel= D8;


//Your Domain name with URL path or IP address with path
const char* serverName = "http://192.168.1.125/api/noise/";

// the following variables are unsigned longs because the time, measured in
// milliseconds, will quickly become a bigger number than can be stored in an int.
unsigned long lastTime = 0;
// Timer set to 10 minutes (600000)
//unsigned long timerDelay = 600000;
// Set timer to 5 seconds (5000)
unsigned long timerDelay = 5000;

void setup() {
  Serial.begin(9600);


  pinMode(raw_Value, INPUT);   // sound sensor
  pinMode(led1, OUTPUT);
  pinMode(buzzel, OUTPUT);

  WiFi.begin(ssid, password);
  Serial.println("Connecting");
  while(WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  Serial.println("");
  Serial.print("Connected to WiFi network with IP Address: ");
  Serial.println(WiFi.localIP());

  Serial.println("Timer set to 5 seconds (timerDelay variable), it will take 5 seconds before publishing the first reading.");


}

void loop() {
  //Send an HTTP POST request every 10 minutes
  if ((millis() - lastTime) > timerDelay) {
    //Check WiFi connection status
    if(WiFi.status()== WL_CONNECTED){
      WiFiClient client;
      HTTPClient http;

      // Your Domain name with URL path or IP address with path
      http.begin(client, serverName);


int my_data = analogRead(A0);
int my_max = my_data;
int my_min = my_data;
int my_avg = my_data;
for (int num=1; num <= 60; num ++){
  my_data = analogRead(A0);
  if (my_data == 1024){
    my_data = my_min;
  }

  if(my_data < my_min){
    my_min = my_data;
  }
  if (my_data > my_max){
    my_max = my_data;
  }
  my_avg = my_avg + my_data;
  Serial.println(" ");
  Serial.print(num);
  Serial.print(": ");
  Serial.print(my_data);
  delay(1000);

}
Serial.println(" ");
Serial.print("Data: Min: ");
Serial.print(my_min);
Serial.print(" Max: ");
Serial.print(my_max);
Serial.print(" Avg: ");
Serial.print(my_avg/60);

if(my_max>100){
  Serial.print(led1, HIGH);
  Serial.print(led1, HIGH);
}



http.addHeader("Content-Type", "application/json");


  String max_val = String(my_max);
  String min_val = String(my_min);
  String avg_val = String(my_avg/60);
  String httpRequestData = "{\"identifier\":\"idatechiot\",\"max\":\""+max_val+"\",\"min\":\""+min_val+"\",\"avg\":\""+avg_val+"\"}";

//    String httpRequestData = "{\"card\":\""+mycard2+"\",\"alcohol\":\""+sensorValue+"\",\"identifier\":\"idatechiot\"}";
    Serial.println(httpRequestData);

      // Send HTTP POST request
      int httpResponseCode = http.POST(httpRequestData);

      // If you need an HTTP request with a content

      Serial.print("HTTP Response code: ");
      Serial.println(httpResponseCode);

      // Free resources
      http.end();
    }
    else {
      Serial.println("WiFi Disconnected");
    }
    lastTime = millis();
  }
}
