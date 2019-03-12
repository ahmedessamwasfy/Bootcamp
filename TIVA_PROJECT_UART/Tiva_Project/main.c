
#include <stdint.h>
#include <stdbool.h>
#include "inc/hw_memmap.h"
#include "driverlib/debug.h"
#include "driverlib/gpio.h"
#include "driverlib/sysctl.h"
#include "driverlib/uart.h"
#include "Types.h"
#include "uart.h"
#include "driverlib/pin_map.h"


int main()
{

    uint8 data; /*local variable to store the 8bit data from UART to UART */
    UART_Init();/* INIT  fun for UART */
    UARTCharPut(UART0_BASE, 'a');
    while(ONE)
    {

      data= UART_Recive();
      UARTCharPut(UART0_BASE,data);

    }

}
