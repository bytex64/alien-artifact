#include "buttons.h"
#include "gamestate.h"
#include "sound.h"

const unsigned char pinmap[] = {PIN_BUTTON_START, PIN_BUTTON_1, PIN_BUTTON_2, PIN_BUTTON_3, PIN_BUTTON_4, PIN_BUTTON_5};

Buttons::Buttons() {
  this->states = 0;
  for (char i = 0; i < 6; i++) {
    pinMode(pinmap[i], INPUT_PULLUP);
    this->debounce_t0[i] = 0;
  }
  this->debounce_enabled = this->tones_enabled = false;
}

bool Buttons::debounced_read(const unsigned long t, unsigned char n) {
  if (t - this->debounce_t0[n] < 250) {
    return this->getState(n);
  } else {
    this->debounce_t0[n] = t;
    return !digitalRead(pinmap[n]);
  }
}

void Buttons::update() {
  const unsigned long now = millis();
  this->lastStates = this->states;
  if (this->debounce_enabled) {
    this->states =
        this->debounced_read(now, 0)
      | this->debounced_read(now, 1) << 1
      | this->debounced_read(now, 2) << 2
      | this->debounced_read(now, 3) << 3
      | this->debounced_read(now, 4) << 4
      | this->debounced_read(now, 5) << 5;
  } else {
    this->states =
        !digitalRead(pinmap[0])
      | !digitalRead(pinmap[1]) << 1
      | !digitalRead(pinmap[2]) << 2
      | !digitalRead(pinmap[3]) << 3
      | !digitalRead(pinmap[4]) << 4
      | !digitalRead(pinmap[5]) << 5;
  }

  if (this->tones_enabled) {
    const bool high = this->getState(0);
    if (this->states & 0b000010) {
      tone_1(high);
    } else if (this->states & 0b000100) {
      tone_2(high);
    } else if (this->states & 0b001000) {
      tone_3(high);
    } else if (this->states & 0b010000) {
      tone_4(high);
    } else if (this->states & 0b100000) {
      tone_5(high);
    } else {
      noTone(AUDIO);
    }
  }
}

unsigned char Buttons::getStates() {
  return this->states;
}

bool Buttons::getState(unsigned char n) {
  return bitRead(this->states, n);
}

unsigned char Buttons::getAllPressed() {
  return ~this->lastStates & this->states;
}

bool Buttons::getPressed(unsigned char n) {
  return bitRead(this->getAllPressed(), n);
}

void Buttons::enableDebounce(bool enable) {
  this->debounce_enabled = true;
}

void Buttons::enableTones(bool enable) {
  this->tones_enabled = enable;
}
