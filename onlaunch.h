#pragma once

#include <avr/io.h>
#include <util/delay.h>

#define BURN_TIME_MILLIS 10000
#define BURN_PIN PD1

uint16_t power;
uint16_t power_threshold;
uint16_t power_threshold_hysteresis;

void launch_sequence();
uint8_t establish_connection();
uint8_t radio_response();  // Dummy task
void burn_wire();
