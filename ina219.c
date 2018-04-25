#include "ina219.h"


void write_register(uint8_t addr, uint8_t offset, uint16_t value)
{
	i2c_start_wait((addr << 1) & ~(0x01));				//set read/write bit to write
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

	write_register(addr, 0x05, cal << 1);
} 

void configuration(uint16_t config, uint8_t addr)
{
	write_register(addr, 0x00, config);
}

uint16_t read_register(uint8_t addr, uint8_t offset)
{
	uint16_t reg;
	i2c_start_wait((addr << 1) & ~(0x01));
	i2c_write(offset);
	i2c_rep_start((addr << 1) | 0x01);			
	reg = i2c_readAck();
	reg = (reg << 8)| i2c_readNak();
	i2c_stop();
	return reg;	
}


uint16_t read_voltage_mV(uint8_t addr)
{
	return 4 * (read_register(addr, 0x02) >> 3);

}


uint16_t read_current(uint8_t addr)
{
	return read_register(addr, 0x04);
}


uint16_t read_power(uint8_t addr)
{
	return read_register(addr, 0x03);
}