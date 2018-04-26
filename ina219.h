#include "i2cmaster.h"
// call i2c_init() in main

typedef struct {
  uint8_t addr;
  uint16_t config;
  uint16_t cal;
} ina219_t;

ina219_t init_ina219(uint8_t addr, uint16_t config, uint16_t cal);

uint16_t read_register(ina219_t *ina, uint8_t offset);
uint16_t read_voltage_mV(ina219_t *ina);
uint16_t read_current(ina219_t *ina);
uint16_t read_power(ina219_t *ina);
float read_current_mA(ina219_t *ina);

void write_register(uint8_t addr, uint8_t offset, uint16_t value);
void calibrate(uint16_t cal, uint8_t addr);
void configuration(uint16_t config, uint8_t addr);
