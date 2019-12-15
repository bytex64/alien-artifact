#include "gamestate.h"
#include "stages.h"
#include "sound.h"

unsigned char puzzle_seq[8];
unsigned char puzzle_length;
unsigned char puzzle_ctr;

unsigned char phase = 0;

void clear_leds();

void init_puzzle() {
  for (char i = 0; i < 8; i++) {
    puzzle_seq[i] = random(0, 5);
  }
  puzzle_length = 1;
  puzzle_ctr = 0;
  alien_print("repeat");
  clear_leds();
  delay(1000);
}

void enter_stage_3() {
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
  led_c.set(true);
  buttons.enableDebounce(true);
  buttons.enableTones(true);
  stage = 3;

  init_puzzle();
}

void run_stage_3() {
  switch(phase) {
    case 0:
      // show the pattern so far
      for (char i = 0; i < puzzle_length; i++) {
        const char current_led = puzzle_seq[i];
        clear_leds();
        delay(100);
        leds[current_led]->set(true);
        switch(current_led) {
          case 0: tone_1(false); break;
          case 1: tone_2(false); break;
          case 2: tone_3(false); break;
          case 3: tone_4(false); break;
          case 4: tone_5(false); break;
        }
        delay(750);
        tone_off();
      }
      puzzle_ctr = 0;
      phase = 1;
      tone(AUDIO, 440, 100);
      break;
    case 1:
      const char b = buttons.getAllPressed() >> 1;
      const char current_led = puzzle_seq[puzzle_ctr];

      // mirror button presses
      led_1.set(buttons.getState(1));
      led_2.set(buttons.getState(2));
      led_3.set(buttons.getState(3));
      led_4.set(buttons.getState(4));
      led_5.set(buttons.getState(5));
      
      if (b > 0) {

        if (b & 0b00001 && current_led == 0 ||
            b & 0b00010 && current_led == 1 ||
            b & 0b00100 && current_led == 2 ||
            b & 0b01000 && current_led == 3 ||
            b & 0b10000 && current_led == 4) {
          // correct; continue
          puzzle_ctr++;
          if (puzzle_ctr == puzzle_length) {
            // sequence correct; increase length if we're not at the end
            if (puzzle_length == 8) {
              // PROCEED
              delay(500);
              tone_off();
              alien_print("you win m m m m m ");
              reset();
              return;
            }
            puzzle_length++;
            phase = 0;
            delay(500);
            sound_success();
          }
        } else {
          // incorrect; restart
          sound_failure();
          init_puzzle();
          phase = 0;
        }
      }
      break;
  }
}
