
#include "includes/Types.h"
#include "includes/BitwiseOperations.h"
#include "includes/uart.h"
#include "includes/DIO.h"
#include <avr/delay.h>


int main(void)
{
	DIO_SetPinDirection(BUTTON1,INPUT);/*set pin 10 button1 as input */
	DIO_SetPinDirection(BUTTON0,INPUT);/*set pin 20 button0 as input */
	UART_Inti();/*INIT FUN FOR UART */
	while(ONE)
	{
	  if(DIO_ReadPin(BUTTON1) && (~DIO_ReadPin(BUTTON0)))/*CHECK IF BUTTON 1 IS PRESSED SEND ZERO */
	  {
		  	  UART_Transmit('A');/*if button 1 is pressed send char A */
			_delay_ms(QUARTER_SECOND);
	  }
	  else if(DIO_ReadPin(BUTTON0) && (~DIO_ReadPin(BUTTON1)))/*CHECK IF BUTTON 0 IS PRESSED SEND ONE */
	  {
		      UART_Transmit('B');/*if button 0 is pressed send char B */
             _delay_ms(QUARTER_SECOND);
	  }

	}
    
}
	

		
	 



