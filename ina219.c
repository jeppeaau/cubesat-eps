#include "ina219.h"

ina219_t init_ina219(uint8_t addr, uint16_t config, uint16_t cal)
{
	return (ina219_t) {addr << 1, config, cal << 1};
}

void write_register(uint8_t addr, uint8_t offset, uint16_t value)
{
	i2c_start_wait((addr) & ~(0x01));				//set read/write bit to write
	i2c_write(offset);
	i2c_write(value & 0xFF); 							// writs 8 lsb to i2c bus
	i2c_write(value >> 8); 								//writes 8 msb to i2c bus
	i2c_stop();
}

void calibrate(uint16_t cal, uint8_t addr)
{
	//Current_LSB = trunc (Maximum Expected Current/2**15)
	//cal = 0.04096/(Current_LSB * r_shunt)
	//
	// Calculations used
	//Current_LSB =(3/2**15)
	//cal = 0.04096/(0.000091552734375 * 0.015)
	//cal = 29826;

	write_register(addr, 0x05, cal);
}

void configuration(uint16_t config, uint8_t addr)
{
	write_register(addr, 0x00, config);
}

uint16_t read_register(ina219_t *ina, uint8_t offset)
{
	uint16_t reg;
	i2c_start_wait(ina->addr & ~(0x01));
	i2c_write(offset);
	i2c_rep_start(ina->addr | 0x01);
	reg = i2c_readAck();
	reg = (reg << 8)| i2c_readNak();
	i2c_stop();
	return reg;
}


uint16_t read_voltage_mV(ina219_t *ina)
{
	return 4 * (read_register(ina, 0x02) >> 3);
}


uint16_t read_current(ina219_t *ina)
{
	return (read_register(ina, 0x04));
}

float read_current_mA(ina219_t *ina)
{
	// curr_lsb = max_expected_current/2**15
	return 1.22 * (read_current(ina) * 1.0 / 10);
}

uint16_t read_power(ina219_t *ina)
{
	return read_register(ina, 0x03);
}
