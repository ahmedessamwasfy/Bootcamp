/*
 * Uart_Registers.h
 *
 * Created: 2/27/2019 1:22:09 PM
 *  Author: AVE-LAP-005
 */ 


#ifndef UART_REGISTERS_H_
#define UART_REGISTERS_H_

/*Masks*/
#define URSEL_MASK   0x80
#define URSEL_DATA_ONE 1
#define URSEL_DATA_ZERO 0
#define UBRRH_DATA_MASK 0x0F00
#define UBRRL_DATA_MASK 0x00FF
#define SHIFT_EIGHT 8

/*Enable MODE*/
#define UART_TRANSMITTER   0
#define UART_RECEIVER      1
#define UART_TRANSMITTER_RECEIVER   2

/*Choose speed*/
#define NORMAL_SPEED 0
#define DOUBLE_SPEED 1

/****************************************Configuration*****************************************/
/*Configuration Options*/
/*Stop Bits*/
#define STOP 1 /* one stop bit*/
/*Data size*/
#define BITS  8
/*Baud Rate*/
#define BAUD_CNFG 9600
#define PARITY 0  /*Disable*/
/*speed mode*/
#define SPEED NORMAL_SPEED
/***************************************************************************************/
/*stop bit number*/
#define STOP_ONE  1
#define STOP_TWO  2
/*Parity*/
#define PARITY 0  /*Disable*/
/*Choose your parity*/
#define PARITY_ODD 1
#define PARITY_EVEN 2
#define PARITY_DISABLE 0

/*No of bits*/
#define FIVE_BITS 5
#define SIX_BITS 6
#define SEVEN_BITS 7
#define EIGHT_BITS 8



/*Enable Transmitter and Receiver bits*/
#define RXEN  4
#define TXEN  3

/*data bits*/
#define UCSZ2 2
#define UCSZ1 2
#define UCSZ0 1
/*selection Register bit*/
#define URSEL 7
/*Synch or Asynch bit*/
#define UMSEL 6
/*Parity bits*/
#define UPM0 4
#define UPM1 5
/*Choose stop bit*/
#define USBS 3
#define UDRE 5
#define RXC  7
/*Speed pin*/
#define U2X 1

volatile typedef struct{
	uint8 UBRRL;
	uint8 UCSRB;
	uint8 UCSRA;
	uint8 UDR;
	
	}StrUart;
	
/* Base Address for uart structure */
#define UART  ((StrUart*)(0x29))

/* the two registers have the same location*/
#define UBRRH (*(volatile uint8*)(0x40))
#define UCSRC (*(volatile uint8*)(0x40))




#endif /* UART_REGISTERS_H_ */