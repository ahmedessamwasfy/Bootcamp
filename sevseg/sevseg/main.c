#include "BitwiseOperations.h"
#include "Types.h"
#include "sevseg.h"
#include "DIO.h"
#include <util/delay.h>


int main()
{
	DIO_SetPinDirection(DATA_PINA,output);
	DIO_SetPinDirection(DATA_PINB,output);
	DIO_SetPinDirection(DATA_PINC,output);
	DIO_SetPinDirection(DATA_PIND,output);
	
	DIO_SetPinDirection(enable_pin_7seg_1,output);
	DIO_SetPinDirection(enable_pin_7seg_2,output);
	DIO_SetPinDirection(enable_pin_7seg_3,output);
	DIO_SetPinDirection(enable_pin_7seg_4,output);
	
	while(1)
	{
		BCDSevegments_enable(enable_pin_7seg_2);
		BCDSevegments_disable(enable_pin_7seg_3);
		BCDSevegments_disable(enable_pin_7seg_1);
		BCDSevegments_disable(enable_pin_7seg_4);
		BCDSevegments_displayNo(8);
		_delay_ms(5);
	}
	return 0;
}