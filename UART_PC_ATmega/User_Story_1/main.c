
#include "includes/Types.h"
#include "includes/BitwiseOperations.h"
#include "includes/uart.h"


int main(void)
{
	UART_Inti();/*INIT FUN FOR UART */
	while(1)
	{
	  UART_Transmit('2');
	}
    
}
	

		
	 



