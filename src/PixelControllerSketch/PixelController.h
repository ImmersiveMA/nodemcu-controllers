#ifndef PixelController_H
#define PixelController_H

#include <stdint.h>
#include <Adafruit_NeoPixel.h>

class PixelController {
private:
  Adafruit_NeoPixel strip;
  uint16_t leds;
  uint16_t pin;

  uint8_t r, g, b;
  uint32_t color;

	uint16_t firstLED, lastLED;
	uint16_t i, j, h;

	uint8_t* arr = nullptr;
	uint16_t arrSize;

  void (PixelController::*animationFunction)();

  bool delaying = false;
  unsigned long delayEnd;

  uint16_t clampLED(uint16_t LED);
  void delay(int delayTime);

  void walkInLoop();
  void walkBackLoop();

  void fadeOutLoop();
  void fadeInLoop();
  void fadeWalkLoop();

public:
  PixelController(uint16_t leds, uint16_t pin, uint8_t brightness);
  void handleAnimation();
  bool isAnimationFinished();

  void setColor(uint8_t red, uint8_t green, uint8_t blue);
  void setBrightness(uint8_t brightness);

  void walkIn(uint16_t firstLED, uint16_t lastLED, uint32_t wait);
  void walkBack(uint16_t firstLED, uint16_t lastLED, uint32_t wait);

  void fadeOut(uint16_t firstLED, uint16_t lastLED, uint32_t wait);
  void fadeIn(uint16_t firstLED, uint16_t lastLED, uint32_t wait);
  void fadeWalk(uint16_t firstLED, uint16_t lastLED, uint32_t wait);
};

#endif