#include "Includes/Types.h"
#include "Includes/uart.h"
#include <stdint.h>
#include <stdbool.h>
#include "Includes/uart_cfg.h"
#include "inc/hw_memmap.h"
#include "driverlib/debug.h"
#include "driverlib/gpio.h"
#include "driverlib/sysctl.h"
#include "driverlib/uart.h"
#include "driverlib/pin_map.h"


//------------UART_Init------------
// Initialize the UART for 38400 baud rate (assuming 80 MHz UART clock),
// 8 bit word length, no parity bits, one stop bit, FIFOs enabled
// Input: none
// Output: none
void UART_Init(void){

    UART_STRCT CONFIG ; /*declared structure from type UART_STRCT*/
    CONFIG.BaudRate    = BAUDRATE; /*115200 BAUD RATE */
    CONFIG.Data_Size   = DATASIZE; /*8 Bit data size */
    CONFIG.No_StopBits = NO_STOPBIT;/* one stop bit */
    CONFIG.Parity_Mode = PARITYMODE;/* no parity check */


    /*ENABLE CLOCK FOR UART PRIPHREL AND MAKE IT SYNCH WITH PROCESSOR SYSTICK
     TIMER AND  Wait for the UART0 module to be ready.Enable the UART0 module.*/
    SysCtlPeripheralEnable(SYSCTL_PERIPH_UART5);
    while(!SysCtlPeripheralReady(SYSCTL_PERIPH_UART5))/*AND  Wait for the UART0 module to be ready.Enable the UART0 module.*/
    {
    }
    /* Initialize the UART. Set the baud rate, number of data bits, turn off
       parity, number of stop bits, and stick mode. The UART is enabled by the
       function call.*/
    UARTConfigSetExpClk(UART5_BASE, SysCtlClockGet(), CONFIG.BaudRate, (CONFIG.Data_Size | CONFIG.No_StopBits | CONFIG.Parity_Mode));


    SysCtlPeripheralEnable(SYSCTL_PERIPH_GPIOE);/*ENABLE CLOCK FOR GPIO PRIPHREL*/
    while(!SysCtlPeripheralReady(SYSCTL_PERIPH_GPIOE))
    {
    }


    /* Set GPIO A0 and A1 as UART pins.*/
    GPIOPinConfigure(GPIO_PE4_U5RX);
    GPIOPinConfigure(GPIO_PE5_U5TX);
    GPIOPinTypeUART(GPIO_PORTE_BASE, GPIO_PIN_4 | GPIO_PIN_5);
}
/****************************************************************************
*  INPUT:uint 8
*  OUTPUT:NOTHING
* Description: This function that send 1 byte by uart
*

****************************************************************************/
void UART_Send(uint8 data)
{
    /* This function sends the character ucData to the transmit FIFO for the specified port. If there is
       no space available in the transmit FIFO, this function waits until there is space available before
       returning
    */
        UARTCharPut(UART5_BASE, data);
}
/****************************************************************************
*  INPUT:uint 8
*  OUTPUT:NOTHING
* Description: This function that recive 1 byte by uart
*

****************************************************************************/
uint8 UART_Recive(void)
{

    /*wait until the data buffer FIFO is empty and i can send or receive */
    while(!UARTCharsAvail(UART5_BASE)){};

    /* Get the character(s) in the receive FIFO.recive data from FIFO by UART and load it in data variable */
    /*This function gets a character from the receive FIFO for the specified port.*/

    return UARTCharGetNonBlocking(UART0_BASE);
}

