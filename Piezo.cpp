/**
 * Piezo Buzzer module
 * 
 * @author W. W. Beauchamp, and J. L. Hay
 */

#include "Piezo.h"

/**
 * Initaliases a piezo object
 * 
 * @param pin The pin the piezo transducer is attached to
 */
PiezoTone::PiezoTone(uint8_t pin){
  piezoPin = pin;
}

/**
 * Plays a a pure tone for the specified duration
 * 
 * @param frequency The tone to play
 * @param duration The length of time to play the tone for
 */
void PiezoTone::play(uint16_t frequency, uint32_t duration) {
  tone(piezoPin, frequency, duration);
}

/**
 * Stops the piezo from playing
 */
void PiezoTone::stop() {
  noTone(piezoPin);
}

/**
 * Defines note spacing
 * 
 * @param spacing The spacing between notes to set
 */
void PiezoTone::noteSpacing(uint8_t spacing) {
  noteLength = 255 - spacing;
}

/**
 * Plays a melody
 * 
 * @param melody Note array
 * @param melody_length Length of note array
 * @param tempo The tempo of the melody
 */
void PiezoTone::playMelody(Note* melody, uint16_t melody_length, uint8_t tempo) {
  for (int i = 0; i < melody_length / 3; i++) {
    uint32_t duration = NOTE_DURATION / tempo / melody[i].duration;
    play(melody[i].pitch, duration * noteLength / 255);
    delay(duration);
  }
}

/**
 * Plays a melody a number of times
 * 
 * @param melody Note array
 * @param melody_length Length of note array
 * @param tempo The tempo of the melody
 * @param count Number of times to play the melody
 */
void PiezoTone::playLoop(Note* melody, uint16_t melody_length, uint8_t tempo, uint8_t count) {
  for (uint8_t j = 0; j < count; j++) {
    playMelody(melody, melody_length, tempo);
    }
}

/**
 * Play a pre-defined error tone
 */
void PiezoTone::error() {
  play(NOTE_FS3, 96);
}

/**
 * Play a pre-defined acknowledge tone
 */
void PiezoTone::acknowledge() {
  play(NOTE_D5, 48);
}

/**
 * Button press melody
 */
Note buttonPress[] = {{NOTE_A6, 8}, {NOTE_CS7, 8}, {NOTE_E7, 8}};

/**
 * Play a pre-defined startup tone
 */
void PiezoTone::startup() {
  uint8_t noteLengthRecord = noteLength;
  noteLength = 128;
  playMelody(buttonPress, 9, 180);
  noteLength = noteLengthRecord;
}
