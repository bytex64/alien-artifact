#pragma once

#define RANDOM_MODE 0
#define DIRECT_MODE 1
#define ONESHOT_MODE 2

class LED {
  unsigned char pin, mode;
  unsigned long t0, delay;
  bool state;

  public:
    LED(unsigned char pin);
    void init();
    void setMode(unsigned char mode);
    void set(bool state);
    void oneshot(unsigned int delay);
    void step();
};
