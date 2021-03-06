#include "ina219.h"

#include <util/delay.h>

ina219_t init_ina219(uint8_t addr, uint16_t config, uint16_t cal) {
  return (ina219_t){addr << 1, config, cal << 1};
}

void write_register_ina219(ina219_t *ina, uint8_t offset, uint16_t value) {
  i2c_start_wait(ina->addr & ~(0x01));  // set read/write bit to write
  i2c_write(offset);
  i2c_write(value & 0xFF);  // writs 8 lsb to i2c bus
  i2c_write(value >> 8);    // writes 8 msb to i2c bus
  i2c_stop();
}

void calibrate_ina219(ina219_t *ina) {
  // Current_LSB = trunc (Maximum Expected Current/2**15)
  // cal = 0.04096/(Current_LSB * r_shunt)
  //
  // Calculations used
  // Current_LSB =(3/2**15)
  // cal = 0.04096/(0.000091552734375 * 0.015)
  // cal = 29826;

  write_register_ina219(ina, 0x05, ina->cal);
}

void configurate_ina219(ina219_t *ina) {
  write_register_ina219(ina, 0x00, ina->config);
}

uint16_t read_register_ina219(ina219_t *ina, uint8_t offset) {
  uint16_t reg;
  i2c_start_wait(ina->addr & ~(0x01));
  i2c_write(offset);
  i2c_stop();
  _delay_ms(5);
  i2c_rep_start(ina->addr | 0x01);
  reg = i2c_readAck();
  reg = (reg << 8) | i2c_readNak();
  i2c_stop();
  return reg;
}

uint16_t read_voltage_mV(ina219_t *ina) {
  uint16_t voltage = read_register_ina219(ina, 0x02);
  if ((voltage & 0x01) || !(voltage & 0x02)) {
    return 0;
  }

  return 4 * (voltage >> 3);
}

uint16_t read_current(ina219_t *ina) {
  uint16_t current = read_register_ina219(ina, 0x04);

  if (current & 0x8000) {
    return 0;
  }

  return current;
}

float read_current_mA(ina219_t *ina) {
  // curr_lsb = max_expected_current/2**15
  return 1.22 * ((read_current(ina) * 0.1));
}

uint16_t read_power(ina219_t *ina) { return read_register_ina219(ina, 0x03); }
