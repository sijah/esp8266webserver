#include <Arduino.h>
#include <ESP8266WiFi.h>
#include <ESP8266WebServer.h>

const char* ssid = "o2";
const char* pass = "asdfghjkl";

void setup() {
  Serial.begin(115200);
  Serial.print("connecting to ..");
  Serial.println(ssid);
  WiFi.begin(ssid,pass);
  while (WiFi.status() != WL_CONNECTED)
  {
    delay(1000);
    Serial.print(".");
  }
  
  // put your setup code here, to run once:
}

void loop() {
  // put your main code here, to run repeatedly:
}