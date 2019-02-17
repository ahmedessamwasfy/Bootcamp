#include "Timer_zero.h"

void timer_init()
{
	
	/* WGM01 bit to activate CTC mode */
	Set_Bit(TCCR0 , 3);
	
	/* force output compare bit */
    Set_Bit(TCCR0 , 7);
	
	/* 64 PRESCALER CS00 , CS01 */
	Set_Bit(TCCR0 , 1);
	Set_Bit(TCCR0 , 0);
	
	/* Compare register value */
	OCR0 = 250 ;
	
	/* Timer initial value */
	TCNT0= 0 ;
	
}
void timer_delay(uint32 n)
{
	/* TO EARASE FLAG COMPARE */
	Set_Bit(TIFR,1);
	/* INITIAL VALUE FOR TCNT REGISTER */
	TCNT0 = 0 ;
	for(n , n>0 , n--)
	{
		while(!(get_bit(TIFR,1)))
		{
			
		}
			Set_Bit(TIFR,1);

	}
}

