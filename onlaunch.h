#include <avr/io.h>
#define BURN_TIME_MILLIS 10000;
#define BURN_PIN_PORTD PD1;

uint32_t bootcount(uint8_t function); // Takes values  1 and 2 for add and subtract one all other values retuns unchanged bootcount
void launch_sequence();
uint8_t establish_connection();
uint8_t radio_response();  //Dummy talsk
void burn_wire();