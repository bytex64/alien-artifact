#include "gamestate.h"

void enter_stage_5() {
  led_a.setMode(DIRECT_MODE);
  led_b.setMode(DIRECT_MODE);
  led_c.setMode(DIRECT_MODE);
  led_1.setMode(ONESHOT_MODE);
  led_2.setMode(ONESHOT_MODE);
  led_3.setMode(ONESHOT_MODE);
  led_4.setMode(ONESHOT_MODE);
  led_5.setMode(ONESHOT_MODE);
  led_a.set(false);
  led_b.set(false);
  led_c.set(false);
  led_1.set(false);
  led_2.set(false);
  led_3.set(false);
  led_4.set(false);
  led_5.set(false);
  buttons.enableTones(true);
  alien_print("piano");
  stage = 5;
}

void run_stage_5() {
  if (buttons.getState(1))
    led_1.oneshot(500);
  if (buttons.getState(2))
    led_2.oneshot(500);
  if (buttons.getState(3))
    led_3.oneshot(500);
  if (buttons.getState(4))
    led_4.oneshot(500);
  if (buttons.getState(5)) {
    led_5.oneshot(500);
  }
}
