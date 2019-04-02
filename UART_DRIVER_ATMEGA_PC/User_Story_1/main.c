
#include "includes/Types.h"
#include "includes/BitwiseOperations.h"
#include "includes/uart.h"


int main(void)
{
	DIO_SetPinDirection(BUTTON0,INPUT);
	DIO_SetPinDirection(BUTTON1,INPUT);
	DIO_SetPinDirection(11,OUTPUT);
	uint8 data ;
	uint8 array[4] = {'A','T','\r','\n'};
	UART_Inti();/*INIT FUN FOR UART */
	while(1)
	{
		UART_Send_String(array,4);
		
		/*
		data = UART_Reseive();
		if(data == '2')
		{
		 DIO_WritePin(11,LOW);
		}
		else if(data == '3')
		{
	     DIO_WritePin(11,HIGH);
		}*/
	}
    
}
	

		
	 



