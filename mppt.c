#include "mppt.h"

//hillclimb algorithm that 
uint16_t hillClimb ( float lastPower, float currentPower, uint16_t stepSize, uint8_t PWM, uint8_t *Direction ){


		if(currentPower >= lastPower){
			if(*Direction == 1){
			PWM = PWM + stepSize;
			*Direction = 1;
			}
			else {
				PWM = PWM - stepSize;
				*Direction = 0;
			}
		}
		else {
				if(*Direction == 1){
			PWM = PWM - stepSize;
			*Direction = 0;
			}
			else {
				PWM = PWM + stepSize;
				*Direction = 1;
			}
}


	return PWM;

}


void mppt(){

  uint16_t LastPower = 0;
  uint8_t brightness = 175;
  uint8_t pin = DDD6;
  uint16_t stepSize = 5;
  uint8_t direction = 1;

    DDRD |= (1 << pin);
    // PD6 is now an output

    OCR0A = brightness;
    // set PWM for duty cycle

    TCCR0A |= (1 << COM0A1);
    // set none-inverting mode

    TCCR0A |= (1 << WGM01) | (1 << WGM00);
    // set fast PWM Mode

    TCCR0B |= (1 << CS02);
    // set prescaler to 256 and starts PWM


   while (1)
   {
      OCR0A = brightness;
      uint16_t currentPower = pv_voltage_mV * pv_current_mA;

      brightness = hillClimb(LastPower, currentPower, stepSize, brightness, &direction);

      LastPower = currentPower;
    }
}