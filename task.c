#include "task.h"

void mppt_task() { mppt_update(&mppt, pv_voltage_mv, pv_current_ma); }

void boost_converter_sensor_task() {
  pv_voltage_mv = (uint32_t)read_voltage_mV(&boost_converter_ina);
  pv_current_ma = (uint32_t)read_current_mA(&boost_converter_ina);
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
