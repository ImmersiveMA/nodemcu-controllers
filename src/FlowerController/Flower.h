#ifndef FLOWER_H
#define FLOWER_H

#include <stdint.h>
#include <Adafruit_NeoPixel.h>

class Flower {
private:
  Adafruit_NeoPixel strip;
  uint16_t leds;
  uint16_t pin;

  // Deze functie zorgt ervoor dat een led integer nooit hoger is dan het aantal leds dat we hebben.
  // Wordt alleen intern gebruikt dus dw about the naming. (●'◡'●)
  uint16_t clampLED(uint16_t LED);

public:
  Flower(uint16_t leds, uint16_t pin, uint8_t brightness);

  void setColor(uint16_t firstLED, uint16_t lastLED, uint8_t red, uint8_t green, uint8_t blue);
  void setBrightness(uint8_t brightness);

  // 1 voor 1 AAN. (geen fade)
  void walkIn(uint16_t firstLED, uint16_t lastLED, uint8_t red, uint8_t green, uint8_t blue, uint32_t wait = 100);
  void walkBack(uint16_t firstLED, uint16_t lastLED, uint8_t red, uint8_t green, uint8_t blue, uint32_t wait = 100);

  void fadeOut(uint16_t firstLED, uint16_t lastLED, uint8_t red, uint8_t green, uint8_t blue, uint32_t wait = 100);
  void fadeIn(uint16_t firstLED, uint16_t lastLED, uint8_t red, uint8_t green, uint8_t blue, uint32_t wait = 100);
  void fadeWalk(uint16_t firstLED, uint16_t lastLED, uint8_t red, uint8_t green, uint8_t blue, uint32_t wait = 100);
}

#endif