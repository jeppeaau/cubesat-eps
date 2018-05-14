#pragma once

#include <stdint.h>
#include "ina219.h"
#include "mppt.h"
#include "stm.h"
#include "uart.h"

#define CONFIG_SIZE 5

uint16_t battery_voltage;

uint32_t bootcount;
uint16_t bootcount_24hour;

uint8_t exit_SAFE_1;

// used by mppt, ina needs to update this value regularly
uint16_t pv_voltage_mv;

// used by mppt , ina needs to update this value regularly
uint16_t pv_current_ma;

stm_t power_mode_stm;
ina219_t boost_converter_ina;
mppt_t mppt;

void mppt_task();
void battery_sensor_task();
void boost_converter_sensor_task();
void subsystem_sensor_task();
void send_data();
void power_mode_stm_task();
void battery_balancing_task();
void battery_control_task();
void logging_task();
