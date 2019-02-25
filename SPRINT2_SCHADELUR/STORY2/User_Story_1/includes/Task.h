

#ifndef TASK_H_
#define TASK_H_

#include "../includes/DIO.h"
#include "../includes/Types.h"
#include "../includes/BitwiseOperations.h"


void GO(void);/*TASK1 PROTOTYPE */
void STOP(void);/*TASK2 PROTOTYPE */
void READY(void);/*TASK3 PROTOTYPE */

#define NUMBER_OF_TASK 3
#define LED1  13 /*LED1 PIN NUMBER */
#define LED2  14 /*LED2 PIN NUMBER */
#define LED3   15 /*LED3 PIN NUMBER */
#define BTN1   /*BUTTON PIN NUMBER */

extern void (*ptr[3])(void);

#endif /* TASK_H_ */