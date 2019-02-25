#include "../includes/Task.h"

/* GO */
/* Parameters : N/A */
/* I/p : N/A */
/* O/p : N/A */
/* Return : void */
/* Function that initialize GO LED IN STATE MACHINE  */

void GO(void)
{
	DIO_WritePin(LED1,HIGH); /*GO State*/
	DIO_WritePin(LED2,LOW);
	DIO_WritePin(LED3,LOW);
	
}

/* STOP */
/* Parameters : N/A */
/* I/p : N/A */
/* O/p : N/A */
/* Return : void */
/* Function that initialize STOP LED IN STATE MACHINE  */
void STOP(void)
{
	DIO_WritePin(LED1,LOW); /*STOP State*/
	DIO_WritePin(LED2,LOW);
	DIO_WritePin(LED3,HIGH);
}
/* READY */
/* Parameters : N/A */
/* I/p : N/A */
/* O/p : N/A */
/* Return : void */
/* Function that initialize STOP LED IN STATE MACHINE  */
void READY(void)
{
	DIO_WritePin(LED1,LOW); /*READY State*/
	DIO_WritePin(LED2,HIGH);
	DIO_WritePin(LED3,LOW);
}

void (*ptr[3])(void)={GO,STOP,READY};/*ARRAY OF POINTER TO FUNCTION FOR 3 TASKS GO STOP READY */


