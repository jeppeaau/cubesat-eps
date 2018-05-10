#include "onlaunch.h"

uint8_t establish_connection() {
  while (power >= power_threshold && !radio_response()) {
    burn_wire();
  }

  return power >= power_threshold;
}

void launch_sequence() {
  uint8_t got_response;

  while (1) {
    got_response = establish_connection();

    if (got_response) {
      return;
    } else {
      while (power < power_threshold + power_threshold_hysteresis)
        ;
    }
  }
}

void burn_wire() {
  // sets pin high, fet turned on when burning
  PORTD |= (1 << BURN_PIN);  // Sets BURN_PIN_PORTD pin high
  _delay_ms(BURN_TIME_MILLIS);
  PORTD &= ~(1 << BURN_PIN);  // Sets BURN_PIN_PORTD pin low
}

uint8_t radio_response() { return 1; }
