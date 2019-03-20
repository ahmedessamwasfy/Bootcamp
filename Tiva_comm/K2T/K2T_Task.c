
/* Transmitter */

#include "Includes/Types.h"
#include "Includes/K2T.h"
#include "Includes/Debouncing.h"
#include "../Includes/uart.h"
#include "../Includes/Keypad.h"
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

uint8 prev=0;
void K2T_task(){

    /*if status equal one then call key pad pressed */
    /*send the uart char*/
    uint8 data=10;


    void Button_Pressed(void);
    if(keypad_state==1)
    {

       data=Keypad_getPressedKey();
       if(data !=0)
       {
           if(data !=prev)
           {
             prev=data;
             UARTCharPut(UART0_BASE, data+48);
           }
        }
    }



}
