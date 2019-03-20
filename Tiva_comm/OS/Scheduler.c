/*
 * Scheduler.c
 *
 * Created: 2/23/2019 4:30:29 PM
 *  Author: AVE-LAP-005
 */ 
#include <Includes/Systick.h>
#include <stdio.h>
#include "../Includes/BitwiseOperations.h"
#include "../Includes/Types.h"
#include "../Includes/Task.h"
#include "../Includes/Scheduler.h"
#include "../Includes/Utilites.h"

volatile uint8 flag=0;
static volatile uint32 size=0;
/* declare static set_flag function */
static void set_flag();
static void Swap(TCB* Task1,TCB* Task2);
static void Sorting_Priority();
/****************************************************************************
*  INPUT:NOTHING
*  OUTPUT:NOTHING
* Description: This function Initilaize timer and initilaize set_callback
* to call set_flag in the isr every tick time and check on the flag to call scheduler

****************************************************************************/
void Scheduler_Init() 
{
	
	uint32 i=0;
	for (i=0;i<MAX_SIZE;i++)
	{
		System_Tasks[i].task=NULL;
		System_Tasks[i].Periodicity=0;
		System_Tasks[i].Delay=0;
		System_Tasks[i].Priority=0;
	}
	
	
}
/****************************************************************************
*  INPUT:NOTHING
*  OUTPUT:NOTHING
* Description: This function Starts The Scheduler 

****************************************************************************/
void Scheduler_Start(){
	
	Sorting_Priority();
	Timer_Init();
	/*Call back the set flag function to set the flag*/
	Set_CallBack(set_flag);
	while (1)
	{
		if (flag==NUM_ONE)
		{
			flag=NUM_ZERO;
			TTC_Scheduler();
		}
	}
	
	
}

/****************************************************************************
*  INPUT:NOTHING
*  OUTPUT:NOTHING
* Description: This function Called every tick to execute the tasks sequentially 

****************************************************************************/
void TTC_Scheduler(){
	
	uint32 i=NUM_ZERO;
	/*Decrease the Delay till equal zero for each task then make it equal periodicity when it's execution time comes*/
	for (i=NUM_ZERO;i<size;i++)
	{
	if(NUM_ZERO==(System_Tasks[i].Delay--))
	{
		/* if id doesn't equal R which remains remove then execute this task */
		if ((System_Tasks[i].id != 'R'))
		{
		System_Tasks[i].task();
		System_Tasks[i].Delay=System_Tasks[i].Periodicity;
		}
	}
	}
}
/****************************************************************************
*  INPUT:NOTHING
*  OUTPUT:NOTHING
* Description: This function Sets flag with one with every tick 

****************************************************************************/
static void set_flag(){
	/*Set the flag*/
	flag=NUM_ONE;
	
}
/****************************************************************************
*  INPUT:Pointer To Function
*  OUTPUT:NOTHING
* Description: This function Adds task to the array of tasks

****************************************************************************/
uint8 Scheduler_Add_Task(TCB* Task)
{
/*Check Wether the size exceeds the max and if not assigns the values to the array of structure */	
	if(size<MAX_SIZE){
		/*assign values to the task */
		System_Tasks[size].task=Task->task;
		System_Tasks[size].Periodicity=Task->Periodicity;
		System_Tasks[size].Delay=Task->Periodicity;
		System_Tasks[size].Priority=Task->Priority;
		System_Tasks[size].id = Task->id;
		size++;
		 return TRUE;
	}else{
		return FALSE;
	}
	
}
/****************************************************************************
*  INPUT:two pointers to structures 
*  OUTPUT:NOTHING
* Description: This function swaps between two structures

****************************************************************************/

static void Swap(TCB* Task1,TCB* Task2){
	TCB temp;
	temp=*(Task1);
	*(Task1)=*(Task2);
	*(Task2)=temp;
	
}
/****************************************************************************
*  INPUT:Nothing
*  OUTPUT:NOTHING
* Description: This function used to sort the System Array by Priority

****************************************************************************/
static void Sorting_Priority()
{
	uint32 i=NUM_ZERO;
	uint32 j=NUM_ZERO;
	for (i=0;i<size;i++)
	{
		for(j=i+1;j<size;j++)
		{
			if (System_Tasks[i].Priority > System_Tasks[j].Priority  )
			{
			Swap(&System_Tasks[i],&System_Tasks[j]);	
			}
		}
	}
	
	
}
/****************************************************************************
*  INPUT:Task_id
*  OUTPUT:NOTHING
* Description: This function Removes the task by id

****************************************************************************/
void Remove_Task(uint32 Task_id){
	uint32 i=NUM_ZERO;
	for (i=NUM_ZERO;i<size;i++)
	{
		if (System_Tasks[i].id == Task_id)
		{
			/* Block Task*/
			System_Tasks[i].id= 'R' ;
		}
	}
	
}
