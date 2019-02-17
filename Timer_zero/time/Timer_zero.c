#include "Timer_zero.h"

timer_init()
{
		
	Set_Bit(TCCR0 , 3);
    Set_Bit(TCCR0 , 7);
	Set_Bit(TCCR0 , 1);
	Set_Bit(TCCR0 , 0);
	
	OCR0 = 250 ;
	TCNT0= 0 ;
	
}
timer_delay(uint32 n)
{
	TCNT0 = 0 ;
	for(n ; n>0 ; n--)
	{
		while()
		
	}
}

