
#include "spi.h"
#include "DIO.h"

void SPI_initMaster(void)
{
	DIO_SetPinDirection(Pin12,OUTPUT);/*SS(PB4)   --> Output*/
	DIO_SetPinDirection(Pin13,OUTPUT);/* MOSI(PB5) --> Output*/
	DIO_SetPinDirection(Pin14,INPUT);/* MISO(PB6) --> Input*/
	DIO_SetPinDirection(Pin15,OUTPUT);/*SCK(PB7) --> Output*/
	SPCR = (1<<SPE) | (1<<MSTR); // enable SPI + enable Master + choose SPI clock = Fosc/4
}

void SPI_initSlave(void)
{
	DIO_SetPinDirection(Pin12,INPUT);/*SS(PB4)   --> Input*/
	DIO_SetPinDirection(Pin13,INPUT);/* MOSI(PB5) --> Input*/
	DIO_SetPinDirection(Pin14,OUTPUT);/*MISO(PB6) --> Output*/
	DIO_SetPinDirection(Pin15,INPUT);/* SCK(PB7) --> Input*/
	SPCR = (1<<SPE); // just enable SPI + choose SPI clock = Fosc/4
}

void SPI_sendByte(const uint8 data)
{
	SPDR = data; //send data by SPI
	while(BIT_IS_CLEAR(SPSR,SPIF)){} //wait until SPI interrupt flag=1 (data is sent correctly)
}

uint8 SPI_recieveByte(void)
{
	while(BIT_IS_CLEAR(SPSR,SPIF)){} //wait until SPI interrupt flag=1(data is receive correctly)
	return SPDR; //return the received byte from SPI data register
}

