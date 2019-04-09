
#ifndef TEMPSENSOR_CFG_H_
#define TEMPSENSOR_CFG_H_

typedef struct TempSensors_config{
	uint8 SensorID; /* Sensor ID*/
	uint8 SensorOutput; /*Sensor milliVolt output per degree celesius.*/
	uint8 SensorMax; /*max degree celesius*/
	sint8 SensorMin; /*min degree celesius*/
}TempSensors_config_t;

#define MAX_TEMP_SENSORS 1

#define VREF  (5U) /* 5 Volt for Target Atmega32 */

#if (ADC_RESOLUTION_MODE == EightBitResolution)
#define RESOLUTION_MODE (254U)
#else
#define RESOLUTION_MODE (1023U)
#endif

#define VOLT_TO_MVOLT (1000U)
#define FOURTY_CEL_DEGREE 40
#define TEN 10
#endif /* TEMPSENSOR_CFG_H_ */