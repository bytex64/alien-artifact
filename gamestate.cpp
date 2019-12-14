#include "gamestate.h"

LED led_a(PIN_LED_A);
LED led_b(PIN_LED_B);
LED led_c(PIN_LED_C);
LED led_1(PIN_LED_1);
LED led_2(PIN_LED_2);
LED led_3(PIN_LED_3);
LED led_4(PIN_LED_4);
LED led_5(PIN_LED_5);

LED* leds[] = {&led_1, &led_2, &led_3, &led_4, &led_5};

Buttons buttons;

int stage = 0;

void clear_leds() {
  for (char i = 0; i < 5; i++) {
    leds[i]->set(false);
  }
}

void reset() {
  // not really sure how this works
  void (*resetFunc)() = 0;
  resetFunc();
}
