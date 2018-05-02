#define CONFIG_SIZE 5
#define TRUE 1
#define FALSE 0

enum states
{					// defaults starting from zero else set each enumerator equals to value
	RELEASE_01,
	ANTENNA_DEPLOY_02,
	SAFE_1,
	SAFE_LITE_2,
	NORMAL_3
};
					// batteryVoltageThreshold | antennaburne | 
uint16_t config[CONFIG_SIZE] = {8000,,}; // all values in mili(V,A,P)

bool antenna_check(); // dummy function
