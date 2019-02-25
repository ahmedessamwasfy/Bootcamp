
#include "includes/Types.h"
#include "includes/_TIMER_.h"
#include "includes/BitwiseOperations.h"
#include "includes/Task.h"
#include "includes/schadular.h"

int main(void)
{
	
    timer0_init_CTC_mode; 
    DIO_SetPinDirection(LED1,OUTPUT); /*Set DDRB5 (LED1) Output*/
    DIO_SetPinDirection(LED2,OUTPUT); /*Set DDRB6 (LED2) Output*/
    DIO_SetPinDirection(LED3,OUTPUT); /*Set DDRB7 (LED3) Output*/

	schadular_init_start();/*initialize the scheduler*/
    
	

}
	

		
	 



