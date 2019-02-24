#include "../includes/Task.h"

void GO(void)
{
	static uint16 G_TICK=ZERO;
	G_TICK++;
	if(G_TICK>=1000)
	{
	DIO_WritePin(LED1,HIGH); /*GO State*/
	DIO_WritePin(LED2,LOW);
	DIO_WritePin(LED3,LOW);
	G_TICK=ZERO;
	}
	
}
void STOP(void)
{
	static uint16 G_TICK=ZERO;
	G_TICK++;
	if(G_TICK>=3000)
	{
	DIO_WritePin(LED1,LOW); /*STOP State*/
	DIO_WritePin(LED2,LOW);
	DIO_WritePin(LED3,HIGH);
	G_TICK=ZERO;
	}
}
void READY(void)
{
		static uint16 G_TICK=ZERO;
		G_TICK++;
		if(G_TICK>=2000)
		{
			DIO_WritePin(LED1,LOW); /*STOP State*/
			DIO_WritePin(LED2,HIGH);
			DIO_WritePin(LED3,LOW);
			G_TICK=ZERO;
		}
}

void (*ptr[NUMBER_OF_TASK])(void)={GO,STOP,READY};/*ARRAY OF POINTER TO FUNCTION FOR 3 TASKS GO STOP READY */


