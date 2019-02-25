

#ifndef SCHADULAR_H_
#define SCHADULAR_H_
#include <avr/delay.h>
#include <avr/interrupt.h>

#include "../includes/DIO.h"
#include "../includes/Types.h"
#include "../includes/BitwiseOperations.h"
#include "../includes/_TIMER_.h"
#include "../includes/Task.h"

void prefield(void (*ptr[])(void),uint8 size );/*PROTOTYPE FOR RRAY OF PTR TO FUN */

#endif /* SCHADULAR_H_ */