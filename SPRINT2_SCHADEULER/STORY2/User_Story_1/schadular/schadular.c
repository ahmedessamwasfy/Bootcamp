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
	FLAG =ONE ;/*flag is set when compare match occure in ISA */
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
			 prefield();

		}
	}
	
	
}
/*prefield  */
/* Parameters : N/A */
/* I/p : array of pointer to function that void/void  and size of array*/
/* O/p : N/A */
/* Return : void */
/* Function that takes array of pointer to fun to access the task  */
void prefield()
{
	uint8 i;
	for(i=ZERO ; i<NUMBER_OF_TASK ; i++)
	{
		/* the idea of this algorithm is in the beginning the periodicity equal time remain 
		so to make sure to execute this task is wait untiles periodicity equal zero so the task execute and 
		initialize the periodicty == remaining and loop like this again this algorithm make sure that each task will be
		executed in its periodicity */
      Task_Arr[i].Remaining_Ticks--;
	  if(Task_Arr[i].Remaining_Ticks==0)/*when remain = zero it means periodicity ticks finished and its time to execute task */
	  {
		  Task_Arr[i].ptr_func();
		  Task_Arr[i].Remaining_Ticks==Task_Arr[i].Task_Periodicity;
	  }
	}
}


uint8 scheduler_Add_Task(Task *ptr)/*the argument for add fun is structure so i recive it in pointer to structure */
{
		uint8 x = 1;
		
		if (index < NUMBER_OF_TASK)
		{
			/* here iam initialize the structure element so in the main i send this structure as argument and here aim assign  each element*/
			Task_Arr[index].ptr_func=ptr->ptr_func;
			Task_Arr[index].Task_Periodicity=ptr->Task_Periodicity;
			Task_Arr[index].Remaining_Ticks=ptr->Task_Periodicity;

			index++;
			x = ONE;
		}
		else
		{
			x = ZERO;
		}
		return x;
	
}