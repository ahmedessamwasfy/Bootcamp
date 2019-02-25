


#ifndef _TIMER__H_
#define _TIMER__H_
#include "../includes/DIO.h"
#include "../includes/Types.h"
#include "../includes/BitwiseOperations.h"
#include "../includes/DIO.h"
#include <avr/interrupt.h>
#define DIRECTION BACKWORD /*MACRO FOR SELECT THE DIRECTION */
#define STOP     5
#define FORWARD  6
#define BACKWORD 7


#define TCCR0  (*((volatile ptr_u8)0x53))
#define TCNT0  (*((volatile ptr_u8)0x52))
#define OCR0   (*((volatile ptr_u8)0x5C))
#define TIMSK  (*((volatile ptr_u8)0x59))
#define SREG   (*((volatile ptr_u8)0x5F))
#define MCUCSR (*((volatile ptr_u8)0x54))
#define GICR   (*((volatile ptr_u8)0x5B))
#define ISC2    6
#define INT2    5
/*******  TIMER1 MEMORY MAPPED  *********/
#define TCCR1A   (*((volatile ptr_u8)0x4F))
#define TCCR1B   (*((volatile ptr_u8)0x4E))
#define TCNT1H   (*((volatile ptr_u8)0x4D))
#define TCNT1L   (*((volatile ptr_u8)0x4C))
#define OCR1AH   (*((volatile ptr_u8)0x48))
#define OCR1AL   (*((volatile ptr_u8)0x4A))
#define OCR1BH   (*((volatile ptr_u8)0x49))
#define OCR1BL   (*((volatile ptr_u8)0x48))

#define COM1B0  4
#define COM1B1  5
#define COM1A0  6
#define COM1A1  7

#define OC1A 29 /*MOTOR 2 ENABLE */
#define OC1B 28 /*MOTOR 1 ENABLE */
#define MOTOR1_DIR_A1 26  /*MOTOR 1 DIRECTION A */
#define MOTOR1_DIR_B1 27  /*MOTOR 1 DIRECTION B */
#define MOTOR2_DIR_A2 30   /*MOTOR 2 DIRECTION A */
#define MOTOR2_DIR_B2 31   /*MOTOR 2 DIRECTION B */

#define TOP_VALUE     4000   /*TOP VALUE WHICH USED IN Input Capture Register AS MODE 14 FAST PWM */
/*#define COMPARE_VALUE 1000*/  /*COMPARE VALUE WHICH USED IN Output Compare Register AS MODE 14 */


#define NUMBER_ZERO 0
#define NUMBER_ONE  1
#define IBIT        7   /*BIT FOR ENABLE GLOBAL INTERRUPT */
#define OCR0_VALUE_REGISTER 124  /*OCR REGISTER VALUE FOR TIMER ZERO COMPARE MODE */

#define TEN_PERCENT             10
#define TWENTY_PERCENT          20
#define THIRTY_PERCENT          30
#define FORTY_PERCENT           40
#define FIFTY_PERCENT           50
#define SIXTY_PERCENT           60
#define SEVENTY_PERCENT			70
#define EIGHTY_PERCENT   	    80
#define NINTY_PERCENT			90
#define HUNDRED_PERCENT			100
#define NUMBER_OF_OVERFLOWS_PER_ONE_SECOND 1000



extern volatile uint8 external_flag ;

void timer0_init_CTC_mode(void);
void ISR_INT2_Init(void);

void SELECT_DUTY(float duty);
void pwm1_init();



#endif /* _TIMER__H_ */