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

  init_pwm(170, DDD6);

  bootcount = read_bootcount();

  if (bootcount == 0) {
    launch_sequence();
  }

  update_bootcount();

  i2c_init();

  boost_converter_ina = init_ina219(0x40, 6559, 27307);
  configurate_ina219(&boost_converter_ina);
  calibrate_ina219(&boost_converter_ina);

  mppt = init_mppt(4, 170);

  uint16_t p1;
  uint16_t p2;
  uint16_t p3;
  uint16_t p4;
  uint16_t p5;

  uint16_t p_avg;

  while (1) {
    boost_converter_sensor_task();

    /*
        p1 = pv_voltage_mv * pv_current_ma;

        _delay_ms(5);

        boost_converter_sensor_task();

        p2 = pv_voltage_mv * pv_current_ma;

        _delay_ms(5);

        boost_converter_sensor_task();

        p3 = pv_voltage_mv * pv_current_ma;

        _delay_ms(5);

        boost_converter_sensor_task();

        p4 = pv_voltage_mv * pv_current_ma;

        _delay_ms(5);

        boost_converter_sensor_task();

        p5 = pv_voltage_mv * pv_current_ma;

        _delay_ms(5);

        p_avg = (p1 + p2 + p3 + p4 + p5) / 5;
        print_value((p_avg >> 12) & 0x0F);
        print_value((p_avg >> 8) & 0x0F);
        print_value((p_avg >> 4) & 0x0F);
        print_value(p_avg & 0x0F);

        uart_putchar('\n');
        */

    mppt_task();

    _delay_ms(20);

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
