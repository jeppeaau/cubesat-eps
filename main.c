#include <avr/eeprom.h>
#include <util/delay.h>
#include "adc.h"
#include "i2cmaster.h"
#include "krnl.h"
#include "onlaunch.h"
#include "pwm.h"
#include "task.h"
#include "uart.h"

char boost_converter_ina_stack[25];
char mppt_stack[100];

void update_bootcount() { bootcount++; }
uint32_t read_bootcount() { return 1; }

int main() {
  uart_init();

  // init_pwm(175, DDD6);

  bootcount = read_bootcount();

  if (bootcount == 0) {
    launch_sequence();
  }

  // update_bootcount();

  // i2c_init();

  // boost_converter_ina = init_ina219(0x40, 6559, 27307);
  // configurate_ina219(&boost_converter_ina);
  // calibrate_ina219(&boost_converter_ina);

  // mppt = init_mppt(5, 175);

  // init krnl so you can create 2 tasks, no semaphores and no message
  // queues
  k_init(2, 0, 0);

  struct k_t *task1 = k_crt_task(boost_converter_sensor_task, 12,
                                 boost_converter_ina_stack, 25);
  struct k_t *task2 = k_crt_task(mppt_task, 11, mppt_stack, 100);

  k_start(10);

  uart_putchar('n');

  return 0;
}
