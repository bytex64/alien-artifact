#include "gamestate.h"
#include "stages.h"
#include "sound.h"

unsigned char puzzle_state;

void enter_stage_2() {
  led_a.setMode(DIRECT_MODE);
  led_b.setMode(DIRECT_MODE);
  led_c.setMode(DIRECT_MODE);
  led_1.setMode(DIRECT_MODE);
  led_2.setMode(DIRECT_MODE);
  led_3.setMode(DIRECT_MODE);
  led_4.setMode(DIRECT_MODE);
  led_5.setMode(DIRECT_MODE);

  led_a.set(false);
  led_b.set(true);
  led_c.set(false);
  buttons.enableDebounce(true);
  buttons.enableTones(true);
  stage = 2;

  // random selection of five bits, excluding all 1s (the goal condition)
  puzzle_state = random(0, 31);
  alien_print("light");
  clear_leds();
  delay(1000);
}

void run_stage_2() {
  if (puzzle_state == 0b11111) {
    sound_success();
    alien_print("good");
    // PROCEED
    enter_stage_3();
  }
  
  if (buttons.getPressed(1)) {
    puzzle_state ^= 0b10101;
  } else if (buttons.getPressed(2)) {
    puzzle_state ^= 0b00111;
  } else if (buttons.getPressed(3)) {
    puzzle_state ^= 0b11100;
  } else if (buttons.getPressed(4)) {
    puzzle_state ^= 0b11010;
  } else if (buttons.getPressed(5)) {
    puzzle_state ^= 0b01101;
  }
  
  led_1.set(puzzle_state & 0b00001);
  led_2.set(puzzle_state & 0b00010);
  led_3.set(puzzle_state & 0b00100);
  led_4.set(puzzle_state & 0b01000);
  led_5.set(puzzle_state & 0b10000);
}
