#include "sound.h"

void sound_success() {
  tone(AUDIO, 440, 100);
  delay(100);
  tone(AUDIO, 523, 100);
  delay(100);
  tone(AUDIO, 880, 100);
  delay(400);
}

void sound_failure() {
  tone(AUDIO, 349, 400);
  delay(500);
  tone(AUDIO, 277, 700);
  delay(500);
}

void sound_ready() {
  delay(500);
  tone(AUDIO, 440, 100);
  delay(500);
  tone(AUDIO, 440, 100);
  delay(500);
  tone(AUDIO, 440, 100);
  delay(700);
  tone(AUDIO, 880, 250);  
}

void tone_1(bool high) {
  tone(AUDIO, 220 * (high + 1));
}

void tone_2(bool high) {
  tone(AUDIO, 261.6256 * (high + 1));
}

void tone_3(bool high) {
  tone(AUDIO, 293.6648 * (high + 1));
}

void tone_4(bool high) {
  tone(AUDIO, 349.2282 * (high + 1));
}

void tone_5(bool high) {
  tone(AUDIO, 391.9954 * (high + 1));
}

void tone_off() {
  noTone(AUDIO);
}
