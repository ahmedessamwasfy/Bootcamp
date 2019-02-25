

#ifndef SCHADULAR_H_
#define SCHADULAR_H_
#include "../includes/DIO.h"
#include "../includes/Types.h"
#include "../includes/BitwiseOperations.h"
#include "../includes/_TIMER_.h"
#include "../includes/Task.h"
#include "../includes/DIO.h"


void schadular_init_start();/* scheduler initialization prototype */
static void prefield();/*PROTOTYPE FOR RRAY OF PTR TO FUN */

void (*Tasks_Arr[NUMBER_OF_TASK])(void);/*STORY 1 array of pointer to fun that store address of my tasks */
void Remove(void (*ptr)(void));

typedef struct 
{
	void(*ptr_func)(void);     /*Pointer to function*/
	uint16 Task_Periodicity;	 /*Task periodicity*/
	uint16 Remaining_Ticks;		/*Remaining Ticks*/
	uint8 priority;           /*priority for each task */ 
}Task;

static void swap(Task *task1 , Task *task2);
static void sort_task();/*prototype for static fun sort_task*/

#endif /* SCHADULAR_H_ */