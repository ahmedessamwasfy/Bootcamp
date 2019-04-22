#include "include/FreeRTOS.h"
#include "include/task.h"
#include "include/event_groups.h"
#include "include/queue.h"
#include "COM_MODULE_AUTOSAR/com_cfg.h"
#include "COM_MODULE_AUTOSAR/com.h"


QueueHandle_t UART_RECEIVE_QUEE; /* RX Queue by UART  */
QueueHandle_t SPI_TRANSMIT_QUEE; /*TX Queue by SPI*/

int main(void)
{
     UART_RECEIVE_QUEE =  xQueueCreate( 1,sizeof(uint8) ); /* UART receive queue */
     SPI_TRANSMIT_QUEE  =  xQueueCreate( 1,sizeof(uint8) ); /* SPI transmit queue */

     xTaskCreate(Init_Task,"INIT Task",100,NULL,8,NULL); /* INIT task */
     xTaskCreate(Allignment_Task,"ALIGHNMENT Task",100,NULL,6,NULL); /* ALIGHNMENT Task*/
     xTaskCreate(Button_Task,"BTN ",100,NULL,7,NULL);/* BTN TASK */
     xTaskCreate(UartRecv_Task,"UartRecv_Task",100,NULL,5,NULL);/* UART Receive task */
     xTaskCreate(ComMAIN_TX,"COMMAIN Task",300,NULL,4,NULL);/* COMMAIN TASK */
     xTaskCreate(SPI_Task,"SPI Task",300,NULL,3,NULL);/*SPI TASK */

     vTaskStartScheduler();
    return 0;
}
