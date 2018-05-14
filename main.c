#include <avr/eeprom.h>
#include <util/delay.h>
#include "adc.h"
#include "i2cmaster.h"
#include "krnl.h"
#include "onlaunch.h"
#include "pwm.h"
#include "task.h"
#include "uart.h"

#define BAUD 9600
#define BAUDRATE ((F_CPU) / (BAUD * 16UL) - 1)

char boost_converter_ina_stack[50];
char mppt_stack[100];

void update_bootcount() { bootcount++; }
uint32_t read_bootcount() { return bootcount; }

int main() {
  init_pwm(175, DDD6);

  bootcount = read_bootcount();

  if (bootcount == 0) {
    launch_sequence();
  }

  update_bootcount();

  i2c_init();

  boost_converter_ina = init_ina219(0x40, 6559, 27307);
  configurate_ina219(&boost_converter_ina);
  calibrate_ina219(&boost_converter_ina);

  mppt = init_mppt(5, 175);

  k_crt_task(boost_converter_sensor_task, 1, boost_converter_ina_stack, 25);
  k_crt_task(mppt_task, 1, mppt_stack, 50);

  // init krnl so you can create 2 tasks, no semaphores and no message
  // queues
  k_init(2, 0, 0);

  return 0;
}
