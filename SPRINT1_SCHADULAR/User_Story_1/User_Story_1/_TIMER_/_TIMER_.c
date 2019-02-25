#include "../includes/_TIMER_.h"


volatile uint16 g_tick = NUMBER_ZERO;  /* FLAG FOR TIMER ZERO COMPRE INTERRUPT */

volatile uint8 external_flag =NUMBER_ZERO ; /* FLAG FOR EXTERNAL INTEERUPT 2 */


/* Interrupt Service Routine for timer0 compare mode */
ISR(TIMER0_COMP_vect)
{
		g_tick++;
}
/* Interrupt Service Routine EXTERNAL INTERRUPT mode */

ISR(INT2_vect)
{
	external_flag = NUMBER_ONE ;
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
	TIMSK|=(NUMBER_ONE<<OCIE0);
	TCCR0|= (NUMBER_ONE<<WGM01) | (NUMBER_ONE<<CS01) | (NUMBER_ONE<<CS00);
    Set_Bit(SREG,IBIT);
}
/* timer_init */
/* Parameters : N/A */
/* I/p : N/A */
/* O/p : N/A */
/* Return : void */
/* Function that initialize external interrupt 2 */
void ISR_INT2_Init(void)
{
	Set_Bit(MCUCSR,ISC2);
	Set_Bit(GICR,INT2);
}


	
