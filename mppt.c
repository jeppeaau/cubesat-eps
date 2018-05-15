#include "mppt.h"
#include "uart.h"

mppt_t init_mppt(uint16_t step_size, uint8_t duty_cycle) {
  return (mppt_t){0, 0, step_size, duty_cycle, 1};
}

// Hillclimb algorithm function that takes Power history and current power,
// stepsize and current modulation level (PWM). The algorithm chooses whether to
// continue moving in the same direction. Returns the updated PWM value.
uint16_t hillClimb(mppt_t *mppt) {
  if (mppt->current_power >= mppt->last_power) {
    // If the new power value is higher than or equal the old:
    if (mppt->direction == 1) {
      // the system continues going up:
      mppt->duty_cycle += mppt->step_size;
      mppt->direction = 1;
    } else {
      // or continues going down:
      mppt->duty_cycle -= mppt->step_size;
      mppt->direction = 0;
    }
  } else {
    // Otherwise, the new power value is lower than the old, the system goes the
    // opposite way compared to the last step:
    if (mppt->direction == 1) {
      mppt->duty_cycle -= mppt->step_size;
      mppt->direction = 0;
    } else {
      mppt->duty_cycle += mppt->step_size;
      mppt->direction = 1;
    }
  }

  return mppt->duty_cycle;
  // The function returns the updated PWM value.
}

void mppt_update(mppt_t *mppt, uint16_t pv_voltage_mv, uint16_t pv_current_ma) {
  pwm_set_duty_cycle(mppt->duty_cycle, DDD6);

  mppt->current_power = pv_voltage_mv * pv_current_ma;
  // The power value is calculated based on current voltage and current.

  mppt->duty_cycle = hillClimb(mppt);
  // PWM variable is updated, by calling the hillClimb function, based on new
  // power calculation.

  mppt->last_power = mppt->current_power;
  // Power level history variable is updated.
}
