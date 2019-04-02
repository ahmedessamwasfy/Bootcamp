
#include "includes/Types.h"
#include "includes/DIO.h"
#include "includes/BitwiseOperations.h"
#include "includes/uart.h"
#include "Free_RTOS/FreeRTOS.h"
#include "Free_RTOS/task.h"
#include "includes/spi.h"

/******************MASTER********************/
int main()
{
	
	DIO_SetPinDirection(BTN1,INPUT);/* BTN1 */
	DIO_SetPinDirection(BTN0,INPUT);/* BTN1 */
    SPI_initMaster(); /* init master spi */
	while(1)
	{
		if(DIO_ReadPin(BTN1))/* check if buttun1 is pressed */
		{
			SPI_sendByte(SWITCH_PRESSED); /* send 1 */
		}
		else if(DIO_ReadPin(BTN0))/* check if buttun0 is pressed */
		{
			SPI_sendByte(SWITCH_NOT_PRESSED);/* send 0 */
		}
	}
}


#if(0)
/* Replace with your application code */
#include "avr\interrupt.h"
#include "Free_RTOS/FreeRTOS.h"
#include "Free_RTOS/task.h"
#include "includes/uart.h"
//================= [Tasks] ===============
char x=0;
void Blink_200ms_task( void *pvParameters)
{
	while(1)
	{

		DIO_WritePin(LED1,HIGH);
		vTaskDelay(2000); //OS Delay
	}
}
//--------------------------------------------------
void Blink_1000ms_task( void *pvParameters)
{
	while(1)
	{

		DIO_WritePin(LED1,LOW);
		vTaskDelay(1000); //OS Delay
	}
}


//================= [Main] ====================//
int main(void)
{
	DIO_SetPinDirection(LED0,OUTPUT);
	DIO_SetPinDirection(LED1,OUTPUT);
	// Create Tasks
	//1 pointer to function
	//2 string
	//3 stack size
	//4 pointer to function create task which will take it
	//5 priority
	xTaskCreate( Blink_200ms_task,NULL, configMINIMAL_STACK_SIZE, NULL, 1, NULL );
	xTaskCreate( Blink_1000ms_task,NULL, configMINIMAL_STACK_SIZE, NULL, 2, NULL );

	// Start FreeRTOS
	vTaskStartScheduler();
}
#endif	
	 



