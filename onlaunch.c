#include "onlaunch.h"

uint32_t bootcount(uint8_t function)
{
    //do some uart stuff to improt the actual bootcount from eprom
    uint32_t bootcount_import = 0; // This is a dummy variable.

    if(function == 1) // Add 1 and then return current bootcount
    {
        bootcount++;
        //Write the new bootvalue to eprom:
        return bootcount;
    }
    else if(function == 2) // subtract 1 and then return current bootcount
    {
        bootcount--;    
        //Write the new bootvalue to eprom:
        return bootcount;
    }
    else
    {
        return  bootcount;
    }
}

uint8_t establish_connection()
{
    while(power >= power_threshold && !radio_response())
    {
        burn_wire();
    }

    return power >= power_threshold;
}

void launch_sequence()
{
    uint8_t response;

    while(1) {
        response = establish_connection();

        if (response) {
            return;
        } else {
            while(power < power_threshold + hystereses);
        }
    }
}

void burn_wire()
{
    //sets pin high, fet turned on when burning
    PORTD |= (1 << BURN_PIN_PORTD); // Sets BURN_PIN_PORTD pin high
    _delay_ms(BURN_TIME_MILLIS);
    PORTD &= ~(1 << BURN_PIN_PORTD); // Sets BURN_PIN_PORTD pin low 
}

uint8_t radio_response()
{
    //sends beakons in interval and waits for response
    _delay_ms(10000);
    return 1;
}

