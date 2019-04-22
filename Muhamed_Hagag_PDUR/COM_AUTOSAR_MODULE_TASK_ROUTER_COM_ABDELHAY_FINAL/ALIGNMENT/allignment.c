#if 0
#include <stdint.h>
#include <stdbool.h>
#include "include/FreeRTOS.h"
#include "include/task.h"
#include "inc/hw_gpio.h"
#include "driverlib/gpio.h"
#include "include/event_groups.h"
#include "inc/hw_memmap.h"

#include "include/queue.h"
#include "BUTTON.h"
#include "FSM.h"
#include "Manager.h"
#include "allignment.h"
#include "spi.h"
/**********************************************/
/*the used MACROS*/
#define PRESSED 1
#define NOT_PRESSED 0
#define ZERO 0
#define ONE 1
#define FIVE 5
#define EIGHT 8
#define COMMAND_MASK 0xff
#define DATA_MASK 0x1f
#define TEN 10
#define TASK_TWO_DELAY 50
/**********************************************/
uint8_t Ignition_on = ZERO, count = ZERO;
/*********************************************/
/*Init Task*/
/*********************************************/
void Init_Task(void)
{
    while (1)
    {
        /*UART Initialize*/
        UART_Init();

        /*SPI Initialize*/
        SPI_Init(ZERO);

        /*Button Initialize*/
        BUTTON_Init();

        vTaskSuspend(NULL);
    }
}

/*********************************************/
/*Transmitter Task*/
/*********************************************/

void Allignment_Task(void)
{

    uint8_t Distance, Command;
    uint32_t Data_to_send = ZERO, check;

    while (1)
    {
        /*start the system */
        if (ONE == Ignition_on)
        {

            Data_to_send = ZERO;
            /*Get the distance*/
            Distance = Get_Distance();
            /*Get the Command*/
            Command = FSM(Distance);
            /* divide on EIGHT to scale the data to 5 bits */
            Distance /= EIGHT;
            /* Allignment the data least 5 bits contains the distance and the most 3 bits contains the command  */
            Data_to_send = (((Data_to_send & COMMAND_MASK) | Command) << FIVE)
                    | ((Data_to_send & DATA_MASK) | Distance);
            /* Transmit the data */
            check = SPI_Transmit(Data_to_send);
        }
        vTaskDelay(50);

    }

}


/*********************************************/
/*Button Task*/
/*********************************************/
void Button_Task(void)
{
    while (1)
    {
        if (Get_BUTTON() == PRESSED)
        {
            count++;
        }
        if (Get_BUTTON() == NOT_PRESSED)
        {
            count = ZERO;
        }

        if (count == TEN)
        {
            Ignition_on = ONE;
            GPIOPinWrite(GPIO_PORTF_BASE, GPIO_PIN_2, GPIO_PIN_2);
            vTaskSuspend(NULL);
        }
        vTaskDelay(50);

    }
}
#endif
