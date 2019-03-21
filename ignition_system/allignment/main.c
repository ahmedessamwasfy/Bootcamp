

/**
 * main.c
 */
#include "include/FreeRTOS.h"
#include "include/task.h"
#include "include/event_groups.h"
#include "include/queue.h"
#include "allignment.h"

//QueueHandle_t UART_Queue;
int main(void)
{
  //   SPI_Queue= xQueueCreate( 10,1 );

     xTaskCreate(Init_Task,"Init Task",100,NULL,8,NULL);
     xTaskCreate(Allignment_Task,"Allignment Task",100,NULL,6,NULL);
     xTaskCreate(Button_Task,"Allignment Task",100,NULL,7,NULL);

     vTaskStartScheduler();

     while(1){

     }
    return 0;
}
