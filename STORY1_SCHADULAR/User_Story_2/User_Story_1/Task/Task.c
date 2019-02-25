#include "../includes/Task.h"

void (*ptr[NUMBER_OF_TASK])(void)={GO,STOP,READY};/*ARRAY OF POINTER TO FUNCTION FOR 3 TASKS GO STOP READY */



/*GO*/
/* Parameters : N/A */
/* I/p : N/A */
/* O/p : N/A */
/* Return : void */
/* Function that perform task1 which is GO LED1 HIGH   */
void GO(void)
{
	static uint16 G_TICK;
	/*each time the prefield call the three task every one 
	sec in one shoot and here i increment the G_TICK flag every time every 1 sec and when this 
	flag is equal the required time (period )thats mean its time to perform this task */
	
	G_TICK++;/*increment G_TICK */
	if(G_TICK>=ONE_SECOUND)/*CHECK G_TICK == REQUIRD TIME EXCUTE THIS TASK */
	{
	DIO_WritePin(LED1,HIGH); /*GO State*/
	DIO_WritePin(LED2,LOW);
	DIO_WritePin(LED3,LOW);
	G_TICK=ZERO;/* clear the flag after executed this task */
	}
	
}


/*GO*/
/* Parameters : N/A */
/* I/p : N/A */
/* O/p : N/A */
/* Return : void */
/* Function that perform task1 which is STOP LED1 HIGH   */
void STOP(void)
{
	static uint16 G_TICK;
	/*each time the prefield call the three task every one 
	sec in one shoot and here i increment the G_TICK flag every time every 1 sec and when this 
	flag is equal the required time (period )thats mean its time to perform this task */
	G_TICK++;
	if(G_TICK>=THREE_SECOUND)
	{
	DIO_WritePin(LED1,LOW); /*STOP State*/
	DIO_WritePin(LED2,LOW);
	DIO_WritePin(LED3,HIGH);
	G_TICK=ZERO;/* clear the flag after executed this task */
	}
}


/*READY*/
/* Parameters : N/A */
/* I/p : N/A */
/* O/p : N/A */
/* Return : void */
/* Function that perform task1 which is READY LED1 HIGH   */
void READY(void)
{
	    static uint16 G_TICK;
		/*each time the prefield call the three task every one 
	   sec in one shoot and here i increment the G_TICK flag every time every 1 sec  and when this 
	   flag is equal the required time (period )thats mean its time to perform this task */
		G_TICK++;
		if(G_TICK>=TWO_SECOND)
		{
			DIO_WritePin(LED1,LOW); /*STOP State*/
			DIO_WritePin(LED2,HIGH);
			DIO_WritePin(LED3,LOW);
			G_TICK=ZERO;/* clear the flag after executed this task */
		}
}

