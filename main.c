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

  init_pwm(70, DDD6);

  bootcount = read_bootcount();

  if (bootcount == 0) {
    launch_sequence();
  }

  update_bootcount();

  i2c_init();

  boost_converter_ina = init_ina219(0x40, 2047, 27307);
  configurate_ina219(&boost_converter_ina);
  calibrate_ina219(&boost_converter_ina);

  battery_sensor_both_ina = init_ina219(0x41, 2047, 27307);
  battery_sensor_single_ina = init_ina219(0x42, 2047, 27307);
  configurate_ina219(&battery_sensor_both_ina);
  calibrate_ina219(&battery_sensor_both_ina);
  configurate_ina219(&battery_sensor_single_ina);
  calibrate_ina219(&battery_sensor_single_ina);

  mppt = init_mppt(1, 70);

  k_init(5, 5, 0);  // 5 tasks, 5 semaphores, 0 messaegQueues */

  boost_converter_kt = k_crt_task(boost_converter_sensor_task, TASKPRIO,
                                  boost_converter_stack, 50);
  mppt_kt = k_crt_task(mppt_task, TASKPRIO + 1, mppt_stack, 100);

  power_mode_kt =
      k_crt_task(power_mode_stm_task, TASKPRIO + 2, power_mode_stack, 50);

  battery_sensor_kt =
      k_crt_task(battery_sensor_task, TASKPRIO, battery_sensor_stack, 50);
  battery_control_kt =
      k_crt_task(battery_control_task, TASKPRIO + 1, battery_control_stack, 50);

  boost_converter_sem = k_crt_sem(0, 1);
  mppt_sem = k_crt_sem(0, 1);
  power_mode_sem = k_crt_sem(0, 1);
  battery_sensor_sem = k_crt_sem(0, 1);
  battery_control_sem = k_crt_sem(0, 1);

  k_start(1); /* start krnl timer speed 1 milliseconds*/

  return 0;
}
