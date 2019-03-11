/*
 * Uart_Interface.h
 *
 * Created: 2/27/2019 1:24:24 PM
 *  Author: AVE-LAP-005
 */ 


#ifndef UART_INTERFACE_H_
#define UART_INTERFACE_H_
#define F_CPU 16000000UL
/* Define your baud rate*/
#define BAUD_RATE(Baud)  ((F_CPU/(16*Baud)))-1 

/*Uart Apis*/
void UART_Init();
void UART_Transmit(uint8 data);
uint8 UART_Receive();

typedef struct{
	uint32 BaudRate;
	uint8 NO_StopBits;
	uint8 ParityMode;
	uint8 DataSize;
	uint8 SpeedMode;
	}UART_Confg_S;




#endif /* UART_INTERFACE_H_ */