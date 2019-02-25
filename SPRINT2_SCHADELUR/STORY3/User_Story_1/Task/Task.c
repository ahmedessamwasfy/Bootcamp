#include "../includes/Task.h"
#include <util/delay.h>
void GO(void)
{
	DIO_WritePin(LED1,HIGH); /*GO State*/
	DIO_WritePin(LED2,LOW);
	DIO_WritePin(LED3,LOW);	

}
void STOP(void)
{
	DIO_WritePin(LED1,LOW); /*STOP State*/
	DIO_WritePin(LED2,LOW);
	DIO_WritePin(LED3,HIGH);	

}
void READY(void)
{	
	DIO_WritePin(LED1,LOW); /*STOP State*/
    DIO_WritePin(LED2,HIGH);
	DIO_WritePin(LED3,LOW);	

}

void (*ptr[NUMBER_OF_TASK])(void)={GO,STOP,READY};/*ARRAY OF POINTER TO FUNCTION FOR 3 TASKS GO STOP READY */


