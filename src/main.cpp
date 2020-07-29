#include <Arduino.h>
#include <ESP8266WiFi.h>
#include <ESP8266WebServer.h>

const char* ssid = "o2";
const char* pass = "asdfghjkl";
ESP8266WebServer server(80);
 void handle_root()
 {
   server.send(200,"text/html","hello");
 }
 void handle_notfound()
 {

server.send(404,"text/html","jango pettu");
 }

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
  Serial.print("sucsses");
  Serial.println("gotIP");
  Serial.print(WiFi.localIP());
  server.on("/",handle_root);
  server.onNotFound(handle_notfound);
  server.begin();
  Serial.print("server started");

  
  // put your setup code here, to run once:
}

void loop() {
  server.handleClient();
  // put your main code here, to run repeatedly:
}