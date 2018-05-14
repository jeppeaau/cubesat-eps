#include "adc.h"

void adc_init() {
  ADCSRA |= ((1 << ADPS2) | (1 << ADPS1) |
             (1 << ADPS0));  // Set prescaler bits in ADCSRA(ADC control and
                             // status register A)

  ADMUX |= (1 << REFS0);
  ADMUX &= ~(1 << REFS1);  // Set mode: (Set reference voltage to 5V input)

  ADCSRB &= ~(
      (1 << ADTS2) | (1 << ADTS1) |
      (1 << ADTS0));  // Set free running mode in control and status register B
  ADMUX = (ADMUX & 0xF0) | (0x00);  // Set default reading pin(Analog 0)

  ADCSRA |= (1 << ADATE);  // Enable auto trigger
  ADCSRA |= (1 << ADEN);   // Enable ADC power supply
  ADCSRA |= (1 << ADSC);   // Start first conversion(will run automatically from
                           // then on.)
}

void analog_read_setpin(uint8_t pin) {
  ADMUX = (ADMUX & 0xF0) | (pin & 0x0F);  // Select ADC channel safely
}

uint16_t analog_read() { return ADC; }
