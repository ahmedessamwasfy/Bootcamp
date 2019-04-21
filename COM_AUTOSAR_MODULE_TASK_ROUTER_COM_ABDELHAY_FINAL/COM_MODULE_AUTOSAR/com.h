#ifndef COM_H_
#define COM_H_
#include "Types.h"

extern void Init_Task(void *pvParameters);
extern void Allignment_Task(void *pvParameters);
extern void Button_Task(void *pvParameters);
extern void UART_Init(void);

extern void SPI_Task(void *pvParameters);
extern void ComMAIN_TX(void *pvParameters);

extern void com_init(void);

extern void com_send_signal(uint8 id , uint8 data);

extern uint8 com_receive_signal(uint8 id);

extern void UartRecv_Task(void *pvParameters);
extern void UART_Send(uint8_t data);




#endif /* COM_H_ */
