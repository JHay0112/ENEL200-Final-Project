#ifndef DISPLAY_H
#define DISPLAY_H

#define DISPLAY_SDA_PIN 9
#define DISPLAY_SCL_PIN 8

#define DISPLAY_WIDTH 128
#define DISPLAY_HEIGHT 64
#define DISPLAY_FONT u8g2_font_t0_11_tr
#define DISPLAY_FONT_HEIGHT 8

#define DISPLAY_EMOJI_FONT u8g2_font_unifont_t_emoticons
#define DISPLAY_SMILY_FACE 0x0020
#define DISPLAY_SUNGLASSES 0x002E
#define DISPLAY_ANGRY_FACE 0x0040
#define DISPLAY_SAD_FACE 0x0061

#define DISPLAY_PLANT_FONT u8g2_font_unifont_t_77
#define DISPLAY_PLANT_ICON 0x2698

#define DATA_Y_OFFSET 10
#define DATA_X_OFFSET 10

#define NUM_PAGES 4

#include <Arduino.h>
#include <U8g2lib.h>

#include "def.h"

enum Page {
  IDLE,
  MENU,
  MESSAGE,
  TEMPERATURE,
  HUMIDITY,
  SOIL_MOISTURE,
  LIGHT
};

void display_init();
void display_data(float data[], uint8_t len, const char title[]);
void display_message(const char msg[]);
void display_menu();
void display_refresh();

#endif
