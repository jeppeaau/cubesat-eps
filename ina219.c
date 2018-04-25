#include "ina219.h"

void calibrate(uint16_t cal, uint8_t addr)
{	
	//Current_LSB = trunc (Maximum Expected Current/2**15)
	//cal = 0.04096/(Current_LSB * r_shunt)

	i2c_start_wait((addr << 1) & ~(0x01));				//set read/write bit to write
	i2c_write(0x05);
	i2c_write(cal >> 8); 						//writes 8 msb to i2c bus
	i2c_write(cal & 0xFF); 							// writs 8 lsb to i2c bus
	i2c_stop();
} 

void configuration(uint16_t config, uint8_t addr)
{
	i2c_start_wait((addr << 1) & ~(0x01));
	i2c_write(0x00);
	i2c_write(config >> 8); 					//writes 8 msb to i2c bus
	i2c_write(config);
	i2c_stop(); 

}

uint16_t read_register(uint8_t addr, uint8_t offset)
{
	uint16_t reg;
	i2c_start_wait((addr << 1) & ~(0x01));
	i2c_write(offset);
	i2c_rep_start((addr << 1) | 0x01);			
	reg = i2c_readAck();
	reg = (reg << 8) | i2c_readNak();
	i2c_stop();
	return reg;	
}


uint16_t read_voltage(uint8_t addr)
{
	return read_register(addr, 0x02);
}


uint16_t read_current(uint8_t addr)
{
	return read_register(addr, 0x04);
}


uint16_t read_power(uint8_t addr)
{
	return read_register(addr, 0x03);
}