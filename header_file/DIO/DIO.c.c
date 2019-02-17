#include "DIO.h"
/*********************************/

void DIO_WritePin(uint8 PinNum,uint8 PinValue)
{
	if((PinNum>=0) && (PinNum<=7))
	{
		if(PinValue==1)
		{
			Set_Bit(PORTA,PinNum);
		}
		else
		{
			Clear_Bit(PORTA,PinNum);
		}
	}
	else if(PinNum>=8 && PinNum<=15)
	{
		if(PinValue==1)
		{
			Set_Bit(PORTB,PinNum-8);
		}
		else
		{
			Clear_Bit(PORTB,PinNum-8);
		}
	}
	else if(PinNum>=16 && PinNum<=23)
	{
		if(PinValue==1)
		{
			Set_Bit(PORTC,PinNum-16);
		}
		else
		{
			Clear_Bit(PORTC,PinNum-16);
		}
	}
	else if(PinNum>=24 && PinNum<=31)
	{
		if(PinValue==1)
		{
			Set_Bit(PORTD,PinNum-24);
		}
		else
		{
			Clear_Bit(PORTD,PinNum-24);
		}
	}
	
}

/********************************/

void DIO_SetPinDirection(uint8 PinNum,uint8 PinDirection)//DDR>>1>>out>>0>>input
{
	if(PinNum>=0 && PinNum<=7)
	{
		if(PinDirection==1)//1
		{
			Set_Bit(DDRA,PinNum);
		}
		else//0
		{
			Clear_Bit(DDRA,PinNum);
		}
	}
	else if(PinNum>=8 && PinNum<=15)
	{
		if(PinDirection==1)
		{
			Set_Bit(DDRB,PinNum-8);
		}
		else
		{
			Clear_Bit(DDRB,PinNum-8);
		}
	}
	else if(PinNum>=16 && PinNum<=23)
	{
		if(PinDirection==1)
		{
			Set_Bit(DDRC,PinNum-16);
		}
		else
		{
			Clear_Bit(DDRC,PinNum-16);
		}
	}
	else if(PinNum>=24 && PinNum<=31)
	{
		if(PinDirection==1)
		{
			Set_Bit(DDRD,PinNum-24);
		}
		else
		{
			Clear_Bit(DDRD,PinNum-24);
		}
	}
	
}

/********************************/

uint8 DIO_ReadPin(uint8 PinNum)
{
		if(PinNum>=0 && PinNum<=7)
		{
			return get_bit( PINA , PinNum );
		}
		else if(PinNum>=8 && PinNum<=15)
		{
			return get_bit( PINB , PinNum-8 );
		}
		else if(PinNum>=16 && PinNum<=23)
		{
			return get_bit( PINC , PinNum-16);
		}
		else if(PinNum>=24 && PinNum<=31)
		{
			return get_bit( PIND ,PinNum-24 );
		}
		
	}
	
/*******************************/
	

