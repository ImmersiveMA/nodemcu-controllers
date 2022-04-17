#include "Flower.h"

Flower::Flower(uint16_t leds, uint16_t pin, uint8_t brightness) {
  this.leds = leds;
  this.pin = pin;
  
  strip = Adafruit_NeoPixel(leds, pin, NEO_RGB + NEO_KHZ800);
  strip.setBrightness(brightness);
  strip.begin();
  strip.show();
}

// Normaal gesproken zou je een error throwen als een led argument out of range is, maar dit is een ez fix. =￣ω￣=
uint16_t Flower::clampLED(uint16_t LED) {
  if(LED > leds - 1) return leds - 1;
  return LED;
}

void Flower::setColor(uint16_t firstLED, uint16_t lastLED, uint8_t red, uint8_t green, uint8_t blue) {
  lastLED = clampLED(lastLED);

  strip.fill(strip.Color(r, g, b), firstLED, lastLED - firstLED);
}

// Dit ziet er zo dom uit maar het is simpel en het werkt, so don't judge. ╰（‵□′）╯
void Flower::setBrightness(uint8_t brightness) {
  strip.setBrightness(brightness);
}

void Flower::walkIn(uint16_t firstLED, uint16_t lastLED, uint8_t red, uint8_t green, uint8_t blue, uint32_t wait = 100) {
  lastLED = clampLED(lastLED);

  uint32_t color = strip.Color(r, g, b);

  for(int i = firstLED; i <= lastLED; i++) {
    strip.setPixelColor(i, color);
    strip.show();
    delay(wait);
  }
}

void Flower::walkOut(uint16_t firstLED, uint16_t lastLED, uint8_t red, uint8_t green, uint8_t blue, uint32_t wait = 100) {
  lastLED = clampLED(lastLED);

  uint32_t color = strip.Color(r, g, b);

  for(int i = lastLED; i >= firstLED; i--) {
    strip.setPixelColor(i, color);
    strip.show();
    delay(wait);
  }
}

void Flower::fadeOut(uint16_t firstLED, uint16_t lastLED, uint8_t red, uint8_t green, uint8_t blue, uint32_t wait = 100) {
  lastLED = clampLED(lastLED);

  for(int i = 100; i >= 0; i -= 10) {
    strip.fill(strip.Color((r / 100.00 * i), (g / 100.00 * i), (b / 100.00 * i)), firstLED, lastLED - firstLED);
  }
}

void Flower::fadeIn(uint16_t firstLED, uint16_t lastLED, uint8_t red, uint8_t green, uint8_t blue, uint32_t wait = 100) {
  lastLED = clampLED(lastLED);

  for(int i = 0; i <= 100; i += 10) {
    strip.fill(strip.Color((r / 100.00 * i), (g / 100.00 * i), (b / 100.00 * i)), firstLED, lastLED - firstLED);
  }
}

void Flower::fadeWalk(uint16_t firstLED, uint16_t lastLED, uint8_t red, uint8_t green, uint8_t blue, uint32_t wait = 100) {
  lastLED = clampLED(lastLED);

  uint16_t size = lastLED - firstLED;
  uint8_t* brightnessArray = new uint8_t[size] { size * 0};
  uint16_t i = 0;

  while(brightnessArray[size - 1] != 100) {
    for(uint16_t j = 0; j <= i; j++) {
      if(brightnessArray[j] == 100) continue;

      brightnessArray[j] += 10;

      // firstLED is basically de offset, als we in de midden van de LEDs beginnen weet de array dat niet. ╯︿╰
      strip.setPixelColor(j + firstLED, strip.Color((r / 100.00 * brightnessArray[j]), (g / 100.00 * brightnessArray[j]), (b / 100.00 * brightnessArray[j])));
    }

    if (i < size - 1) i++;
    strip.show();
    delay(wait);
  }

  delete[] brightnessArray;
}




