#include "../includes/DIO.h"
#include "../includes/Types.h"
#include "../includes/BitwiseOperations.h"
#include "../includes/TempSensor.h"
#include "../includes/ADC.h"
extern TempSensors_config_t TempSensor_arr[MAX_TEMP_SENSORS];


/*TempSensor_ReadValue */
/* Parameters : uint8  */
/* I/p : void , void  */
/* O/p : N/A */
/* Return : uint8 */
/* Function that read temp sendor value   */
uint8 TempSensor_ReadValue( uint8 TempSensor)
{
	double TempDegree = 0 ;
	TempDegree = (double)( ADC_StartConversion(TempSensor_arr[TempSensor].SensorID) * VREF)/RESOLUTION_MODE;
	TempDegree *=VOLT_TO_MVOLT;
	TempDegree /=TempSensor_arr[TempSensor].SensorOutput;
	return (uint8)TempDegree;
}