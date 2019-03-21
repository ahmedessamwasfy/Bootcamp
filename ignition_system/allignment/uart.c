#include "uart.h"
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
    SysCtlPeripheralEnable(SYSCTL_PERIPH_UART0);
    while(!SysCtlPeripheralReady(SYSCTL_PERIPH_UART0))/*AND  Wait for the UART0 module to be ready.Enable the UART0 module.*/
    {
    }
    /* Initialize the UART. Set the baud rate, number of data bits, turn off
       parity, number of stop bits, and stick mode. The UART is enabled by the
       function call.*/
    UARTConfigSetExpClk(UART0_BASE, SysCtlClockGet(), CONFIG.BaudRate, (CONFIG.Data_Size | CONFIG.No_StopBits | CONFIG.Parity_Mode));


    SysCtlPeripheralEnable(SYSCTL_PERIPH_GPIOA);/*ENABLE CLOCK FOR GPIO PRIPHREL*/
    while(!SysCtlPeripheralReady(SYSCTL_PERIPH_GPIOA))
    {
    }


    /* Set GPIO A0 and A1 as UART pins.*/
    GPIOPinConfigure(GPIO_PA0_U0RX);
    GPIOPinConfigure(GPIO_PA1_U0TX);
    GPIOPinTypeUART(GPIO_PORTA_BASE, GPIO_PIN_0 | GPIO_PIN_1);

}

void UART_Send(uint8_t data)
{
    /* This function sends the character ucData to the transmit FIFO for the specified port. If there is
       no space available in the transmit FIFO, this function waits until there is space available before
       returning
    */
        UARTCharPut(UART0_BASE, data);
}
uint8_t first_recieve=1;/*flag to check if the buffer is clean or not if ==1 its not clean */

uint8_t UART_Recive(void)
{
    uint8_t data=0 ;
    if (first_recieve&UARTCharsAvail(UART0_BASE))
    {
        /*to clear the buffer for UART we read the buffer and store data in data variable */
        data = UARTCharGetNonBlocking(UART0_BASE);
        first_recieve=0;/*clear the buffer flag */
    }
    /*wait until the data buffer FIFO is empty and i can send or receive */
    while(!UARTCharsAvail(UART0_BASE)){};

    /* Get the character(s) in the receive FIFO.recive data from FIFO by UART and load it in data variable */
    /*This function gets a character from the receive FIFO for the specified port.*/
    data = UARTCharGetNonBlocking(UART0_BASE);
    return data ;
}
