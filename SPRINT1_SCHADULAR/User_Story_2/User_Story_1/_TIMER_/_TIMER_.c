#include "../includes/_TIMER_.h"


volatile uint16 g_tick = NUMBER_ZERO;  /* FLAG FOR TIMER ZERO COMPRE INTERRUPT */


/*global pointer to function that take the address of called back function to use it inside ISR */
void (*global_ptr)(void);


/* Interrupt Service Routine for timer0 compare mode */
ISR(TIMER0_COMP_vect)
{
		global_ptr();/*address of function that called by call back */
		
}



/*set_callback */
/* Parameters : N/A */
/* I/p : pointer to function that void/void */
/* O/p : N/A */
/* Return : void */
/* Function that takes pointer to fun to use it inside ISR */
void set_call_back(void (*gptr)(void))
{
	global_ptr=gptr;
}



/* timer_init */
/* Parameters : N/A */
/* I/p : N/A */
/* O/p : N/A */
/* Return : void */
/* Function that initialize timer zero */
void timer0_init_CTC_mode(void)
{
	TCNT0=NUMBER_ZERO;/*timer register zero TCNT0 start from zero */
	OCR0=OCR0_VALUE_REGISTER;/*compare register value */
	TIMSK|=(NUMBER_ONE<<OCIE0);/*interrupt enable module for compare mode in timer */
	TCCR0|= (NUMBER_ONE<<WGM01) | (NUMBER_ONE<<CS01) | (NUMBER_ONE<<CS00);
    Set_Bit(SREG,IBIT);/*enable global interrupt bit 7 */
}



	
