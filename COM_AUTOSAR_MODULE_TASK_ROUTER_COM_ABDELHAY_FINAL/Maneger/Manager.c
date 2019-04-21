#include <stdint.h>
#include "Manager.h"
#include "Types.h"
#include "UART/uart.h"
#include <stdint.h>
#include <stdbool.h>
#include "include/FreeRTOS.h"
#include "include/task.h"
#include "inc/hw_gpio.h"
#include "driverlib/gpio.h"
#include "include/event_groups.h"
#include "inc/hw_memmap.h"
#include "include/queue.h"


extern QueueHandle_t UART_RECEIVE_QUEE; /* transmit Queue */

/*Get_Distance */
/* Parameters : void  */
/* I/p : uint8 , void  */
/* O/p : N/A */
/* Return : uint8 */
/* Function that get duty by UART and make calculation to get the distance */
uint8 Get_Distance()
{
    static uint8 Distance = 0; /* DIS = 0 at begin */
    static uint8_t Duty = 0;

    if (uxQueueMessagesWaiting(UART_RECEIVE_QUEE)) /* check if queue receive anything by UART */
    {
        xQueueReceive(UART_RECEIVE_QUEE, &Duty, 10); /* Assign the received data in Duty variable to make calculation and get distance */
    }
    else
    {
    }
    if (Duty <= 100)
    {
        Distance = (2.55535 * Duty);
    }
    return Distance;
}


