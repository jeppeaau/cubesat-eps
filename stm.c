#include "stm.h"
#include "task.h"


void state_logic(uint8_t current_state, uint16_t config[CONFIG_SIZE])
{
	uint8_t next_state;

	switch(current_state)
	{
		case SAFE_1:
			if(exit_safe == 1)
			{
				next_state = SAFE_LITE_1;
				in_safe = 0;
			}
			else if(exit_safe == 0)
			{
				if(config[0] < battery_voltage)
				{
					next_state = SAFE_LITE_2;
					in_safe = 0;
				}
				else
				{
					next_state = SAFE_1;
					in_safe = 1;
				}
			}
			return(next_state);

		case SAFE_LITE_2:
			if(config[1] < battery_voltage)
			{
				next_state = NORMAL_3;
			}
			else if(config[2] > battery_voltage)
			{
				next_state = SAFE_1;
				in_safe = 1;
			}
			else
			{
				next_state = SAFE_LITE_2;
			}
			return(next_state);

		case NORMAL_3:
			if(config[3] > battery_voltage)
			{
				next_state = SAFE_LITE_2;
			}
			else
			{
				next_state = NORMAL_3;
			}
			return(next_state);
	}
}