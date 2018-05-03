#include<stdint.h>
#define CONFIG_SIZE 5

typedef enum
{					// defaults starting from zero else set each enumerator equals to value
	SAFE_1,
	SAFE_LITE_2,
	NORMAL_3
} state_t;
state_t next_state;
state_t current_state;

uint16_t config[CONFIG_SIZE];
uint16_t battery_voltage;
uint16_t bootcount_24hour;
uint8_t exit_safe_1 = 0;
uint16_t pv_voltage_mv;  // used by mppt, ina needs to update this value regularly
uint16_t pv_current_ma;	// used by mppt , ina needs to update this value regularly
uint32_t global_bootcount;
uint16_t power_threshold;
uint16_t hystereses;