#include "includes/Types.h"
#include "includes/BitwiseOperations.h"
#include "includes/LCD.h"
#include "includes/spi.h"

/*************************SLAVE******************/
int main(void)
{
	SPI_initSlave();/*INIT master */
    LCD_init(); /* INIT LCD */
	uint8 data ;
	while(1)
	{
       data = SPI_recieveByte();
	   LCD_displayCharacter(data);	
	}
	
}







