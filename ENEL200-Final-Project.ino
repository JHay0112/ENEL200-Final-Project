#include <Arduino.h>
#include <U8g2lib.h>

#ifdef U8X8_HAVE_HW_SPI
#include <SPI.h>
#endif
#ifdef U8X8_HAVE_HW_I2C
#include <Wire.h>
#endif

U8G2_SSD1306_128X64_NONAME_1_HW_I2C u8g2(U8G2_R0, U8X8_PIN_NONE);

void setup(void) {
  u8g2.begin();
}

void loop(void) {
  u8g2.clearBuffer();          // clear the internal memory
  u8g2.setFont(u8g2_font_ncenB08_tr); // choose a suitable font
  u8g2.drawStr(0,10,"Hello World!");  // write something to the internal memory
  u8g2.setFont(u8g2_font_ncenB18_tr); // choose a suitable font
  u8g2.drawStr(0,40,"Hello World!");  // write something to the internal memory
  u8g2.setFont(u8g2_font_pieceofcake_mel_tr); // choose a suitable font
  u8g2.drawStr(0,60,"Hello World!");  // write something to the internal memory
  u8g2.setCursor(40, 80);
  u8g2.setFont(u8g2_font_ncenB08_tr); // choose a suitable font
  u8g2.print("Hello World!");
  u8g2.setFont(u8g2_font_unifont_t_symbols);
  u8g2.drawGlyph(40, 100, 0x2603);
  u8g2.sendBuffer();          // transfer internal memory to the display
  delay(1000);  
}
