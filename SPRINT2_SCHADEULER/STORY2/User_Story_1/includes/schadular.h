

#ifndef SCHADULAR_H_
#define SCHADULAR_H_
#include <avr/delay.h>
#include <avr/interrupt.h>

#include "../includes/DIO.h"
#include "../includes/Types.h"
#include "../includes/BitwiseOperations.h"
#include "../includes/_TIMER_.h"
#include "../includes/Task.h"
void schadular_init_start();
void prefield();/*PROTOTYPE FOR RRAY OF PTR TO FUN */
void (*Tasks_Arr[NUMBER_OF_TASK])(void);

typedef struct 
{
	void(*ptr_func)(void); /*Pointer to function*/
	uint8 Task_Periodicity;	/*Task periodicity*/
	uint8 Remaining_Ticks;		/*Remaining Ticks*/
}Task;

Task Task_Arr[NUMBER_OF_TASK];/*array of structure from type TASK  */

#endif /* SCHADULAR_H_ */