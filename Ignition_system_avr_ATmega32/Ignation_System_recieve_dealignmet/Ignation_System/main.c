#include "Free_RTOS/FreeRTOS.h"
#include "Free_RTOS/task.h"
#include "Dealingment/De-Allignment.h"
#include "avr/interrupt.h"
/*******************************DEALIGNMENT SLAVE ***************/
int main(void)
{
    sei();
	SPI_SlaveInit();/*INIT SPI*/
	LCD_init();/*INIT LCD */
	De_allignment_Task();/*DEALIGNMENT TASK */  
	return 0;
}

