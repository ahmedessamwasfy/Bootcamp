#include "sevseg.h"

void BCDSevegments_enable(uint8 SevenSegment_Number)
{
	DIO_WritePin(SevenSegment_Number,high);
}

void BCDSevegments_disable (uint8 SevenSegment_Number)
{
		DIO_WritePin(SevenSegment_Number,low);

}

/*void BCDSevegments_displayNo (uint8 Display_Number)
{
	switch(Display_Number)
	{
		case 0 :
		DIO_WritePin(DATA_PINA,low);
		DIO_WritePin(DATA_PINB,low);
		DIO_WritePin(DATA_PINC,low);
		DIO_WritePin(DATA_PIND,low);
		break ;
		
		case 1 :
		DIO_WritePin(DATA_PINA,high);
		DIO_WritePin(DATA_PINB,low);
		DIO_WritePin(DATA_PINC,low);
		DIO_WritePin(DATA_PIND,low);
		break ;
		
		case 2 :
		DIO_WritePin(DATA_PINA,low);
		DIO_WritePin(DATA_PINB,high);
		DIO_WritePin(DATA_PINC,low);
		DIO_WritePin(DATA_PIND,low);
		break ;
		
		case 3 :
		DIO_WritePin(DATA_PINA,high);
		DIO_WritePin(DATA_PINB,high);
		DIO_WritePin(DATA_PINC,low);
		DIO_WritePin(DATA_PIND,low);
		break ;
		
		case 4 :
		DIO_WritePin(DATA_PINA,low);
		DIO_WritePin(DATA_PINB,low);
		DIO_WritePin(DATA_PINC,high);
		DIO_WritePin(DATA_PIND,low);
		break ;
		
		case 5 :
		DIO_WritePin(DATA_PINA,high);
		DIO_WritePin(DATA_PINB,low);
		DIO_WritePin(DATA_PINC,high);
		DIO_WritePin(DATA_PIND,low);
		break ;
		
		case 6 :
		DIO_WritePin(DATA_PINA,low);
		DIO_WritePin(DATA_PINB,high);
		DIO_WritePin(DATA_PINC,high);
		DIO_WritePin(DATA_PIND,low);
		break ;
		
		case 7 :
		DIO_WritePin(DATA_PINA,high);
		DIO_WritePin(DATA_PINB,high);
		DIO_WritePin(DATA_PINC,high);
		DIO_WritePin(DATA_PIND,low);
		break ;
		
		case 8 :
		DIO_WritePin(DATA_PINA,low);
		DIO_WritePin(DATA_PINB,low);
		DIO_WritePin(DATA_PINC,low);
		DIO_WritePin(DATA_PIND,high);
		break ;
		
		case 9 :
		DIO_WritePin(DATA_PINA,high);
		DIO_WritePin(DATA_PINB,low);
		DIO_WritePin(DATA_PINC,low);
		DIO_WritePin(DATA_PIND,high);
		break ;
          
		  
		  default:
		  break;
		
	}
}*/
void BCDSevegments_displayNo (uint8 Display_Number){
	
	PORTB=Display_Number;
}