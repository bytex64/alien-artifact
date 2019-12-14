#include <arduino.h>
#include "led.h"

LED::LED(unsigned char pin) {
  this->pin = pin;
  this->mode = 0;
  this->t0 = 0;
  this->state = false;
}

void LED::init() {
  pinMode(this->pin, OUTPUT);
}

void LED::setMode(unsigned char m) {
  this->mode = m;
}

void LED::set(bool state) {
  this->state = state;
  digitalWrite(this->pin, state ? HIGH : LOW);
}

void LED::oneshot(unsigned int delay) {
  this->set(true);
  this->t0 = millis();
  this->delay = delay;
}

void LED::step() {
  unsigned long now = millis();
  
  switch(this->mode) {
    case RANDOM_MODE:
      if (now - this->t0 > this->delay) {
        this->set(!this->state);
        this->t0 = now;
        this->delay = random(100, 500);
      }
      break;
    case DIRECT_MODE:
      break;
    case ONESHOT_MODE:
      if (this->state && now - this->t0 > this->delay) {
        this->set(false);
      }
      break;
  }
}
