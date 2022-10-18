#include "RGB_LED.h"

/*uint8_t halfSineValues[] = {0,  16,  33,  49,  65,  80,  96, 111, 125, 139, 153, 165, 177,
                            189, 199, 209, 218, 226, 233, 239, 244, 249, 252, 254, 255, 255,
                            254, 252, 249, 244, 239, 233, 226, 218, 209, 199, 189, 177, 165,
                            153, 139, 125, 111,  96,  80,  65,  49,  33,  16,   0
                           };*/
uint8_t halfSineValues[] = {0,   8,  16,  24,  32,  40,  48,  56,  63,  71,  79,  86,  94,
       101, 109, 116, 123, 130, 137, 143, 150, 156, 163, 169, 175, 180,
       186, 191, 196, 201, 206, 211, 215, 219, 223, 227, 231, 234, 237,
       240, 243, 245, 247, 249, 250, 252, 253, 254, 254, 255, 255, 255,
       254, 254, 253, 252, 250, 249, 247, 245, 243, 240, 237, 234, 231,
       227, 223, 219, 215, 211, 206, 201, 196, 191, 186, 180, 175, 169,
       163, 156, 150, 143, 137, 130, 123, 116, 109, 101,  94,  86,  79,
        71,  63,  56,  48,  40,  32,  24,  16,   8};

RGBled::RGBled(uint8_t rPin, uint8_t gPin, uint8_t bPin) {
  this->rPin = rPin;
  this->gPin = gPin;
  this->bPin = bPin;
  pinMode(this->rPin, OUTPUT);
  pinMode(this->gPin, OUTPUT);
  pinMode(this->bPin, OUTPUT);
  this->off();
  this->setBrightness(255);
  this->setColorRGB(255, 255, 255);
  this->doAnimation = false;
}

void RGBled::updateLight() {
  analogWrite(this->rPin, (this->r * this->brightness) / 255);
  analogWrite(this->gPin, (this->g * this->brightness) / 255);
  analogWrite(this->bPin, (this->b * this->brightness) / 255);
}

void RGBled::on() {
  this->updateLight();
}

void RGBled::off() {
  digitalWrite(this->rPin, 0);
  digitalWrite(this->gPin, 0);
  digitalWrite(this->bPin, 0);
}

void RGBled::startAnimation() {
  this->doAnimation = true;
  this->animationStep = 0;
  this->stepAnimation();
}

void RGBled::stopAnimation() {
  this->doAnimation = false;
}

void RGBled::toggleAnimation() {
  this->doAnimation = !this->doAnimation;
}

void RGBled::setAnimation(AnimationStyle animationStyle, uint8_t frequency) {
  this->animationStyle = animationStyle;
  this->animationStep = 0;
  this->animationStepSize = frequency;
}

void RGBled::stepAnimation() {
  if (this->doAnimation) {
    switch (this->animationStyle) {
      case SAWTOOTH:
        this->brightness = this->animationStep * 255 / 100;
        break;
      case INVERSE_SAWTOOTH:
        this->brightness = 255 - (this->animationStep * 255 / 100);
        break;
      case TRIANGLE:
        if (this->animationStep < 50) {
          this->brightness = (this->animationStep * 255 / 50);
        } else {
          this->brightness = 510 - (this->animationStep * 255 / 50);
        }
        break;
      case HALF_SINE:
        this->brightness = halfSineValues[this->animationStep];
        break;
      default:
        this->doAnimation = false;
    }
    this->updateLight();
    this->animationStep += this->animationStepSize;
    this->animationStep = this->animationStep < 100 ? this->animationStep : 0;
  }
}


void RGBled::setBrightness(uint8_t brightness) {
  this->brightness = brightness;
  this->updateLight();
}

void RGBled::setColorRGB(uint8_t r, uint8_t g, uint8_t b) {
  this->r = r;
  this->g = g;
  this->b = b;
  this->updateLight();
}

void RGBled::setColorHex(unsigned long rgb) {
  this->r = rgb >> 16;
  this->g = (rgb & 0x00ff00) >> 8;
  this->b = (rgb & 0x0000ff);
  this->updateLight();
}

void RGBled::red() {
  this->r = 255;
  this->b = 0;
  this->g = 0;
  this->updateLight();
}

void RGBled::green() {
  this->r = 0;
  this->g = 255;
  this->b = 0;
  this->updateLight();
}

void RGBled::blue() {
  this->r = 0;
  this->g = 0;
  this->b = 255;
  this->updateLight();
}
