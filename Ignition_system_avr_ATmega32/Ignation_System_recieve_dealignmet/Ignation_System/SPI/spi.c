
#include "../includes/Std_Types.h"
#include "../includes/numbers.h"
#include "../includes/BitwiseOperations.h"
#include "../includes/atmega32.h"
#include "../DIO/DIO_prog.h"
#include "spi.h"
#include "../LCD/lcd.h"

void SPI_MasterInit(void)
{
	/* Set SPI SS PIN AS OUTPUT */
	DIO_SetPinDirection(SPI_SS,OUTPUT);
	
	/* Set SPI MOSI PIN AS OUTPUT */
	DIO_SetPinDirection(SPI_MOSI,OUTPUT);
	
	/* Set SPI MISO PIN AS INPUT */
	DIO_SetPinDirection(SPI_MISO,INPUT);
	
	/* Set SPI CLK PIN AS OUTPUT */
	DIO_SetPinDirection(SPI_CLK,OUTPUT);
	
	/* enable SPI, enable AS Master, choose SPI clock = Fosc/4 */
	SPCR = (1<<SPE) | (1<<MSTR); 
}

void SPI_SlaveInit(void)
{
	/* Set SPI SS PIN AS INPUT */
	DIO_SetPinDirection(SPI_SS,INPUT);
	
	/* Set SPI MOSI PIN AS INPUT */
	DIO_SetPinDirection(SPI_MOSI,INPUT);
	
	/* Set SPI MISO PIN AS OUTPUT */
	DIO_SetPinDirection(SPI_MISO,OUTPUT);
	
	/* Set SPI CLK PIN AS INPUT */
	DIO_SetPinDirection(SPI_CLK,INPUT);
	/*  enable SPI */
	SPCR = (1<<SPE); 
}

void SPI_Send(uint8 data)
{
	SPDR = data; 
	
	while(!Get_Bit(SPSR,SPIF)){} 
}

uint8 SPI_Recieve(void)
{
	while(!Get_Bit(SPSR,SPIF)){} 
	return SPDR; 
}

