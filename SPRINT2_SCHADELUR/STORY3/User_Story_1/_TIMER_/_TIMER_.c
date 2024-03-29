#include "../includes/_TIMER_.h"


volatile uint16 g_tick = NUMBER_ZERO;  /* FLAG FOR TIMER ZERO COMPRE INTERRUPT */
void (*global_ptr)(void);/*GLOBAL POINTER TO STORE THE ADDRESS OF CALL BACK FUNCTION AND USE IT INSIDE isr */

/* Interrupt Service Routine for timer0 compare mode */
ISR(TIMER0_COMP_vect)
{
		global_ptr();
		
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
	TIMSK|=(NUMBER_ONE<<OCIE0);/*TIMER INTERRUPT ENABLE FOR COMPARE MATCH */
	TCCR0|= (NUMBER_ONE<<WGM01) | (NUMBER_ONE<<CS01) | (NUMBER_ONE<<CS00);/*prescaler */
    Set_Bit(SREG,IBIT);/*ENABEL GLOBAL INTERRUPT BIT IN SREG REGISTER */
}



	
