#include <Adafruit_NeoPixel.h>
#include <stdint.h>
#include <ESP8266WiFi.h>
#include <WiFiClient.h>
#include <ESP8266WebServer.h>
#include "PixelController.h"

#define LEDS 14
#define PIN D1
#define BRIGHTNESS 255
#define DELAY 50

const char *ssid = "NodeMCU";
const char *password = "NodeMCUTesting";

ESP8266WebServer webServer{ 80 };
PixelController controller{ LEDS, PIN, BRIGHTNESS };

void setup() {
  Serial.begin(115200);
  Serial.write('\n');

  pinMode(PIN, OUTPUT);

  randomSeed(analogRead(1));

  WiFi.begin(ssid, password);


  webServer.begin();

  webServer.on("/color", []() {
    controller.setColor(webServer.arg(0).toInt(), webServer.arg(1).toInt(), webServer.arg(2).toInt());
    webServer.send(200, "text/json", "{\"success\": true}");
  });

  controller.solid(0, LEDS);
}

void loop() {

  webServer.handleClient();

  controller.handleAnimation();

  // yield zorgt ervoor dat de background functions van de ESP8266 hun ding kunnen doen. :)
  yield();
}