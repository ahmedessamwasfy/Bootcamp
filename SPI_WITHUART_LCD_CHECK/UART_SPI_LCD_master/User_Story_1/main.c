
#include "includes/Types.h"
#include "includes/BitwiseOperations.h"
#include "includes/uart.h"
#include "includes/spi.h"
#include "includes/LCD.h"

/****************************MASTER*************************/
int main(void)
{
	SPI_initMaster();/*INIT master */
	UART_Inti();/*INIT FUN FOR UART */
    LCD_init(); /* INIT LCD */
	DIO_SetPinDirection(BUTTON0,INPUT);
	DIO_SetPinDirection(BUTTON1,INPUT);
	uint8 PREV_BTN1 = 0;
	uint8 PREV_BTN0 = 0;
	uint8 data ;
	
	while(1)
	{
        #if(0)
		if(DIO_ReadPin(BUTTON1) && (PREV_BTN1 != DIO_ReadPin(BUTTON1)))
		{
			UART_Transmit('2');
			PREV_BTN1 = 1 ;
		}
		else if(DIO_ReadPin(BUTTON0) && (PREV_BTN0 != DIO_ReadPin(BUTTON0)))
		{
			UART_Transmit('1');
			PREV_BTN0 = 1 ;
		}
		#endif
		data = UART_Reseive();
		LCD_displayCharacter(data);
		SPI_sendByte(data);		
	}
	
}







