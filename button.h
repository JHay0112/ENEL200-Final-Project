/**
 * Button module
 * 
 * @author J. L. Hay
 */

#ifndef BUTTON_H
#define BUTTON_H

#define BACK_BUTTON_PIN A2
#define SELECT_BUTTON_PIN A3
#define UP_BUTTON_PIN 2
#define DOWN_BUTTON_PIN 7
#define NUM_BUTTONS 4

#include <Arduino.h>
#include "Piezo.h"
#include "def.h"

/**
 * Button struct
 */
typedef struct {
  uint8_t p;
  bool prevState;
  void (*callback)(void);
} Button;

Button button_init(uint8_t p, void (*callback)(void));
void button_poll(Button button);
void display_up();
void display_down();
void display_select();
void display_back();
void display_refresh();

#endif 
