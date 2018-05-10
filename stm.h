#pragma once

#include <stdint.h>

#define CONFIG_SIZE 5

uint16_t stm_config[CONFIG_SIZE];

typedef enum { SAFE_1, SAFE_LITE_2, NORMAL_3 } state_t;

typedef struct {
  state_t next_state;
  state_t current_state;
} stm_t;

void state_logic(stm_t *stm, uint16_t battery_voltage, uint8_t exit_SAFE_1);
state_t safe(uint16_t battery_voltage, uint8_t exit_SAFE_1);
state_t safe_lite(uint16_t battery_voltage);
state_t normal(uint16_t battery_voltage);
