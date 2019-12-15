#include "gamestate.h"

// Alien alphabet:
// 00000 -> [space]
// 00001 A
// 00010 B
// 00011 C
// 00100 D
// 00101 E
// 00110 F
// 00111 G
// 01000 H
// 01001 I
// 01010 J
// 01011 K
// 01100 L
// 01101 M
// 01110 N
// 01111 O
// 10000 P
// 10001 Q
// 10010 R
// 10011 S
// 10100 T
// 10101 U
// 10110 V
// 10111 W
// 11000 X
// 11001 Y
// 11010 Z
// 11011 1
// 11100 2
// 11101 3
// 11110 4
// 11111 5

void alien_print(const char *s) {
  char *p = s;
  while (*p != 0) {
    unsigned char led_out = 0;
    if (*p >= 0x41 && *p <= 0x5a) {
      led_out = *p - 0x40;
    } else if (*p >= 0x61 && *p <= 0x7a) {
      led_out = *p - 0x60;
    }

    digitalWrite(PIN_LED_1, LOW);
    digitalWrite(PIN_LED_2, LOW);
    digitalWrite(PIN_LED_3, LOW);
    digitalWrite(PIN_LED_4, LOW);
    digitalWrite(PIN_LED_5, LOW);
    
    delay(100);

    digitalWrite(PIN_LED_1, led_out & 0b00001);
    digitalWrite(PIN_LED_2, led_out & 0b00010);
    digitalWrite(PIN_LED_3, led_out & 0b00100);
    digitalWrite(PIN_LED_4, led_out & 0b01000);
    digitalWrite(PIN_LED_5, led_out & 0b10000);
      
    delay(750);

    p++;
  }

  digitalWrite(PIN_LED_1, LOW);
  digitalWrite(PIN_LED_2, LOW);
  digitalWrite(PIN_LED_3, LOW);
  digitalWrite(PIN_LED_4, LOW);
  digitalWrite(PIN_LED_5, LOW);
}

char alien_char_decode(unsigned char c) {
  if (c == 0) {
    return ' ';
  } else if (c < 26) {
    return c + 0x40;
  } else {
    return c + 2;
  }
}
