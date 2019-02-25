#include "../includes/schadular.h"
volatile uint8 FLAG=ZERO ;

volatile uint32 index = ZERO; 
Task Task_Arr[NUMBER_OF_TASK];/*array of structure from type TASK  */




/*schadular_init_start */
/* Parameters : N/A */
/* I/p : N/A */
/* O/p : N/A */
/* Return : void */
/* Function that SET FLAG BY CALL THIS FUN INSIDE ISR */
void SET_FLAG()
{
	FLAG = ONE ;/*flag is set when compare match occur in ISA */
}



/*schadular_init_start */
/* Parameters : N/A */
/* I/p : N/A */
/* O/p : N/A */
/* Return : void */
/* Function that initialize the scheduler  */
void schadular_init_start()
{
	timer0_init_CTC_mode();/*TIMER INIT */
	set_call_back(SET_FLAG);/*CALL BACK FUN THAT TAKES THE ADDRESS OFN SET FLAG FUN TO SET THIS FLAG EACH COMPARE */
	sort_task();
	while(ONE)
	{
		if(ONE == FLAG)/*check if flag is set and its set every compare occur and its set inside ISR */
		{
			 FLAG=ZERO;
			 prefield();/*call algorithm for scheduling */

		}
	}	
}



/*prefield  */
/* Parameters : N/A */
/* I/p : array of pointer to function that void/void  and size of array*/
/* O/p : N/A */
/* Return : void */
/* Function that takes array of pointer to fun to access the task  */
static void prefield()
{
	uint8 i;/*INDEX */
	for(i=ZERO ; i<index ; i++)
	{
		/* the idea of this algorithm is in the beginning the periodicity equal time remain 
		so to make sure to execute this task is wait untiles periodicity equal zero so the task execute and 
		initialize the periodicty == remaining and loop like this again this algorithm make sure that each task will be
		executed in its periodicity */
      Task_Arr[i].Remaining_Ticks--;
	  /*when remain = zero it means periodicity ticks finished and its time to execute task */
	  if(Task_Arr[i].Remaining_Ticks==0)
	  {
		  Task_Arr[i].ptr_func();
		  Task_Arr[i].Remaining_Ticks=Task_Arr[i].Task_Periodicity;
		  
	  }
	}
}




/*scheduler_Add_Task  */
/* Parameters : N/A */
/* I/p : array of pointer to function that void/void  and size of array*/
/* O/p : N/A */
/* Return : void */
/* Function that takes array of pointer to fun to access the task  */
uint8 scheduler_Add_Task(Task *ptr)/*the argument for add fun is structure so i receive it in pointer to structure */
{
		uint8 x = ONE;
		
		if (index < NUMBER_OF_TASK)
		{
			/* here i am initialize the structure element so in the main i 
			send this structure as argument and here aim assign  each element*/
			
			Task_Arr[index].ptr_func=ptr->ptr_func;/*assign the value of ptr_fun element in Task_array = ptr in main */
			Task_Arr[index].Task_Periodicity=ptr->Task_Periodicity;
			Task_Arr[index].Remaining_Ticks=ptr->Remaining_Ticks;
			Task_Arr[index].priority=ptr->priority;
             /*access each element in structure using arrow cause its pointer */
			index++;
			x = ONE;
		}
		else
		{
			x = ZERO;
		}
		return x;	
}


/* sort_task  */
/* Parameters : N/A */
/* I/p :void */
/* O/p : N/A */
/* Return : void */
/*function that takes array of structure and sort these structure 
by priority and the lowest priority is the lowest address and so on   */
static void sort_task()
{
	uint8 i,j;
	for(i=0 ; i<NUMBER_OF_TASK ; ++i)/*loop for sort */
	{
	for(j=i+1;j<NUMBER_OF_TASK;++j)
	{
		if(Task_Arr[i].priority>Task_Arr[j].priority)   /* To sort in descending order, change > to < in this line. */
		{
			swap(&Task_Arr[i],&Task_Arr[j]);/* call swap fun and the argument is address for two element in task_arr [i][j]*/
		}
	}
	}
	
}


/* swap  */
/* Parameters : N/A */
/* I/p :two pointer to structure */
/* O/p : N/A */
/* Return : void */
/* Function that takes two pointer to structure that carry address of two structure inside array 
of pointer to structure call task_arr that send from sort fun  */
static void swap(Task *task1 , Task *task2)
{
	/* swap function that task address for structure and receive it in pointer to structure and
     use temp variable from type TASK struct to use it as temporary variable */
	Task temp ;
	/*swap structure task1 with structure task2 by temp */
    temp=*task1;  
	*task1=*task2;
	*task2=temp;	
}