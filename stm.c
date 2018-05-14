#include "stm.h"

void state_logic(stm_t *stm, uint16_t battery_voltage, uint8_t exit_SAFE_1) {
  switch (stm->current_state) {
    case SAFE_1:
      stm->next_state = safe(battery_voltage, exit_SAFE_1);
      break;

    case SAFE_LITE_2:
      stm->next_state = safe_lite(battery_voltage);
      break;

    case NORMAL_3:
      stm->next_state = normal(battery_voltage);
      break;

    default:
      break;
  }

  stm->current_state = stm->next_state;
}

state_t safe(uint16_t battery_voltage, uint8_t exit_SAFE_1) {
  if (exit_SAFE_1) {
    return SAFE_LITE_2;
  } else if (!exit_SAFE_1) {
    if (stm_config[0] < battery_voltage) {
      return SAFE_LITE_2;
    } else {
      return SAFE_1;
    }
  }

  return SAFE_1;
}

state_t safe_lite(uint16_t battery_voltage) {
  if (stm_config[1] < battery_voltage) {
    return NORMAL_3;

  } else if (stm_config[2] > battery_voltage) {
    return SAFE_1;

  } else {
    return SAFE_LITE_2;
  }
}

state_t normal(uint16_t battery_voltage) {
  if (stm_config[3] > battery_voltage) {
    return SAFE_LITE_2;
  } else {
    return NORMAL_3;
  }
  return NORMAL_3;
}
