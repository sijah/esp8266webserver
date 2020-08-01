#include <Arduino.h>
#include <ESP8266WiFi.h>
#include <ESP8266WebServer.h>
#include <ESP8266mDNS.h>

const char *ssid = "o2";
const char *pass = "asdfghjkl";
ESP8266WebServer server(80);
uint8_t led = D1;
bool ledstatus = LOW;

String SendHTML(uint8_t led1stat)
{
  String ptr = "<!DOCTYPE html> <html>\n";
  ptr += "<head><meta name=\"viewport\" content=\"width=device-width, initial-scale=1.0, user-scalable=no\">\n";
  ptr += "<title>LED Control</title>\n";
  ptr += "<style>\n";
  ptr += "html{font-family:arial;text-align:center;}\n";
  ptr += "h1{color:grey;margin : 50px auto 50px;}\n";
  ptr += ".button {display: block;width: 80px;background-color: #1abc9c;border: none;color: white;padding: 13px 30px;text-decoration: none;font-size: 25px;margin: 0px auto 35px;cursor: pointer;border-radius: 4px;}\n";
  ptr += ".button-on {background-color: #1abc9c;}\n";
  ptr += ".button-on:active {background-color: #16a085;}\n";
  ptr += ".button-off {background-color: #34495e;}\n";
  ptr += ".button-off:active {background-color: #2c3e50;}\n";
  ptr += "p {font-size: 14px;color: #888;margin-bottom: 10px;}\n";
  ptr += "</style>\n";
  ptr += "</head>\n";
  ptr += "<body>\n";
  ptr += "<h1>ESP8266 Web Server</h1>\n";
  if (led1stat)
  {
    ptr += "<p>LED1 Status: ON</p><a class=\"button button-off\" href=\"/ledoff\">OFF</a>\n";
  }
  else
  {
    ptr += "<p>LED1 Status: OFF</p><a class=\"button button-on\" href=\"/ledon\">ON</a>\n";
  }
  ptr += "</body>\n";
  ptr += "</html>\n";
  return ptr;
}

void handle_root()
{
  server.send(200, "text/html", SendHTML(ledstatus));
}

void led_on()
{
  digitalWrite(led, HIGH);
  ledstatus = HIGH;
  server.send(200, "text/html", SendHTML(ledstatus));
}

void led_off()
{
  ledstatus = LOW;
  digitalWrite(led, LOW);
  server.send(200, "text/html", SendHTML(ledstatus));
}

void handle_notfound()
{

  server.send(404, "text/html", "jango pettu");
}

void setup()
{
  pinMode(led, OUTPUT);
  Serial.begin(115200);
  Serial.print("connecting to ..");
  Serial.println(ssid);
  WiFi.begin(ssid, pass);
  while (WiFi.status() != WL_CONNECTED)
  {
    delay(1000);
    Serial.print(".");
  }
  if (!MDNS.begin("esp8266"))
  {
    Serial.println("Error setting up MDNS responder!");
    while (1)
    {
      delay(1000);
    }
  }
  Serial.println("mDNS responder started");

  Serial.print("sucsses");
  Serial.println("gotIP");
  Serial.print(WiFi.localIP());
  server.on("/", handle_root);
  server.on("/ledon", led_on);
  server.on("/ledoff", led_off);
  server.onNotFound(handle_notfound);
  server.begin();
  Serial.print("server started");
}

void loop()
{
  MDNS.update();
  server.handleClient();
}