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

#define FIVE_ELEMNTS_IN_QUEE     5
#define SIZE_FOR_ELEMNT_1_BYTE   1

#define INIT_TASK_PRIORITY       6
#define BTN2_TASK_PRIORITY       5
#define BTN1_TASK_PRIORITY       4
#define LCD_TASK_PRIORITY        3

#define STACK_SIZE_WORD          100
int main(void)
{
    Quee=xQueueCreate( FIVE_ELEMNTS_IN_QUEE, SIZE_FOR_ELEMNT_1_BYTE ); /*Declaration for quee which is contain five element each element is 1 byte */

    xTaskCreate(vTaskCode,NULL,STACK_SIZE_WORD,NULL,INIT_TASK_PRIORITY,NULL);/*INIT TASK */
    xTaskCreate(vTaskCode3,NULL,STACK_SIZE_WORD,NULL,BTN2_TASK_PRIORITY,NULL);/*BTN2 TASK */
    xTaskCreate(vTaskCode6,NULL,STACK_SIZE_WORD,NULL,BTN1_TASK_PRIORITY,NULL);/*BTN1 TASK */
    xTaskCreate(vTaskCode5,NULL,STACK_SIZE_WORD,NULL,LCD_TASK_PRIORITY,NULL);/*LCD Task */
    vTaskStartScheduler();

	return 0;
}
