

#ifndef SCHADULAR_H_
#define SCHADULAR_H_
#include "../includes/DIO.h"
#include "../includes/Types.h"
#include "../includes/BitwiseOperations.h"
#include "../includes/_TIMER_.h"
#include "../includes/Task.h"


void schadular_init_start();/* scheduler initialization prototype */
static void prefield();/*PROTOTYPE FOR RRAY OF PTR TO FUN */

void (*Tasks_Arr[NUMBER_OF_TASK])(void);/*STORY 1 array of pointer to fun that store address of my tasks */


typedef struct 
{
	void(*ptr_func)(void);   /*Pointer to function*/
	uint16 Task_Periodicity;	 /*Task periodicity*/
	uint16 Remaining_Ticks;		/*Remaining Ticks*/
}Task;



#endif /* SCHADULAR_H_ */