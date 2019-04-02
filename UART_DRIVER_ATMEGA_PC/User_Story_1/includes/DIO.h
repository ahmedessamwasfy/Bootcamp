

#ifndef __DIO_H__
#define __DIO_H__

#include "Types.h"
#define BUTTON0 20
#define BUTTON1 10
#define LOW 0
#define HIGH 1
#define PORTA	(*(volatile uint8 *) 0x3B)
#define DDRA	(*(volatile uint8 *) 0x3A)
#define PINA	(*(volatile uint8 *) 0x39)

#define PORTB	(*(volatile uint8 *) 0x38)
#define DDRB	(*(volatile uint8 *) 0x37)
#define PINB	(*(volatile uint8 *) 0x36)

#define PORTC	(*(volatile uint8 *) 0x35)
#define DDRC	(*(volatile uint8 *) 0x34)
#define PINC	(*(volatile uint8 *) 0x33)

#define PORTD	(*(volatile uint8 *) 0x32)
#define DDRD	(*(volatile uint8 *) 0x31)
#define PIND	(*(volatile uint8 *) 0x30)

#define SFIOR	(*(volatile uint8 *) 0x50)

#define Pin0	((uint8)0)
#define Pin1	((uint8)1)
#define Pin2	((uint8)2)
#define Pin3	((uint8)3)
#define Pin4	((uint8)4)
#define Pin5	((uint8)5)
#define Pin6	((uint8)6)
#define Pin7	((uint8)7)
#define Pin8	((uint8)8)
#define Pin9	((uint8)9)
#define Pin10	((uint8)10)
#define Pin11	((uint8)11)
#define Pin12	((uint8)12)
#define Pin13	((uint8)13)
#define Pin14	((uint8)14)
#define Pin15	((uint8)15)
#define Pin16	((uint8)16)
#define Pin17	((uint8)17)
#define Pin18	((uint8)18)
#define Pin19	((uint8)19)
#define Pin20	((uint8)20)
#define Pin21	((uint8)21)
#define Pin22	((uint8)22)
#define Pin23	((uint8)23)
#define Pin24	((uint8)24)
#define Pin25	((uint8)25)
#define Pin26	((uint8)26)
#define Pin27	((uint8)27)
#define Pin28	((uint8)28)
#define Pin29	((uint8)29)
#define Pin30	((uint8)30)
#define Pin31	((uint8)31)

#define  TWENTY_FOUR 24
#define  THIRTY_ONE  31
#define   SIXTEEN    16
#define   TWENTY_THREE 23
#define   EIGHT 8
#define FIFTEEN 15
#define SEVEN 7



extern void DIO_WritePin(uint8 PinNum,uint8 PinValue);
extern uint8 DIO_ReadPin(uint8 PinNum);
extern void DIO_SetPinDirection(uint8 PinNum,uint8 PinDirection);

#endif