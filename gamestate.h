#pragma once

#include <arduino.h>
#include "led.h"
#include "buttons.h"

#define PIN_LED_A 15
#define PIN_LED_B 14
#define PIN_LED_C 16
#define PIN_LED_1 10
#define PIN_LED_2 A0
#define PIN_LED_3 A1
#define PIN_LED_4 A2
#define PIN_LED_5 A3

#define PIN_BUTTON_START 2
#define PIN_BUTTON_1 3
#define PIN_BUTTON_2 4
#define PIN_BUTTON_3 5
#define PIN_BUTTON_4 6
#define PIN_BUTTON_5 7

#define AUDIO 9

extern LED led_a, led_b, led_c, led_1, led_2, led_3, led_4, led_5;
extern LED* leds[];
extern Buttons buttons;
extern int stage;

void alien_print(const char *s);
char alien_char_decode(unsigned char c);
void clear_leds();
void reset();
