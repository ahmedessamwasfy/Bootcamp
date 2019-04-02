


#ifndef _TIMER__H_
#define _TIMER__H_
#include "../includes/DIO.h"
#include "../includes/Types.h"
#include "../includes/BitwiseOperations.h"
#include "../includes/DIO.h"
#include <avr/interrupt.h>
#define TCCR0  (*((volatile ptr_u8)0x53))
#define TCNT0  (*((volatile ptr_u8)0x52))
#define OCR0   (*((volatile ptr_u8)0x5C))
#define TIMSK  (*((volatile ptr_u8)0x59))
#define SREG   (*((volatile ptr_u8)0x5F))
#define MCUCSR (*((volatile ptr_u8)0x54))
#define GICR   (*((volatile ptr_u8)0x5B))
#define ISC2    6
#define INT2    5
#define TCCR1A     0x4F
#define TCCR1B     0x4E
#define _TCNT1H_   0x4D
#define TCNT1L     0x4C
#define OCR1AH     0x48
#define OCR1AL     0x4A
#define OCR1BH     0x49
#define OCR1BL     0x48

#define COM1B0  4
#define COM1B1  5
#define COM1A0  6
#define COM1A1  7

#define OC1A 29
#define OC1B 28

#define NUMBER_ZERO 0
#define NUMBER_ONE  1
#define IBIT        7
#define OCR0_VALUE_REGISTER 124


extern volatile uint16 g_tick;

void timer0_init_CTC_mode(void);

extern volatile uint8 STATUS;
#define NUMBER_OF_OVERFLOWS_PER_ONE_SECOND 500



#endif /* _TIMER__H_ */