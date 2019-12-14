#include "gamestate.h"
#include "stages.h"
#include "sound.h"

unsigned char light;
unsigned long t0;
unsigned char part = 0;
unsigned char n_try = 0;

void enter_stage_1() {
  led_a.setMode(DIRECT_MODE);
  led_b.setMode(DIRECT_MODE);
  led_c.setMode(DIRECT_MODE);
  led_1.setMode(ONESHOT_MODE);
  led_2.setMode(ONESHOT_MODE);
  led_3.setMode(ONESHOT_MODE);
  led_4.setMode(ONESHOT_MODE);
  led_5.setMode(ONESHOT_MODE);
  led_a.set(true);
  led_b.set(false);
  led_c.set(false);
  led_1.set(false);
  led_2.set(false);
  led_3.set(false);
  led_4.set(false);
  led_5.set(false);
  buttons.enableDebounce(false);
  buttons.enableTones(false);
  stage = 1;

  alien_print("quick");
}

void light_it() {
  switch(light) {
    case 1:
      led_1.oneshot(100);
      break;
    case 2:
      led_2.oneshot(100);
      break;
    case 3:
      led_3.oneshot(100);
      break;
    case 4:
      led_4.oneshot(100);
      break;
    case 5:
      led_5.oneshot(100);
      break;
  }
}

void run_stage_1() {
  unsigned long now = millis();

  switch (part) {
    case 0:
      sound_ready();
      part = 1;
      t0 = millis();
      
      light = random(1, 6);
      light_it();
      break;
    case 1:
      if (now - t0 <= 500) {
        const unsigned char s = buttons.getStates();
        if (buttons.getState(1) && light == 1 ||
            buttons.getState(2) && light == 2 ||
            buttons.getState(3) && light == 3 ||
            buttons.getState(4) && light == 4 ||
            buttons.getState(5) && light == 5) {
          sound_success();
          alien_print("good");
          n_try++;
          if (n_try == 3) {
            // PROCEED!
            enter_stage_2();
            return;
          }          
          part = 0;
        }
      } else {
        sound_failure();
        alien_print("no");
        n_try = 0;
        part = 0;        
      }
      break;
  }
}
