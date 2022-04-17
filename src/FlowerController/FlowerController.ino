#include <Adafruit_NeoPixel.h>
#include <stdint.h>
#include "Flower.h"

void setup() {
  Serial.begin(115200);
  Serial.print("test\n\r");
}

void loop() {
  Serial.print("test but looped\n\r");
}