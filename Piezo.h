// Piezo.h
#ifndef Piezo_h
#define Piezo_h

#include <Arduino.h>
#include "Notes.h"

#define NOTE_DURATION 240000
#define NOTE_SPACING 9/10

/**
 * Defines a note with pitch and duration
 */
struct Note {
  uint16_t pitch;
  uint8_t duration;
};

/*Note entertainer[] = {{NOTE_D4, 8}, {NOTE_DS4, 8}, {NOTE_E4, 8}, {NOTE_C5, 4}, {NOTE_E4, 8}, {NOTE_C5, 4}, {NOTE_E4, 8}, {NOTE_C5, 2}, {0, 4},
{NOTE_C5, 8}, {NOTE_D5, 8}, {NOTE_DS5, 8}, {NOTE_E5, 8}, {NOTE_C5, 8}, {NOTE_D5, 8}, {NOTE_E5, 4}, {NOTE_B4, 8}, {NOTE_D5, 4}, {NOTE_C5, 1}};
Note announcement[] = {{NOTE_C4, 4}, {NOTE_E4, 4}, {NOTE_G4, 4}, {NOTE_C5, 1}}; 
Note startupXP[] = {{NOTE_E6, 4}, {NOTE_B5, 4}, {NOTE_A5, 4}, {NOTE_A5, 8}, {NOTE_E6, 8}, {NOTE_B5, 2}};
Note shutdownXP[] = {{NOTE_A6, 4}, {NOTE_E6, 4}, {NOTE_A5, 4}, {NOTE_B5, 2}};*/


/**
 * The piezo class
 */
class PiezoTone
{
  private:
    uint8_t piezoPin;
    uint8_t noteLength;
    
  public:
    PiezoTone(uint8_t pin);
    void play(uint16_t frequency, uint32_t duration = 0);
    void stop();
    void noteSpacing(uint8_t spacing);
    void playMelody(Note* melody, uint16_t melody_length, uint8_t tempo);
    void playLoop(Note* melody, uint16_t melody_length, uint8_t tempo, uint8_t count);
    void error();
    void acknowledge();
    void startup();
};

#endif
