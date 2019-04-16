
#ifndef UART_H_
#define UART_H_

#include <stdint.h>
#include <stdbool.h>
#include "uart_cfg.h"
#include "inc/hw_memmap.h"
#include "driverlib/debug.h"
#include "driverlib/gpio.h"
#include "driverlib/sysctl.h"
#include "driverlib/uart.h"
#include <Types.h>
#include "driverlib/pin_map.h"

void UART_Init(void);
void UART_Send(uint8 data);
uint8 UART_Recive(void);


#endif /* UART_H_ */
