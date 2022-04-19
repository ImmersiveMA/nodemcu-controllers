#include "Flower.h"

Flower::Flower(uint16_t leds, uint16_t pin, uint8_t brightness) {
  this->leds = leds;
  this->pin = pin;
  
  strip = Adafruit_NeoPixel(leds, pin, NEO_RGB + NEO_KHZ800);
  strip.setBrightness(brightness);
  strip.begin();
  strip.show();
}

void Flower::handleAnimation() {
  if(this->animationFunction == nullptr) return;

  if(delaying) {
    if(delayEnd < millis()) {
      delaying = false;
    }
    return;
  }

  (this->*animationFunction)();
}

bool Flower::isAnimationFinished() {
  if(this->animationFunction == nullptr) return true;
  return false;
}

void Flower::delay(int delayTime) {
  this->delaying = true;
  this->delayEnd = millis() + delayTime;
}

// Normaal gesproken zou je een error throwen als een led argument out of range is, maar dit is een ez fix. =￣ω￣=
uint16_t Flower::clampLED(uint16_t LED) {
  if(LED > leds - 1) return leds - 1;
  return LED;
}

void Flower::setColor(uint8_t red, uint8_t green, uint8_t blue) {
  this->r = red;
  this->g = green;
  this->b = blue;

  this->color = strip.Color(red, green, blue);
}

// Dit ziet er zo dom uit maar het is simpel en het werkt, so don't judge. ╰（‵□′）╯
void Flower::setBrightness(uint8_t brightness) {
  this->strip.setBrightness(brightness);
}

void Flower::walkIn(uint16_t firstLED, uint16_t lastLED, uint32_t wait) {
  this->lastLED = clampLED(lastLED);
  this->i = firstLED;
  this->j = wait;

  this->animationFunction = &Flower::walkInLoop;
}

void Flower::walkInLoop() {
  this->strip.setPixelColor(this->i, this->color);
  this->strip.show();

  if(this->i == this->lastLED) {
    Serial.print(3);
    this->animationFunction = nullptr;
    return;
  }

  this->i++;
  this->delay(this->j);
}

void Flower::walkBack(uint16_t firstLED, uint16_t lastLED, uint32_t wait) {
  this->firstLED = firstLED;
  this->i = clampLED(lastLED);
  this->j = wait;

  this->animationFunction = &Flower::walkBackLoop;
}

void Flower::walkBackLoop() {
  this->strip.setPixelColor(this->i, this->color);
  this->strip.show();

  if(this->i == this->firstLED) {
    this->animationFunction = nullptr;
    return;
  }

  this->i--;
  this->delay(this->j);
}

void Flower::fadeOut(uint16_t firstLED, uint16_t lastLED, uint32_t wait) {
  this->lastLED = clampLED(lastLED);
  this->firstLED = firstLED;
  this->i = 100;
  this->j = wait;

  this->animationFunction = &Flower::fadeOutLoop;
}

void Flower::fadeOutLoop() {
  this->strip.fill(this->strip.Color((this->r / 100.00 * this->i), (this->g / 100.00 * this->i), (this->b / 100.00 * this->i)), this->firstLED, this->lastLED - this->firstLED);

  if(this->i == 0) {
    this->animationFunction = nullptr;
    return;
  }

  this->i -= 10;
  this->delay(this->j);
}

void Flower::fadeIn(uint16_t firstLED, uint16_t lastLED, uint32_t wait) {
  this->lastLED = clampLED(lastLED);
  this->firstLED = firstLED;
  this->i = 0;
  this->j = wait;

  this->animationFunction = &Flower::fadeInLoop;
}

void Flower::fadeInLoop() {
  this->strip.fill(this->strip.Color((this->r / 100.00 * this->i), (this->g / 100.00 * this->i), (this->b / 100.00 * this->i)), this->firstLED, this->lastLED - this->firstLED);

  if(this->i == 100) {
    this->animationFunction = nullptr;
    return;
  }

  this->i += 10;
  this->delay(this->j);
}

void Flower::fadeWalk(uint16_t firstLED, uint16_t lastLED, uint32_t wait) {
  this->firstLED = firstLED;

  this->arrSize = clampLED(lastLED) - firstLED;
  this->arr = new uint8_t[arrSize] { arrSize * 0 };
  this->i = 0;
  this->j = 0;
  this->h = wait;

  this->animationFunction = &Flower::fadeWalkLoop;
}

void Flower::fadeWalkLoop() {
  if(this->arr[this->j] != 100) {
    this->arr[this->j] += 10;
    this->strip.setPixelColor(this->j + this->firstLED, this->strip.Color((this->r / 100.00 * this->arr[this->j]), (this->g / 100.00 * this->arr[this->j]), (this->b / 100.00 * this->arr[this->j])));
  }

  if(this->arr[this->arrSize - 1] == 100) {
    this->animationFunction = nullptr;

    delete[] this->arr;
    this->arr = nullptr;

    return;
  }

  if(this->j == this->i) {
    if(this->i < this->arrSize - 1) this->i++;
    this->j = 0;
  } else this->j++;

  this->strip.show();
  this->delay(this->h);
}


