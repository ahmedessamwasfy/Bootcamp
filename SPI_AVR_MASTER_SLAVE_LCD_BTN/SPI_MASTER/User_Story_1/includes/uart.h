
#ifndef UART_H_
#define UART_H_

#include "../includes/uart_cfg.h"

#include "../includes/Types.h"
#include "../includes/BitwiseOperations.h"
#define LED1  13 /*LED1 PIN NUMBER */
#define LED0  12 /*LED1 PIN NUMBER */
#define BUZZER 11


void UART_Inti(void);
void UART_Transmit(uint8 Data);
uint8 UART_Reseive(void);
void UART_TransmitString(uint8* String ,uint8 Size);



#endif /* UART_H_ */