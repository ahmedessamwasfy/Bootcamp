
#include "includes/Types.h"
#include "includes/BitwiseOperations.h"
#include "includes/uart.h"
#include "includes/LCD.h"
#include "Free_RTOS/FreeRTOS.h"
#include "Free_RTOS/task.h"
#include "includes/spi.h"


/******************SLAVE*********************/
int main()
{
	LCD_init();/* LCD INIT */
	_delay_ms(60);
	DIO_SetPinDirection(BUZZER,OUTPUT);/*BUZZER INIT to check */
	SPI_initSlave();/* INIT SPI as slave */
    uint8 data=0; /* Variable to store SPI receive */
	LCD_displayCharacter('A');
	while(1)
	{
		data=SPI_recieveByte();
		if(data==SWITCH_PRESSED)
		{
			LCD_displayCharacter('F');
		}
		else if(data == SWITCH_NOT_PRESSED)
		{
			LCD_displayCharacter('L');
		}
	}
}

		
	 



