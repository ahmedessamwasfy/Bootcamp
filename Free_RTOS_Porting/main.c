#include <stdbool.h>
#include <stdint.h>
#include "inc/hw_memmap.h"
#include "inc/hw_types.h"
#include "driverlib/gpio.h"
#include "driverlib/pin_map.h"
#include "driverlib/rom.h"
#include "driverlib/sysctl.h"
#include "driverlib/uart.h"
#include "utils/uartstdio.h"
#include "FreeRTOS.h"
#include "task.h"
#include "BUZZER.h"
#include "queue.h"
#include "My_Task.h"



int main(void)
{
    Quee=xQueueCreate( 5, 1 );

    xTaskCreate(vTaskCode,NULL,100,NULL,6,NULL);/*INIT TASK */
    xTaskCreate(vTaskCode3,NULL,100,NULL,5,NULL);/*BTN2 TASK */
    xTaskCreate(vTaskCode6,NULL,100,NULL,4,NULL);/*BTN1 TASK */
    xTaskCreate(vTaskCode5,NULL,100,NULL,3,NULL);/*LCD Task */
    vTaskStartScheduler();

	return 0;
}
