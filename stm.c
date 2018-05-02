#include "stm.h"
#include "task.h"


void state_logic(uint8_t current_state, uint16_t config[config_size]){
	uint8_t next_state;
	uint8_t timer;
	


	switch(current_state){
		case release_01:
			if(timer =< 50 || battery_voltage =< config[0]){ // 50 is min
				next_state = release_01;
			}
			else if (timer > 50 || battery_voltage > config[0]){
				next_state = antenna_deploy_02;
			}
			return next_state;

		case antenna_deploy_02:
			if (antenna_check = FALSE){
				next_state = antenna_deploy_02;
			}
			else if(antenna_check == TRUE){
				next_state = safe_1;
			}
			return next_state;

		case safe_1:
			if (battery_voltage >= config[1])
			{
				/* code */
			}

			return next_state;

		case safe_lite_2:

			return next_state;

		case normal_3:

			return next_state;


	}
}

bool antenna_check(){
	//this is a dummy function
	return TRUE;
}