#pragma once

#include <arduino.h>

class Buttons {
  unsigned char states, lastStates;
  unsigned long debounce_t0[6];
  bool debounce_enabled, tones_enabled;

  bool debounced_read(unsigned long t, unsigned char n);

  public:
    Buttons();
    void update();
    unsigned char getStates();
    bool getState(unsigned char n);
    unsigned char getAllPressed();
    bool getPressed(unsigned char n);
    void enableDebounce(bool enable);
    void enableTones(bool enable);
};
