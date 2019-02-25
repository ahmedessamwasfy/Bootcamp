#include "../includes/schadular.h"
volatile uint8 FLAG=ZERO ;

volatile uint32 index = ZERO;
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
			 prefield(Tasks_Arr, NUMBER_OF_TASK);

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
		Tasks_Arr[i]();
	}
}

uint8 scheduler_Add_Task(void(*ptr)(void))
{
	uint8 ret = 1;
	if (index < NUMBER_OF_TASK)
	{
		Tasks_Arr[index]=ptr;
		index++;
		ret = 1;
	}
	else
	{
		ret = 0;
	}
	return ret;
}