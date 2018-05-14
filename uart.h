#include <avr/io.h>

#define BAUD 9600
#define BAUDRATE ((F_CPU) / (BAUD * 16UL) - 1)

void print_value(uint8_t val);
void uart_putchar(char c);
void uart_init();
