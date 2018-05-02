#include <avr/io.h>             /* for DDRB, PORTB, etc. */
#include <util/delay.h>         /* for _delay_ms () */
#include <stdio.h>


uint16_t hillClimb ( float lastPower, float currentPower, uint16_t stepSize, uint8_t PWM, uint8_t *Direction );
float Power(uint8_t PWM); //simulates inputpower reading
