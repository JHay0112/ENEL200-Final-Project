#include "button.h"

extern PiezoTone buzzer;

Button button_init(uint8_t p, void (*callback)(void)) {
  Button newButton = {
    p,
    HIGH, 
    callback
  };

  pinMode(p, INPUT);

  return newButton;
}

void button_poll(Button button) {
  if ((digitalRead(button.p) == LOW) && (button.prevState == HIGH)) {
    button.prevState = LOW;
    buzzer.acknowledge();
    button.callback(); 
  } else {
    button.prevState = digitalRead(button.p);
  }
}
