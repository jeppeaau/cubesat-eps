#include "i2cmaster.h"

typedef struct {
    uint8_t addr;
    uint8_t config;
} tmp101_t;

tmp101_t init_tmp101(uint8_t addr, uint8_t config);

void write_register_tmp101(tmp101_t *tmp, uint8_t value, uint8_t offset);
uint16_t read_register_tmp101(tmp101_t *tmp, uint8_t offset);

void configurate_tmp101(tmp101_t *tmp);
uint8_t read_temperature(tmp101_t *tmp);
