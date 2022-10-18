#include "Piezo.h"


PiezoTone::PiezoTone(uint8_t pin){
  piezoPin = pin;
}

void PiezoTone::play(uint16_t frequency, uint32_t duration) {
  tone(piezoPin, frequency, duration);
}

void PiezoTone::stop() {
  noTone(piezoPin);
}

void PiezoTone::noteSpacing(uint8_t spacing) {
  noteLength = 255 - spacing;
}

void PiezoTone::playMelody(Note* melody, uint16_t melody_length, uint8_t tempo) {
  for (int i = 0; i < melody_length / 3; i++) {
    uint32_t duration = NOTE_DURATION / tempo / melody[i].duration;
    play(melody[i].pitch, duration * noteLength / 255);
    delay(duration);
  }
}
void PiezoTone::playLoop(Note* melody, uint16_t melody_length, uint8_t tempo, uint8_t count) {
  for (uint8_t j = 0; j < count; j++) {
    playMelody(melody, melody_length, tempo);
    }
}

void PiezoTone::error() {
  play(NOTE_FS3, 96);
}

void PiezoTone::acknowledge() {
  play(NOTE_D5, 48);
}

Note buttonPress[] = {{NOTE_A6, 8}, {NOTE_CS7, 8}, {NOTE_E7, 8}};

void PiezoTone::startup() {
  uint8_t noteLengthRecord = noteLength;
  noteLength = 128;
  playMelody(buttonPress, 9, 180);
  noteLength = noteLengthRecord;
}
