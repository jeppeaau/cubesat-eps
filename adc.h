#pragma once

#include <avr/io.h>
#include <stdint.h>

void adc_init();

void analog_read_setpin(uint8_t pin);

uint16_t analog_read();
