

/**
 * main.c
 */
#include <stdbool.h>
#include <stdint.h>
#include "inc/hw_memmap.h"
#include "inc/hw_types.h"
#include "driverlib/gpio.h"
#include "driverlib/pin_map.h"
#include "driverlib/rom.h"
#include "driverlib/sysctl.h"
#include "include/FreeRTOS.h"
#include "include/task.h"
#include "include/event_groups.h"
#include "include/queue.h"
#include "De-Allignment.h"
#include "spi.h"
#include "LCD.h"
QueueHandle_t SPI_Queue;
int main(void)
{
#if (0)
    ROM_SysCtlClockSet(SYSCTL_SYSDIV_4 | SYSCTL_USE_PLL | SYSCTL_XTAL_16MHZ |
                          SYSCTL_OSC_MAIN);
    uint32_t x;
    uint32_t y;
    LCD_init();
    SPI_Init(3);
    while(1){
        x=SPI_Recieve(&y);
        LCD_displayData(y);
    }

#endif
    SPI_Queue = xQueueCreate( 10,2 );

     xTaskCreate(Init_Task,"Init Task",100,NULL,8,NULL);
     xTaskCreate(SPI_Task,"SPI Task",100,NULL,7,NULL);
     xTaskCreate(De_allignment_Task,"main Task",100,NULL,6,NULL);
     vTaskStartScheduler();

     while(1){

     }
	return 0;
}

