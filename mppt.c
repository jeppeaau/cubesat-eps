#include "mppt.h"

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


float Power(uint8_t PWM){
	return -(PWM * PWM)/30 + 9 * PWM;
}



/*
void main()
{
	uint8_t brightness = 175;
	uint8_t pin = DDD6;
	uint8_t Amount = 1;
	float LastPower = 0;
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
    	float CurrentPower = Power(brightness);
    	
    	//if (brightness <= 10 || brightness >= 245) {
    	//fadeAmount = -fadeAmount;
  		//}
  		//if (brightness <= 100){
  		//_delay_ms (15);
  		//}
  		//if (brightness <= 50){
  		//_delay_ms (50);
  		//}
  		//_delay_ms (20);

  		brightness = hillClimb(LastPower, CurrentPower, 5, brightness, &direction);

  		_delay_ms (1000);

  		OCR0A = 135;

  		_delay_ms (1000);

  		LastPower = CurrentPower;
    }
}
/*

