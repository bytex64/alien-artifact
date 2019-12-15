#include <Keyboard.h>
#include "gamestate.h"

void enter_keyboard_mode() {
  led_a.setMode(DIRECT_MODE);
  led_b.setMode(DIRECT_MODE);
  led_c.setMode(DIRECT_MODE);
  led_1.setMode(DIRECT_MODE);
  led_2.setMode(DIRECT_MODE);
  led_3.setMode(DIRECT_MODE);
  led_4.setMode(DIRECT_MODE);
  led_5.setMode(DIRECT_MODE);

  led_a.set(false);
  led_b.set(false);
  led_c.set(false);
  buttons.enableDebounce(true);
  buttons.enableTones(false);
  alien_print("keys");
  stage = 6;
}

void run_keyboard_mode() {
  if (buttons.getPressed(0)) {
    unsigned char alien_c = buttons.getStates() >> 1;
    Keyboard.write(alien_char_decode(alien_c));
  }
  led_1.set(buttons.getState(1));
  led_2.set(buttons.getState(2));
  led_3.set(buttons.getState(3));
  led_4.set(buttons.getState(4));
  led_5.set(buttons.getState(5));
}
