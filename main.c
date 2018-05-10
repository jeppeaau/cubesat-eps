#include <avr/eeprom.h>
#include <util/delay.h>
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
  bootcount = read_bootcount();

  if (bootcount == 0) {
    launch_sequence();
  }

  update_bootcount();

  init_pwm(175, DDD6);

  ina219_t boost_converter_ina = init_ina219(0x40, 6559, 27307);

  mppt = init_mppt(5, 175);

  i2c_init();

  k_crt_task(boost_converter_sensor_task, 1, boost_converter_ina_stack, 50);
  k_crt_task(mppt_task, 2, mppt_stack, 100);

  // init krnl so you can create 2 tasks, no semaphores and no message
  // queues
  k_init(2, 0, 0);

  return 0;
}
