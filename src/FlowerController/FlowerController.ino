#include <Adafruit_NeoPixel.h>
#include <stdint.h>
#include <ESP8266WiFi.h>
#include <WiFiClient.h>
#include <ESP8266WebServer.h>
#include "Flower.h"

#define LEDS 20
#define PIN 5
#define BRIGHTNESS 255
#define DELAY 100

const char *ssid = "NodeMCU";
const char *password = "NodeMCUTesting";

ESP8266WebServer webServer{ 80 };
Flower flower{ LEDS, PIN, BRIGHTNESS };

void randomAnimation() {
  switch(random(5) + 1) {
    case 1:
      flower.walkIn(0, LEDS, DELAY);
      break;

    case 2:
      flower.walkBack(0, LEDS, DELAY);
      break;

    case 3:
      flower.fadeOut(0, LEDS, DELAY);
      break;

    case 4:
      flower.fadeIn(0, LEDS, DELAY);
      break;

    case 5:
      flower.fadeWalk(0, LEDS, DELAY);
      break;       
  }
}

void setup() {
  Serial.begin(115200);
  Serial.write('\n');

  randomSeed(analogRead(0));

  WiFi.begin(ssid, password);

  webServer.begin();

  webServer.on("/color", []() {
    flower.setColor(webServer.arg(0).toInt(), webServer.arg(1).toInt(), webServer.arg(2).toInt());

    webServer.send(200, "text/json", "{\"success\": true}");
  });

  randomAnimation();
}

void loop() {
  webServer.handleClient();

  if(flower.isAnimationFinished()) randomAnimation();

  flower.handleAnimation();

  // yield zorgt ervoor dat de background functions van de ESP8266 hun ding kunnen doen. :)
  yield();
}