#pragma once

#include <avr/io.h> /* for DDRB, PORTB, etc. */
#include <stdio.h>
#include <util/delay.h> /* for _delay_ms () */

#include "pwm.h"

typedef enum { UP, DOWN } direction_t;

typedef struct {
  uint32_t last_power;
  uint32_t current_power;
  uint16_t step_size;
  uint8_t duty_cycle;
  direction_t direction;
} mppt_t;

mppt_t init_mppt(uint16_t step_size, uint8_t duty_cycle);

void hillClimb(mppt_t *mppt);

uint8_t sweep(mppt_t *mppt, uint8_t duty_cycle, uint32_t pv_voltage_mv,
              uint32_t pv_current_ma);

// float Power(uint8_t PWM);  // simulates inputpower reading

void mppt_update(mppt_t *mppt, uint32_t pv_voltage_mv, uint32_t pv_current_ma);
