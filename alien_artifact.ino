#include "gamestate.h"
#include "stages.h"

void setup() {
  randomSeed(analogRead(9));
  led_a.init();
  led_b.init();
  led_c.init();
  led_1.init();
  led_2.init();
  led_3.init();
  led_4.init();
  led_5.init();

  Serial.begin(115200);
}

void loop() {
  buttons.update();
  
  switch(stage) {
     case 0:
      if (buttons.getState(0)) {
        const unsigned int selector = buttons.getStates() >> 1;
        switch(selector) {
          case 0b00000:
          case 0b00001:
            enter_stage_1();
            break;
          case 0b00010:
            enter_stage_2();
            break;
          case 0b00100:
            enter_stage_3();
            break;
          case 0b01000:
            enter_dice_mode();
            break;
          case 0b10000:
            buttons.enableTones(true);
            enter_stage_5();
            break;
        }
      }
      break;
      
    case 1: run_stage_1(); break;
    case 2: run_stage_2(); break;
    case 3: run_stage_3(); break;
    case 4: run_dice_mode(); break;
    case 5: run_stage_5(); break;
  }

  led_a.step();
  led_b.step();
  led_c.step();
  led_1.step();
  led_2.step();
  led_3.step();
  led_4.step();
  led_5.step();
}
