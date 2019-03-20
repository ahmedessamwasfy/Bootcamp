
#include "Includes/Types.h"
#include "Includes/Systick.h"
#include <stdbool.h>
#include "TM4C123GH6PM.h"
#include "Includes/Scheduler.h"
#include "LCD.h"
#include "Includes/Utilites.h"
#include "Includes/uart.h"
#include "driverlib/sysctl.h"
#include "Includes/Keypad.h"
#include "Includes/K2T.h"
#include "Includes/Debouncing.h"


int main(void)
{
    UART_Init();
    Keypad_init();
    uint8_t key=0;

    while(1){

        key=Keypad_getPressedKey();
        if(key!=0){
            UART_Send(key);
        }
    }

}
