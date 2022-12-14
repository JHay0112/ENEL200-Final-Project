/**
 * Display module
 * 
 * @author J. L. Hay
 */

#include "display.h"

/**
 * u8g2 display driver instantiation
 */
U8G2_SSD1306_128X64_NONAME_1_SW_I2C u8g2(U8G2_R0, DISPLAY_SCL_PIN, DISPLAY_SDA_PIN, U8X8_PIN_NONE);

/**
 * External data pointers
 * 
 * Once again this doesn't feel safe but was convenient for the purposes of the demo
 * I would prefer to do this another way
 */
extern float soilMoisture[];
extern float light[];
extern float temperature[];
extern float humidity[];
extern bool pageChanged;

/**
 * Page tracker
 */
static Page currentPage = IDLE;
/**
 * Selection options for menu
 */
static const Page menuPages[NUM_PAGES] = {TEMPERATURE, HUMIDITY, SOIL_MOISTURE, LIGHT};
/**
 * Currently selected page on menu
 */
static uint8_t selectedMenuPage = 0;

/**
 * Initialise display
 */
void display_init() {
  u8g2.begin();
}

/**
 * Private function that returns a pointer to the highest value in data
 * Used for histogram scaling
 * 
 * @param data The data to find the max of
 * @param len The length of the data array
 */
float* dataMax(float data[], uint8_t len) {
  float* highest = &data[0];
  for (uint8_t i = 0; i < len; i++) {
    if (data[i] > *highest) {
      highest = &data[i];
    }
  }
  return highest;
}

/**
 * Display a set of data as a histogram on the screen
 * 
 * @param data The data to display
 * @param len The length of the data to display
 * @param title The title of the data
 */
void display_data(float data[], uint8_t len, const char title[]) {
  
  uint8_t dataWidth = (DISPLAY_WIDTH - 3*DATA_X_OFFSET)/len;
  float maxVal = *dataMax(data, len);
  
  u8g2.firstPage();
  do {
    for (uint8_t i = 0; i < len; i++) {
      u8g2.drawBox(i*dataWidth + 2.5*DATA_X_OFFSET, 1.2*DATA_Y_OFFSET + (DISPLAY_HEIGHT - 2*DATA_Y_OFFSET)*(1.0 - data[i]/maxVal), dataWidth, DISPLAY_HEIGHT);
    }
    
    u8g2.setFont(DISPLAY_FONT);
    u8g2.setCursor(0, DATA_Y_OFFSET);
    u8g2.print(title);
    
    u8g2.setDrawColor(0);
    u8g2.drawBox(DATA_X_OFFSET, DISPLAY_HEIGHT - DATA_Y_OFFSET, DISPLAY_WIDTH, DISPLAY_HEIGHT);

    u8g2.setDrawColor(1);

    u8g2.setCursor(2*DATA_X_OFFSET, DISPLAY_HEIGHT);
    u8g2.print(0);
    u8g2.setCursor(DISPLAY_WIDTH - DATA_X_OFFSET, DISPLAY_HEIGHT);
    u8g2.print(len);

    u8g2.setCursor(0, DISPLAY_HEIGHT - DATA_Y_OFFSET);
    u8g2.print(0.0, 1);
    u8g2.setCursor(0, DATA_Y_OFFSET + DISPLAY_FONT_HEIGHT + 5);
    u8g2.print(maxVal, 1);
  } while (u8g2.nextPage());
}

/**
 * Displays a string message on the screen
 * 
 * @param msg The message to display
 */
void display_message(const char msg[]) {

  u8g2.firstPage();
  do {
    u8g2.setFont(DISPLAY_FONT);
    u8g2.setCursor(0, 10);
    u8g2.print(msg);
  } while (u8g2.nextPage());
}

/**
 * Displays the menu screen
 */
void display_menu() {
  u8g2.firstPage();
  do {
    u8g2.setFont(DISPLAY_FONT);
    for (uint8_t i = 0; i < NUM_PAGES; i++) {
      u8g2.setCursor(DISPLAY_FONT_HEIGHT, (i + 1)*(DISPLAY_FONT_HEIGHT + 5));

      switch(menuPages[i]) {
        case TEMPERATURE:
          u8g2.print("Temperature");
          break;
        case HUMIDITY:
          u8g2.print("Humidity");
          break;
        case SOIL_MOISTURE:
          u8g2.print("Soil Moisture");
          break;
        case LIGHT:
          u8g2.print("Light");
          break;
      }

      if (i == selectedMenuPage) {
        u8g2.drawFrame(0, i*(DISPLAY_FONT_HEIGHT + 5) + 1, DISPLAY_WIDTH, DISPLAY_FONT_HEIGHT + 8);
      }
    }
  } while (u8g2.nextPage());
}

/**
 * Intended as a button callback
 * Handles when the up button is pressed
 */
void display_up() {
  switch (currentPage) {
    case IDLE:
      currentPage = MENU;
      pageChanged = true;
      break;
    case MENU:
      if (selectedMenuPage != 0) {
        selectedMenuPage--;
      }
      pageChanged = true;
      break;
  }
  
}

/**
 * Intended as a button callback
 * Handles when the down button is pressed
 */
void display_down() {
  switch (currentPage) {
    case IDLE:
      currentPage = MENU;
      pageChanged = true;
      break;
    case MENU:
      if (selectedMenuPage < NUM_PAGES - 1) {
        selectedMenuPage++;
      }
      pageChanged = true;
      break;
  }
   
}

/**
 * Intended as a button callback
 * Handles when the select button is pressed
 */
void display_select() {
   switch (currentPage) {
    case IDLE:
      currentPage = MENU;
      pageChanged = true;
      break;
    case MENU:
      currentPage = menuPages[selectedMenuPage];
      pageChanged = true;
      break;
   }
}

/**
 * Intended as a button callback
 * Handles when the back button is pressed
 */
void display_back() {
   switch (currentPage) {
    case IDLE:
      currentPage = MENU;
      pageChanged = true;
      break;
    case MENU:
      currentPage = IDLE;
      pageChanged = true;
      break;
    default:
      currentPage = MENU;
      pageChanged = true;
      break;
   }
}

/**
 * Displays the idle screen
 */
void display_idle() {
  u8g2.firstPage();
  do {
    u8g2.setFont(DISPLAY_PLANT_FONT);
    u8g2.drawGlyph(DISPLAY_WIDTH/2 - DISPLAY_FONT_HEIGHT, DISPLAY_HEIGHT/2 - DISPLAY_FONT_HEIGHT/2, DISPLAY_PLANT_ICON);
    u8g2.setFont(DISPLAY_FONT);
    u8g2.setCursor(DISPLAY_WIDTH/2 - 12, DISPLAY_HEIGHT/2 + 2*DISPLAY_FONT_HEIGHT);
    u8g2.print("IDLE");
  } while (u8g2.nextPage());
}

/**
 * Refreshes the display based on the last registered change to be made.
 * To be called after each change
 */
void display_refresh() {
  if (pageChanged) {
    switch (currentPage) {
      case MENU:
        display_menu();
        break;
      case TEMPERATURE:
        display_data(temperature, DATA_LEN, "Temperature");
        break;
      case HUMIDITY:
        display_data(humidity, DATA_LEN, "Relative Humidity");
        break;
      case SOIL_MOISTURE:
        display_data(soilMoisture, DATA_LEN, "Soil Moisture");
        break;
      case LIGHT:
        display_data(light, DATA_LEN, "Ambient Light");
        break;
      case IDLE:
        display_idle();
        break;
    }
  }
  pageChanged = false;
}
