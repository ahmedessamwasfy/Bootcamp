
#ifndef UART_CFG_H_
#define UART_CFG_H_
#include "../includes/uart.h"
#include "Types.h"
#define F_CPU 16000000UL
#define UBBR_REGISTER_VALUE (((F_CPU / (BAUDRATE * 8UL))) - 1)/* UART Driver Baud Rate */

#define BAUDRATE    9600 /* Baud rate */
#define NO_STOPBIT  1    /*Macro for number of stop bits */
#define PARITYMODE  0    /*Macro for parity mode if zero it mean there is no parity check */
#define DATASIZE    8    /* data size sent per one transmit */
#define SPEEDMODE   2    /* double speed mode */


typedef struct{
	uint32 BaudRate;
	uint8 No_StopBits;
	uint8 Parity_Mode;
	uint8 Data_Size;
	uint8 SpeedMode;
} UART_STRCT;

/*memory mapped register for UAART */
#define UCSRA (*((volatile ptr_u8)0x2B))
#define UCSRB (*((volatile ptr_u8)0x2A))
#define UCSRC (*((volatile ptr_u8)0x40))
#define UBBRL (*((volatile ptr_u8)0x29))
#define UBBRH (*((volatile ptr_u8)0x40))
#define UDR   (*((volatile uint8*) 0x2C))


/*bits for UCSRA*/
#define RXC    7
#define TXC    6
#define UDRE   5
#define FE     4
#define DOR    3
#define PE     2
#define U2X    1
#define MPCM   0

/*bits for UCSRB*/
#define RXCIE  7
#define TXCIE  6
#define UDRIE  5
#define RXEN   4
#define TXEN   3
#define UCSZ2  2
#define RXB8   1
#define TXB8   0

/*bits for UCSRC*/
#define URSEL  7
#define UMSEL  6
#define UPM1   5
#define UPM0   4
#define USBSN  3
#define UCSZ1  2
#define UCSZ0  1
#define UCPOL  0

#endif /* UART_CFG_H_ */