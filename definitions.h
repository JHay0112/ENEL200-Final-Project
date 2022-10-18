#ifndef DEFINITIONS_H
#define DEFINITIONS_H

#include <Arduino.h>
#include <U8g2lib.h>

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

#define HOURS_PER_DAY 24
#define MINUTES_PER_HOUR 60
#define SECONDS_PER_MINUTE 60

#define TICK_RATE_HZ 50

#define DISPLAY_REFRESH_PERIOD_S 1
#define SENSOR_POLL_PERIOD_S 60

#define DATA_LEN 24

#endif
