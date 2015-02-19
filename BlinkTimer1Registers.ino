#include <avr/io.h>
#include <avr/interrupt.h>

#define LED_PIN 7
#define LED_PIN_BITMASK 1 << LED_PIN
#define SECOND_TICKS 15624

void setup() {
  cli();
  DDRD |= LED_PIN_BITMASK;

  TCCR1A = 0;
  TCCR1B = 0;
  
  OCR1A = SECOND_TICKS * 3;
  TCCR1B |= (1 << WGM12) | (1 << CS12) | (1 << CS10);
  TIMSK1 |= (1 << OCIE1A);
  sei();
}

void loop() {
}

ISR(TIMER1_COMPA_vect) {
  unsigned char newPin = (~PIND & LED_PIN_BITMASK);
  PORTD = (PIND & ~LED_PIN_BITMASK) | newPin;
  OCR1A = newPin ? SECOND_TICKS : SECOND_TICKS * 3;
}
