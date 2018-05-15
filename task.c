#include "task.h"

void mppt_task() {
  DDRD |= (1 << DDD7);
  while (1) {
    PORTD ^= 0x80;
    // uart_putchar('m');
    // mppt_update(&mppt, pv_voltage_mv, pv_current_ma);
  }
}

void boost_converter_sensor_task() {
  while (1) {
    // uart_putchar('p');
    // pv_voltage_mv = read_voltage_mV(&boost_converter_ina);
    // pv_current_ma = read_current_mA(&boost_converter_ina);
    // k_sleep(10);
  }
}

void power_mode_stm_task() {
  while (1) {
    state_logic(&power_mode_stm, battery_voltage, exit_SAFE_1);
  }
}

void battery_control_task() {
  while (1) {
  }
}
