#include <avr/io.h>
#include <stdint.h>


void PWM(uint8_t DT, uint8_t pin)
{
    DDRD |= (1 << pin);
        // Pin D6

    OCR0A = DT;  // Output Compare Register
        // set PWM for between 0-255

    TCCR0A |= (1 << COM0A1);
        // set none-inverting mode
        // when it reaches 255 it overflows to 0 in none-inverting mode

    TCCR0A |= (1 << WGM01) | (1 << WGM00);
        // set fast PWM Mode
    
    TCCR0B |= (1 << CS00);
        /*
        set prescaler to 8 and starts PWM
        frequency = (16mhz/255)*(1/x)   where x is the prescaler
        example1 TCCR0B |= (1 << CS00)|(1 << CS02); will have a prescaler of Clock / 1024
        example2 TCCR0B |= (1 << CS00); no prescaling
          CS02 CS01 CS00 DESCRIPTION
            0   0   0    Timer/Counter2 Disabled 
            0   0   1    No Prescaling
            0   1   0    Clock / 8
            0   1   1    Clock / 64
            1   0   0    Clock / 256
            1   0   1    Clock / 1024
        */
}



void main()
{
    uint8_t Duty = 182;
    uint8_t pin = DDD6;
    PWM(Duty, pin);
}
