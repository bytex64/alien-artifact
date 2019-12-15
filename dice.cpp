#include "gamestate.h"
#include "sound.h"

char current_roll, last_roll;

void enter_dice_mode() {
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
  alien_print("dice");
  stage = 4;
}

void displayRoll(char roll) {
  clear_leds();
  char digit1 = ((roll - 1) % 5) + 1;
  for (char i = 0; i < digit1; i++) {
    leds[i]->set(true);
  }

  led_a.set(roll > 5);
  led_c.set(roll > 10);
  led_b.set(roll > 15);   
}

void roll(char d) {
  last_roll = current_roll;
  
  led_a.set(false);
  led_b.set(false);
  led_c.set(false);
  clear_leds();
  for (char i = 0; i < (d/2); i++) {
    tone(AUDIO, 2185);
    delay(20);
    tone(AUDIO, 1772);
    delay(20);
  }
  noTone(AUDIO);
  
  current_roll = random(1, d + 1);
  Serial.println((int)current_roll);
  displayRoll(current_roll);
}

void run_dice_mode() {
  if (buttons.getState(0)) {
    // recall mode
    displayRoll(last_roll);
  } else {
    displayRoll(current_roll);
    
    // roll it!
    const char pressed = buttons.getAllPressed() >> 1;
    if (pressed & 0b00001) {
      // d4
      roll(4);
    } else if (pressed & 0b00010) {
      // d6
      roll(6);
    } else if (pressed & 0b00100) {
      // d8
      roll(8);
    } else if (pressed & 0b01000) {
      // d10
      roll(10);
    } else if (pressed & 0b10000) {
      // d20
      roll(20);
      if (current_roll == 20) {
        sound_success();
      } else if (current_roll == 1) {
        sound_failure();
      }
    }
  }
}
