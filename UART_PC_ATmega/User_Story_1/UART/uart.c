#include "../includes/uart.h"
/*********************************************************************************
 *
 * Function: UART_Inti
 *
 * @param:
 *		input :void
 *
 * @return:   void
 *
 * Description: function that initialize the UART  
 *
 *
 ********************************************************************************/
void UART_Inti()
{
	UART_STRCT UART_Config_S={BAUDRATE,NO_STOPBIT,PARITYMODE,DATASIZE,SPEEDMODE};
	
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


/*********************************************************************************
 *
 * Function: UART_Transmit
 *
 * @param:
 *		input :void
 *
 * @return:   void
 *
 * Description: function that transmit 1 byte by UART
 *
 *
 ********************************************************************************/
void UART_Transmit(uint8 data)
{
	/* UDRE flag is set when the Tx buffer (UDR) is empty and ready for 
	 * transmitting a new byte so wait until this flag is set to one */
	while(!(Get_Bit(UCSRA,UDRE)));
	UDR=data;
}
/*********************************************************************************
 *
 * Function: UART_Transmit
 *
 * @param:
 *		input :void
 *
 * @return:   void
 *
 * Description: function that receive 1 byte by UART
 *
 *
 ********************************************************************************/
uint8 UART_Reseive(void)
{
	/* RXC flag is set when the UART receive data so wait until this 
	 * flag is set to one */
	while(Get_Bit(UCSRA,RXC)==ZERO){};
    return UDR;	
}