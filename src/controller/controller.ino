#include <ESP8266WiFi.h>
#include <WiFiClient.h>
#include <ESP8266WebServer.h>

#define YELLOWLED D0
#define WHITELED D1
#define GREENLED D2

const char *ssid = "NodeMCU";
const char *password = "NodeMCUTesting";

ESP8266WebServer server{ 80 };

void setup() {
  pinMode(LED_BUILTIN, OUTPUT);
  pinMode(YELLOWLED, OUTPUT);
  pinMode(WHITELED, OUTPUT);
  pinMode(GREENLED, OUTPUT);
  
  WiFi.begin(ssid, password);

  server.on("/", root);
  server.on("/echo", echo);
  server.on("/lampje", lampje);
  server.begin();
}

void loop() {
  checkWifiStatus();
  server.handleClient();
}

// Just use the builtin led to check if we are still connected. Because why not? It's easy!
void checkWifiStatus() {
  if(WiFi.status() == WL_CONNECTED) digitalWrite(LED_BUILTIN, LOW);
  else digitalWrite(LED_BUILTIN, HIGH);
}

void root() {
  server.send(200, "text/plain", "hello me");
}

void echo() {
  String message = "{";
  for(int i = 0; i < server.args(); i++) message += "\"" + server.argName(i) + "\": \"" + server.arg(i) + "\", ";
  message += '}';

  server.send(200, "text/json", message);
}

void lampje(){
  String color = server.arg(0);

  digitalWrite(GREENLED, LOW);
  digitalWrite(YELLOWLED, LOW);
  digitalWrite(WHITELED, LOW);

  if(color == "green") digitalWrite(GREENLED, HIGH);
  else if(color == "yellow") digitalWrite(YELLOWLED, HIGH);
  else if(color == "white") digitalWrite(WHITELED, HIGH);


  server.send(200, "text/json", "{\"success\":true, \"color\": "+ color + "}");
}

void blink(const unsigned char led) {
  digitalWrite(led, HIGH);
  delay(100);
  digitalWrite(led, LOW);
}
