#include "stm.h"
#include "task.h"


void state_logic()
{
	while(1)
	{
		switch(current_state)
		{
			case SAFE_1:
				next_state = safe();
				break;

			case SAFE_LITE_2:
				next_state = safe_lite();
				break;

			case NORMAL_3:
				next_state = normal();
				break;

			default:
				break;
		}
		
		current_state = next_state;
	}
}





state_t safe() {
		if(exit_safe_1 == 1)
		{
			config[CONFIG_SIZE] = {Defalt,};   //// add all values before compiling!!!!!!
			return SAFE_LITE_1;
		} else if(exit_safe_1 == 0) {
			if(config[0] < battery_voltage)
			{
				return SAFE_LITE_2;
			} else {
				return SAFE_1;
			}
		}

	return SAFE_1;
}

state_t safe_lite(){
		if(config[1] < battery_voltage)
		{
			return NORMAL_3;
			
		}
		else if(config[2] > battery_voltage)
		{
			return SAFE_1;
			
		}
		else
		{
			return SAFE_LITE_2;
			
		}
}

state_t normal(){
				if(config[3] > battery_voltage)
				{
					return SAFE_LITE_2;
				}
				else
				{
					return NORMAL_3;
				}
		return NORMAL_3;
}




