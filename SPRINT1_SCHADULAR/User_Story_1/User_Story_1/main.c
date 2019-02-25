#include "includes/BitwiseOperations.h"
#include "includes/schadular.h"

int main(void)
{
	
    DIO_SetPinDirection(LED1,OUTPUT); /*Set DDRB5 (LED1) Output*/
    DIO_SetPinDirection(LED2,OUTPUT); /*Set DDRB6 (LED2) Output*/
    DIO_SetPinDirection(LED3,OUTPUT); /*Set DDRB7 (LED3) Output*/

    DIO_WritePin(LED1,LOW); /*Led is off*/
    DIO_WritePin(LED2,LOW); /*Led is off*/
    DIO_WritePin(LED3,LOW); /*Led is off*/
    while (1) 
    {  
		prefield(ptr,3);
	}
	

}
	

		
	 



