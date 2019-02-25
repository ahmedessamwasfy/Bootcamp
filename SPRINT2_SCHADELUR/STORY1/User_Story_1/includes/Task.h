

#ifndef TASK_H_
#define TASK_H_

#include "../includes/DIO.h"
#include "../includes/Types.h"
#include "../includes/BitwiseOperations.h"


void GO(void);
void STOP(void);
void READY(void);
#define NUMBER_OF_TASK 3
#define LED1  13
#define LED2  14
#define LED3   15
#define BTN1   10

extern void (*ptr[3])(void);

#endif /* TASK_H_ */