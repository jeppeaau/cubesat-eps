#include "tmp101.h"

tmp101_t init_tmp101(uint8_t addr, uint8_t config)
{
    return (tmp101_t) {addr << 1, config};
}

void write_register_tmp101(tmp101_t *tmp, uint8_t value, uint8_t offset)
{
    i2c_start_wait(tmp->addr & (~0x01));
	i2c_write(offset);
	i2c_write(value);
	i2c_stop();
}

uint16_t read_register_tmp101(tmp101_t *tmp, uint8_t offset)
{
    uint16_t reg;
	i2c_start_wait(tmp->addr & (~0x01));
	i2c_write(offset);
	i2c_rep_start(tmp->addr | 0x01);
	reg = i2c_readAck();
    reg = (reg << 8) | i2c_readNak();
	i2c_stop();
	return reg;
}

void configurate_tmp101(tmp101_t *tmp)
{
    write_register_tmp101(tmp, tmp->config, 0x01);
}

uint8_t read_temperature(tmp101_t *tmp)
{
    return read_register_tmp101(tmp, 0x00) >> 8;
}
