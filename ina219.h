#include "i2cmaster.h"
// call i2c_init() in main 

uint16_t read_register(uint8_t addr, uint8_t offset);

uint16_t read_voltage(uint8_t addr);
uint16_t read_current(uint8_t addr);
uint16_t read_power(uint8_t addr);
void calibrate(uint16_t cal, uint8_t addr);
void configuration(uint16_t config, uint8_t addr);
