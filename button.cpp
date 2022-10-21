/**
 * Button module
 * 
 * @author J. L. Hay
 */

#include "button.h"

/**
 * Loads an external buzzer
 * not safe, would prefer to fix this for a final product
 */
extern PiezoTone buzzer;

/**
 * Initialises a button struct
 * 
 * @param p The pin the button is on
 * @param callback Callback function pointer to be called upon press
 */
Button button_init(uint8_t p, void (*callback)(void)) {
  Button newButton = {
    p,
    HIGH, 
    callback
  };

  pinMode(p, INPUT);

  return newButton;
}

/**
 * Polls the button
 * Includes rudimentary software debouncing
 * 
 * @param button The button to poll the state of
 */
void button_poll(Button button) {
  if ((digitalRead(button.p) == LOW) && (button.prevState == HIGH)) {
    button.prevState = LOW;
    buzzer.acknowledge();
    button.callback(); 
  } else {
    button.prevState = digitalRead(button.p);
  }
}
