#pragma once

#include <avr/io.h> /* for DDRB, PORTB, etc. */
#include <stdio.h>
#include <util/delay.h> /* for _delay_ms () */

#include "pwm.h"

typedef struct {
  float last_power;
  float current_power;
  uint16_t step_size;
  uint8_t duty_cycle;
  uint8_t direction;
} mppt_t;

mppt_t init_mppt(uint16_t step_size, uint8_t duty_cycle);

uint16_t hillClimb(mppt_t *mppt);

// float Power(uint8_t PWM);  // simulates inputpower reading

void mppt_update(mppt_t *mppt, uint16_t pv_voltage_mv, uint16_t pv_current_ma);
