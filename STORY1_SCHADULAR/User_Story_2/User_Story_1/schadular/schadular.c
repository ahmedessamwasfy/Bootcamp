#include "../includes/schadular.h"
volatile uint8 FLAG=ZERO ;
/*schadular_init_start */
/* Parameters : N/A */
/* I/p : N/A */
/* O/p : N/A */
/* Return : void */
/* Function that SET FLAG BY CALL THIS FUN INSIDE ISR */
void SET_FLAG()
{
	FLAG =ONE ;
}
/*schadular_init_start */
/* Parameters : N/A */
/* I/p : N/A */
/* O/p : N/A */
/* Return : void */
/* Function that initialize the schadular  */
void schadular_init_start()
{
	
	timer0_init_CTC_mode();/*TIMER INIT */
	set_call_back(SET_FLAG);/*CALL BACK FUN THAT TAKES THE ADDRESS OFN SET FLAG FUN TO SET THIS FLAG EACH COMPARE */
	
	while(ONE)
	{
		if(FLAG ==ONE)
		{
			 FLAG=ZERO;
			 prefield(ptr, NUMBER_OF_TASK);

		}
	}
	
	
}
/*prefield  */
/* Parameters : N/A */
/* I/p : array of pointer to function that void/void  and size of array*/
/* O/p : N/A */
/* Return : void */
/* Function that takes array of pointer to fun to access the task  */
void prefield(void (*ptr[])(void),uint8 size )
{
	uint8 i;
	for(i=ZERO ; i<NUMBER_OF_TASK ; i++)
	{
		ptr[i]();
	}
}