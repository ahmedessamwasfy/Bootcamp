
#include "includes/Types.h"
#include "includes/_TIMER_.h"
#include "includes/BCDSevSegment.h"
#include "includes/KeyPad.h"
#include "includes/BitwiseOperations.h"


extern volatile uint16 g_tick;
extern volatile uint8 external_flag;
#define GO    0
#define READY 1
#define STOP  2
#define LED1  13
#define LED2  14
#define LED3   15
#define BTN1   10



int main(void)
{
	uint8 STATE = GO ;
    Set_Bit(MCUCSR,ISC2); 
    Set_Bit(GICR,INT2);
	timer0_init_CTC_mode();
    
    DIO_SetPinDirection(LED1,HIGH); /*Set DDRB5 (LED1) Output*/
    DIO_SetPinDirection(LED2,HIGH); /*Set DDRB6 (LED2) Output*/
    DIO_SetPinDirection(LED3,HIGH); /*Set DDRB7 (LED3) Output*/
    DIO_SetPinDirection(BTN1,LOW); /*Set DDRB2 (BTN1) Input*/

    DIO_WritePin(LED1,LOW); /*Led is off*/
    DIO_WritePin(LED2,LOW); /*Led is off*/
    DIO_WritePin(LED3,LOW); /*Led is off*/
    while (1) 
    {   
	switch (STATE)
	{
		case GO :
		DIO_WritePin(LED1,high); /*GO State*/
		DIO_WritePin(LED2,low);
		DIO_WritePin(LED3,low);

	    if(external_flag==NUMBER_ONE)
	       {
		     STATE = STOP ;
		     external_flag=NUMBER_ZERO;
		     g_tick = NUMBER_ZERO ;
		     break ;
         	}
		else if(g_tick >= NUMBER_OF_OVERFLOWS_PER_ONE_SECOND)/*check if external interrupt 2 accrue go to stop state */
		    {
			g_tick = NUMBER_ZERO ;
			STATE = STOP ;
		    }
		   break;
		
		case STOP :
		DIO_WritePin(LED1,low); /*Stop State*/
		DIO_WritePin(LED2,low);
		DIO_WritePin(LED3,high);
		
	    if(external_flag==NUMBER_ONE)/*check if external interrupt 2 accrue go to stop state */
    	{
	     	STATE = STOP ;
	    	external_flag=NUMBER_ZERO;
	     	g_tick = NUMBER_ZERO ;
	    	break ;
     	}
		else if(g_tick >= NUMBER_OF_OVERFLOWS_PER_ONE_SECOND)
		{
			g_tick = NUMBER_ZERO ;
			STATE = READY ;
		}
		break;
		
		case READY :     /*READY State*/
		DIO_WritePin(LED1,low);
		DIO_WritePin(LED2,high);
		DIO_WritePin(LED3,low);
		if(external_flag==NUMBER_ONE)/*check if external interrupt 2 accrue go to stop state */
		{
			STATE = STOP ;
			external_flag=NUMBER_ZERO;
			g_tick = NUMBER_ZERO ;
			break ;
		}
		else if(g_tick >= NUMBER_OF_OVERFLOWS_PER_ONE_SECOND)
		{
			g_tick = NUMBER_ZERO ;
			STATE = GO ;
		}
		break;
		default :
		STATE = GO ;
		break;
	}
}
}
	

		
	 



