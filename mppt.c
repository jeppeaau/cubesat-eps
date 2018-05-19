#include "mppt.h"
#include "uart.h"

mppt_t init_mppt(uint16_t step_size, uint8_t duty_cycle) {
  return (mppt_t){0, 0, step_size, duty_cycle, 0};
}

uint8_t sweep(mppt_t *mppt, uint8_t duty_cycle, uint32_t pv_voltage_mv,
              uint32_t pv_current_ma) {
  mppt->duty_cycle += 5;

  if (mppt->duty_cycle < 255) {
    pwm_set_duty_cycle(mppt->duty_cycle, DDD6);
  }

  mppt->current_power = (pv_current_ma * pv_voltage_mv);

  if (mppt->current_power >= mppt->last_power) {
    mppt->last_power = mppt->current_power;
    return (mppt->duty_cycle) - 1;
  }

  return duty_cycle;
}

// Hillclimb algorithm function that takes Power history and current power,
// stepsize and current modulation level (PWM). The algorithm chooses whether to
// continue moving in the same direction. Returns the updated PWM value.
void hillClimb(mppt_t *mppt) {
  if (mppt->current_power >= (mppt->last_power)) {
    // If the new power value is higher than or equal the old:
    if (mppt->direction == UP) {
      // the system continues going up:
      mppt->duty_cycle += mppt->step_size;
      mppt->direction = UP;
    } else {
      // or continues going down:
      mppt->duty_cycle -= mppt->step_size;
      mppt->direction = DOWN;
    }
  } else if (mppt->current_power < (mppt->last_power)) {
    // Otherwise, the new power value is lower than the old, the system goes the
    // opposite way compared to the last step:
    if (mppt->direction == UP) {
      mppt->duty_cycle -= mppt->step_size;
      mppt->direction = DOWN;
    } else {
      mppt->duty_cycle += mppt->step_size;
      mppt->direction = UP;
    }
    // mppt->last_power = mppt->current_power;
  }
}

void mppt_update(mppt_t *mppt, uint32_t pv_voltage_mv, uint32_t pv_current_ma) {
  // The power value is calculated based on current voltage and current.
  mppt->current_power = (pv_voltage_mv * pv_current_ma);

  hillClimb(mppt);
  // PWM variable is updated, by calling the hillClimb function, based on new
  // power calculation.

  mppt->last_power = mppt->current_power;
  // Power level history variable is updated.

  pwm_set_duty_cycle(mppt->duty_cycle, DDD6);
}
