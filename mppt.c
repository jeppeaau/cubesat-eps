#include "mppt.h"

// Hillclimb algorithm function that takes Power history and current power, stepsize and current modulation level (PWM).
// The algorithm chooses whether to continue moving in the same direction.
// Returns the updated PWM value.
uint16_t hillClimb ( float lastPower, float currentPower, uint16_t stepSize, uint8_t PWM, uint8_t *Direction ){


		if(currentPower >= lastPower){
    // If the new power value is higher than or equal the old:
			if(*Direction == 1){
      // the system continues going up:
			PWM = PWM + stepSize;
			*Direction = 1;
			}
			else {
      // or continues going down:
				PWM = PWM - stepSize;
				*Direction = 0;
			}
		}
		else {
    // Otherwise, the new power value is lower than the old, the system goes the opposite way compared to the last step:
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
  // The function returns the updated PWM value.
}


void mppt(){

  // initialization of variables:
  uint16_t LastPower = 0;
  uint8_t modulation = 175;
  uint8_t pin = DDD6;
  uint16_t stepSize = 5;
  uint8_t direction = 1;

    DDRD |= (1 << pin);
    // PD6 is now an output

    OCR0A = modulation;
    // set PWM for duty cycle

    TCCR0A |= (1 << COM0A1);
    // set none-inverting mode

    TCCR0A |= (1 << WGM01) | (1 << WGM00);
    // set fast PWM Mode

    TCCR0B |= (1 << CS02);
    // set prescaler to 256 and starts PWM


   while (1)
   {
      OCR0A = modulation;
      // PWM output level is updated

      uint16_t currentPower = pv_voltage_mV * pv_current_mA;
      // The power value is calculated based on current voltage and current.

      modulation = hillClimb(LastPower, currentPower, stepSize, modulation, &direction);
      // PWM variable is updated, by calling the hillClimb function, based on new power calculation.

      LastPower = currentPower;
      // Power level history variable is updated.
    }
}