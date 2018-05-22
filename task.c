#include "task.h"
#include "krnl.h"

void mppt_task() {
  uint32_t cnt = 0;
  uint8_t i = 0;
  uint8_t duty_cycle = 0;
  k_set_sem_timer(mppt_sem, 12);
  while (1) {
    k_wait(mppt_sem, 0);
    if (cnt < 2500) {
      mppt_update(&mppt, pv_voltage_mv, pv_current_ma);
      cnt++;
    } else if (i < 255) {
      if (i == 0) {
        mppt.duty_cycle = 0;
      }
      duty_cycle = sweep(&mppt, duty_cycle, pv_voltage_mv, pv_current_ma);
      i += 5;
    } else {
      mppt.duty_cycle = duty_cycle;
      pwm_set_duty_cycle(duty_cycle, DDD6);
      i = 0;
      cnt = 0;
    }
  }
}

void boost_converter_sensor_task() {
  k_set_sem_timer(boost_converter_sem, 12);
  while (1) {
    k_wait(boost_converter_sem, 0);
    pv_voltage_mv = (uint32_t)read_voltage_mV(&boost_converter_ina);
    pv_current_ma = (uint32_t)read_current_mA(&boost_converter_ina);
  }
}

void power_mode_stm_task() {
  k_set_sem_timer(power_mode_sem, 64);
  while (1) {
    k_wait(power_mode_sem, 0);
    state_logic(&power_mode_stm, battery_voltage_both, exit_SAFE_1);
  }
}

void battery_sensor_task() {
  k_set_sem_timer(battery_sensor_sem, 40);
  while (1) {
    k_wait(battery_sensor_sem, 0);
    battery_voltage_both = read_voltage_mV(&battery_sensor_both_ina);
    battery_voltage_single = read_voltage_mV(&battery_sensor_single_ina);
  }
}

void battery_control_task() {
  DDRD |= (1 << PD7) | (1 << PD6);
  int32_t battery_voltage_delta;
  k_set_sem_timer(battery_control_sem, 40);
  while (1) {
    k_wait(battery_control_sem, 0);
    battery_voltage_delta = battery_voltage_both - 2 * battery_voltage_single;

    if (battery_voltage_delta >= 30 || battery_voltage_delta <= -30) {
      PORTD |= (1 << PD7) | (1 << PD6);
    } else if (battery_voltage_delta <= 5 || battery_voltage_delta >= -5) {
      PORTD &= ~((1 << PD7) | (1 << PD6));
    }
  }
}
