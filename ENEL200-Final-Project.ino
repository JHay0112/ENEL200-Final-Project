/**
 * ENEL200 Final Project 
 * Group 31
 * Plant Meter Prototype Board Software
 * 
 * Software is modularised for ease of maintenance
 * It is intended only for use as prototype/demonstration software
 * further software should be developed for a final product
 */

#include <Wire.h>
#include <SPI.h>
#include <MCP7940.h>
#include <Adafruit_Sensor.h>
#include <Adafruit_AM2320.h>

#include "def.h"
#include "button.h"
#include "display.h"
#include "Piezo.h"
#include "RGB_LED.h"

// Data collected by sensors
float soilMoisture[DATA_LEN] = {1.0};
float temperature[DATA_LEN] = {1.0};
float light[DATA_LEN] = {1.0};
float humidity[DATA_LEN] = {1.0};

// Keep track of page changes
bool pageChanged = true;

// Interface buttons
Button upButton;
Button downButton;
Button selectButton;
Button backButton;

// Feedback devices
RGBled stateLED(STATUS_R_PIN, STATUS_G_PIN, STATUS_B_PIN);
PiezoTone buzzer(BUZZER_PIN);

// Other peripherals
MCP7940_Class rtcc;
Adafruit_AM2320 am2320 = Adafruit_AM2320();

// Ticks for task scheduling
uint32_t ticks = 0;

/**
 * Appends data to the specified data list
 * 
 * @param data The data list to append to
 * @param len The length of the data list to append to
 * @param newData The new piece of data to append.
 * 
 * Note that this shuffles data down the list and may be intensive.
 */
void dataAppend(float data[], uint8_t len, float newData) {
  // This is an expensive operation which is stupid
  for (uint8_t i = 0; i < len - 1; i++) {
    data[i] = data[i + 1];
  }
  data[len - 1] = newData;
}

/**
 * Poll all nav buttons.
 */
void pollButtons(void) {
  button_poll(upButton);
  button_poll(downButton);
  button_poll(selectButton);
  button_poll(backButton);
}

/**
 * Read the light sensor
 * 
 * @return Lux value
 */
float readLight() {
  pinMode(AMBIENT_LIGHT_PIN, INPUT);
  return pow(8.0*pow(10.0, 11.0)/pow((330.0*1023.0/analogRead(SOIL_MOISTURE_PIN)) - 330.0, 3.0), 0.5);
}

/**
 * Read the soil moisture sensor
 * 
 * @return Relative soil moisture
 */
float readSoilMoisture() {
  pinMode(SOIL_MOISTURE_PIN, INPUT);
  return 100.0*analogRead(SOIL_MOISTURE_PIN)/1023.0;
}

/**
 * Read humidity sensor
 * 
 * @return Relative humidity
 */
float readHumidity() {
  float hum = am2320.readHumidity();
  if (hum > 100.0) {
    hum = 100.0;
  } else if (hum < 0.0001) {
    hum = 0.00001; 
  }
  return hum;
}

/**
 * Poll all sensors and append data to data lists
 */
void pollSensors() {
  dataAppend(soilMoisture, DATA_LEN, readSoilMoisture());
  dataAppend(temperature, DATA_LEN, am2320.readTemperature());
  dataAppend(humidity, DATA_LEN, readHumidity());
  dataAppend(light, DATA_LEN, readLight());
}


void setup() {
  // Initialise peripheral
  Serial.begin(9600);
  Wire.begin();
  SPI.begin();
  am2320.begin();
  rtcc.begin();
  display_init();

  // Setup displays
  upButton = button_init(UP_BUTTON_PIN, &display_up);
  downButton = button_init(DOWN_BUTTON_PIN, &display_down);
  selectButton = button_init(SELECT_BUTTON_PIN, &display_select);
  backButton = button_init(BACK_BUTTON_PIN, &display_back);

  // Setup state feedback peripoherals
  stateLED.green();
  stateLED.setAnimation(HALF_SINE, 1.0/LED_REFRESH_PERIOD_S);

  buzzer.startup();
}

void loop() {

  // Begin counting time
  uint32_t startTime = millis();

  // Poll all buttons
  pollButtons(); 

  // If a pagae has changed then refresh the display
  if (pageChanged) {
    display_refresh();
  } 

  // Step animation based on animation period
  if ((ticks % (LED_REFRESH_PERIOD_S*TICK_RATE_HZ)) == 0) {  
    stateLED.stepAnimation();
  }

  // Poll sensors if it is time to
  if ((ticks % (SENSOR_POLL_PERIOD_S*TICK_RATE_HZ)) == 0) {
    pollSensors();
  }
  
  ticks++;
  
  // Pacer
  while ((millis() - startTime) < 1000/TICK_RATE_HZ) {
    continue;  
  }
  
}
