#include <stdbool.h>
#include <stdint.h>
#include "inc/hw_memmap.h"
#include "inc/hw_types.h"
#include "driverlib/gpio.h"
#include "driverlib/pin_map.h"
#include "driverlib/rom.h"
#include "driverlib/sysctl.h"
#include "driverlib/can.h"
#include "driverlib/uart.h"
#include "utils/uartstdio.h"
#include "FreeRTOS.h"
#include "task.h"
#include "CAN.h"
#include "BUZZER.h"
#include "queue.h"
#include "My_Task.h"
#include "BTN.h"
#include "LED.h"
/**************************TRANSMIT ECU**********************************/
#define STACK_SIZE_WORD       300
int main(void)
{
    xTaskCreate(vTaskCode3, NULL, STACK_SIZE_WORD, NULL, 7, NULL);/*INIT TASK */
    //xTaskCreate(vTaskCode_NODE_ZERO_START, NULL, STACK_SIZE_WORD, NULL, 6, NULL);/*start up node task */

    xTaskCreate(vTaskCode_NODE_ONE_RX, NULL, STACK_SIZE_WORD, NULL, 3, NULL);
    xTaskCreate(vTaskCode_NODE_ZERO_RX, NULL, STACK_SIZE_WORD, NULL, 3, NULL);
    xTaskCreate(vTaskCode_NODE_TWO_RX, NULL, STACK_SIZE_WORD, NULL, 3, NULL);

    xTaskCreate(vTaskCode_NODE_ZERO_TX, NULL, STACK_SIZE_WORD, NULL, 3, NULL);
    xTaskCreate(vTaskCode_NODE_ONE_TX, NULL, STACK_SIZE_WORD, NULL, 3, NULL);
    xTaskCreate(vTaskCode_NODE_TWO_TX, NULL, STACK_SIZE_WORD, NULL, 3, NULL);

    vTaskStartScheduler();
    return 0;
}
