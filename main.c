#include <avr/eeprom.h>
#include <util/delay.h>
#include "adc.h"
#include "i2cmaster.h"
#include "krnl.h"
#include "onlaunch.h"
#include "pwm.h"
#include "task.h"
#include "uart.h"

void update_bootcount() { bootcount++; }
uint32_t read_bootcount() { return 1; }

int main() {
  uart_init();

  init_pwm(0, DDD6);

  bootcount = read_bootcount();

  if (bootcount == 0) {
    launch_sequence();
  }

  update_bootcount();

  i2c_init();

  // boost_converter_ina = init_ina219(0x40, 6559, 27307);
  boost_converter_ina = init_ina219(0x40, 2047, 27307);
  // boost_converter_ina = init_ina219(0x40, 1639, 22369);
  configurate_ina219(&boost_converter_ina);
  calibrate_ina219(&boost_converter_ina);

  mppt = init_mppt(1, 0);

  k_init(3, 3, 0);  // 3 tasks, 3 semaphores, 0 messaegQueues */

  boost_converter_kt = k_crt_task(boost_converter_sensor_task, TASKPRIO,
                                  boost_converter_stack, 50);

  mppt_kt = k_crt_task(mppt_task, TASKPRIO + 1, mppt_stack, 100);

  power_mode_kt =
      k_crt_task(power_mode_stm_task, TASKPRIO + 2, power_mode_stack, 50);

  boost_converter_sem = k_crt_sem(0, 1);
  mppt_sem = k_crt_sem(0, 1);
  power_mode_sem = k_crt_sem(0, 1);

  k_start(1); /* start krnl timer speed 1 milliseconds*/

  return 0;
}
