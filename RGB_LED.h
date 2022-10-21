/**
 * Controls an RGB LED indicator
 * 
 * @author W. W. Beauchamp, and J. L. Hay
 */
 
#ifndef RGB_LED_h
#define RGB_LED_h

#include <Arduino.h>

/**
 * Supported animations
 */
enum AnimationStyle {
  SAWTOOTH = 0,
  INVERSE_SAWTOOTH,
  TRIANGLE,
  HALF_SINE,
};

class RGBled
{
  private:
    uint8_t r;
    uint8_t g;
    uint8_t b;
    uint8_t brightness;

    uint8_t rPin;
    uint8_t gPin;
    uint8_t bPin;

    bool doAnimation;
    AnimationStyle animationStyle;
    uint8_t animationStep;
    uint8_t animationStepSize;

    void updateLight();

   public:
    RGBled(uint8_t rPin, uint8_t gPin, uint8_t bPin);
    void on();
    void off();
    void startAnimation();
    void stopAnimation();
    void toggleAnimation();
    void setAnimation(AnimationStyle animationStyle, uint8_t frequency);
    void stepAnimation();
    void setBrightness(uint8_t brightness);
    void setColorRGB(uint8_t r, uint8_t g, uint8_t b);
    void setColorHex(unsigned long rgb);
    void red();
    void green();
    void blue();
    
};

#endif
