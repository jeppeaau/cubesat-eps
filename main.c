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

  // boost_converter_ina = init_ina219(0x40, 6559, 27307);
  boost_converter_ina = init_ina219(0x40, 2047, 27307);
  // boost_converter_ina = init_ina219(0x40, 1639, 22369);
  configurate_ina219(&boost_converter_ina);
  calibrate_ina219(&boost_converter_ina);

  mppt = init_mppt(2, 0);

  uint32_t p1;
  uint32_t p2;
  uint16_t p3;
  uint16_t p4;
  uint16_t p5;

  uint32_t p_avg;

  uint8_t duty_cycle = 0;
  /*
    while (1) {
      _delay_ms(1000);
      boost_converter_sensor_task();
      p_avg = pv_current_ma * pv_voltage_mv;
      print_value((p_avg >> 20) & 0x0F);
      print_value((p_avg >> 16) & 0x0F);
      print_value((p_avg >> 12) & 0x0F);
      print_value((p_avg >> 8) & 0x0F);
      print_value((p_avg >> 4) & 0x0F);
      print_value(p_avg & 0x0F);
      uart_putchar('\n');
    }
    */

  _delay_ms(1000);

  mppt.duty_cycle = 0;

  for (int i = 0; i < 255; i++) {
    boost_converter_sensor_task();
    p_avg = pv_current_ma * pv_voltage_mv;
    print_value((p_avg >> 28) & 0x0F);
    print_value((p_avg >> 24) & 0x0F);
    print_value((p_avg >> 20) & 0x0F);
    print_value((p_avg >> 16) & 0x0F);
    print_value((p_avg >> 12) & 0x0F);
    print_value((p_avg >> 8) & 0x0F);
    print_value((p_avg >> 4) & 0x0F);
    print_value(p_avg & 0x0F);
    uart_putchar('\n');
    duty_cycle = sweep(&mppt, duty_cycle, pv_voltage_mv, pv_current_ma);
    _delay_ms(50);
  }

  mppt.duty_cycle = duty_cycle;

  pwm_set_duty_cycle(duty_cycle, DDD6);

  while (1) {
    boost_converter_sensor_task();

    // mppt_task();

    //_delay_ms(9);

    /*
        battery_sensor_task();
        battery_balancing_task();
        battery_control_task();

        power_mode_stm_task();

        subsystem_sensor_task();
        */
  }

  return 0;
}
