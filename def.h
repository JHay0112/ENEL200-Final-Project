/**
 * Set of definitions that were useful to break out into own module
 * Note that definitions are being used to ensure fields are in progmem
 * This is inline with ENCE260 standards
 * 
 * @author J. L. Hay
 */

#ifndef DEF_H
#define DEF_H

#include <Arduino.h>

#define SPI_SS_PIN 10
#define SPI_COPI_PIN 11
#define SPI_CIPO_PIN 12
#define SPI_SCK_PIN 13

#define AMBIENT_LIGHT_PIN A0
#define SOIL_MOISTURE_PIN A1

#define BUZZER_PIN 4

#define STATUS_R_PIN 3
#define STATUS_G_PIN 5
#define STATUS_B_PIN 6

#define I2C_SDA_PIN A4
#define I2C_SCL_PIN A5

#define TICK_RATE_HZ 50

#define LED_REFRESH_PERIOD_S 1
#define SENSOR_POLL_PERIOD_S 1

#define DATA_LEN 24

#endif
