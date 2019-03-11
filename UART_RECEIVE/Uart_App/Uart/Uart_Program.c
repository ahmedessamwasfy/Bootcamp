/*
 * Uart_Program.c
 *
 * Created: 2/27/2019 1:23:42 PM
 *  Author: AVE-LAP-005
 */ 

#include "Types.h"
#include "Utilites.h"
#include "BitwiseOperations.h"
#include "Uart_Config.h"
#include "Uart_Interface.h"

/***********************UART_Init()***************************
*I/P:NOTHING
*Return:NOTHING
*Description:this function Initilaize Uart with the values choosen in the uart_Config
*************************************************************/

void UART_Init(){
	 uint16 UBRR_VALUE=0;
	
	/*local Uart_Str*/
	UART_Confg_S Uart_Str={BAUD_CNFG,STOP,PARITY,BITS,SPEED};
	/*Check wether double speed or not*/
	switch(Uart_Str.SpeedMode){
		case NORMAL_SPEED:
		{
			/*Apply the equation at the normal mode*/
		UBRR_VALUE=((F_CPU/16)/(Uart_Str.BaudRate))-1;
		break;
		}
		case DOUBLE_SPEED:Set_Bit(UART->UCSRA,U2X);
		{
			/*Apply the equation at the double speed mode*/
		UBRR_VALUE=((F_CPU/8)/(Uart_Str.BaudRate))-1;
		break;
		}
	}
	
	/*Update the Baud Rate*/
	UBRRH =(uint8)(UBRR_VALUE>>SHIFT_EIGHT);
	UART->UBRRL =(uint8)UBRR_VALUE;
	
	/*Choose Size*/
	switch(Uart_Str.DataSize)
	{
	case FIVE_BITS:
	{
	/*Choose data bits as 5 bits*/
	Clear_Bit(UART->UCSRB,UCSZ2);
   break;
	}
   case SIX_BITS:
   {
	/*Choose data bits as 6 bits*/
	UCSRC|=(1<<UCSZ0)|(1<<URSEL);
	Clear_Bit(UART->UCSRB,UCSZ2);
   break;
   }
   case SEVEN_BITS:
   {
	/*Choose data bits as 7 bits*/
    UCSRC|=(1<<UCSZ1)|(1<<URSEL);
	Clear_Bit(UART->UCSRB,UCSZ2);   
    break;
   }
	case EIGHT_BITS:
	{
   /*Choose data bits as 8 bits*/
   UCSRC|=(1<<UCSZ0)|(1<<UCSZ1)|(1<<URSEL);
    break;
	}
	}
   switch(Uart_Str.NO_StopBits)
   {
	   case STOP_ONE:
	   {
	/* one stop bit*/
	break;
	   }
   case STOP_TWO:
   {
	   /* two stop bit*/
	   UCSRC|=(1<<URSEL)|(1<<USBS);
	   break;
   }
   }
   switch(Uart_Str.ParityMode)
   {
	   case PARITY_ODD:
	   {
	  UCSRC|=(1<<URSEL)|(1<<UPM0)|(1<<UPM1);
	   break;
	   }
      case PARITY_EVEN: 
	  {
	   UCSRC|=(1<<URSEL)|(1<<UPM1);
	   break;
	  }
      case PARITY_DISABLE:
	  {
		  /*Choose Default values*/
	   break;
	  }
   }
	/*Enable transimetter and reciver*/
	Set_Bit(UART->UCSRB,RXEN);
	Set_Bit(UART->UCSRB,TXEN);
	
 }
 /***********************UART_Transmit()***************************
 *I/P:uint8 data
 *Return:NOTHING
 *Description:this function transmit one char
 *************************************************************/
void UART_Transmit(uint8 data){
   /*Check wether the udr empty to transmit*/
   while (!( UART->UCSRA & (1<<UDRE)));
   /* Put data into buffer, sends the data */
   UART->UDR = data;
}
/***********************UART_Reccive()***************************
*I/P:NOTHING
*Return:uint8
*Description:this function receive one char from uart
*************************************************************/
uint8 UART_Receive(){
	/*Receive completed*/
	while(Get_Bit(UART->UCSRA,RXC)==0);
	return UART->UDR;
	
}