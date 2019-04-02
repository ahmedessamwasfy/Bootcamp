#include "../includes/uart.h"


/*UART_Inti */
/* Parameters : void */
/* I/p : void */
/* O/p : N/A */
/* Return : Void */
/* Function that initialize UART  */
void UART_Inti()
{
	UART_STRCT UART_Config_S={BAUDRATE,NO_STOPBIT,PARITYMODE,DATASIZE,SPEEDMODE};/*initialize structure */
	
	UCSRB |= (ONE<<RXEN) | (ONE<<TXEN);/*UART enable transmit and receive */
	
	if(UART_Config_S.Data_Size==EIGHT_BIT_DATA)/*check the data size */
	{
		
		UCSRC|=(ONE<<UCSZ0)|(ONE<<UCSZ1)|(ONE<<URSEL);/*write 1 in URSEL to enable writing in UCSRC register */
	}
	
	if(UART_Config_S.SpeedMode)
	{
		Set_Bit(UCSRA,U2X);/*double speed mode */
	}
	/* First 8 bits from the BAUD_PRESCALE inside UBRRL and last 4 bits in UBRRH*/
	UBBRH = UBBR_REGISTER_VALUE>>EIGHT_BIT_DATA;
	UBBRL = UBBR_REGISTER_VALUE;
}



/*UART_Transmit */
/* Parameters : Uint8 */
/* I/p : Uint8 */
/* O/p : N/A */
/* Return : Void */
/* Function that send 1 byte by UART  */
void UART_Transmit(uint8 data)
{
	/* UDRE flag is set when the Tx buffer (UDR) is empty and ready for 
	 * transmitting a new byte so wait until this flag is set to one */
	while(!(Get_Bit(UCSRA,UDRE)));
	UDR=data;
}


/*UART_Reseive */
/* Parameters : N/A */
/* I/p : N/A */
/* O/p : N/A */
/* Return : Uint8 */
/* Function that receive 1byte by UART by UDR register */
uint8 UART_Reseive(void)
{
	/* RXC flag is set when the UART receive data so wait until this 
	 * flag is set to one */
	while(Get_Bit(UCSRA,RXC)==ZERO){};
    return UDR;	/* return from this fun the sent value by uart which is stored in UDR register */
}