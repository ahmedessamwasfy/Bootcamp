/*
 * Uart_App.c
 *
 * Created: 2/27/2019 1:16:34 PM
 * Author : AVE-LAP-005
 */ 

#include "Types.h"
#include "BitwiseOperations.h"
#include "DIO_Interface.h"
#include "Uart_Interface.h"


int main(void)
{
	DIO_SetPinDirection(pin13,OUTPUT);
	DIO_SetPinDirection(pin14,OUTPUT);
	/*uart initilaization*/
	UART_Init();
	while (1)
	{
	/*Check the value received from uart */	
	uint8 x=UART_Receive();
	/*if value equal to A then write high to led2*/
	if (x=='A'){
	DIO_WritePin(pin13,LOW);
	DIO_WritePin(pin14,High);	
	}
	/*if value equal to A then write high to led3*/
	if (x=='B'){
		DIO_WritePin(pin13,High);
		DIO_WritePin(pin14,LOW);
	}
	}
    
}

