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
/* Function that initialize timer zero COMPRATE MODE  */

void timer0_init_CTC_mode(void)
{
	TCNT0=NUMBER_ZERO;
	OCR0=OCR0_VALUE_REGISTER;
	TIMSK|=(NUMBER_ONE<<OCIE0);
	TCCR0|= (NUMBER_ONE<<WGM01) | (NUMBER_ONE<<CS01) | (NUMBER_ONE<<CS00);
    Set_Bit(SREG,IBIT);
}
/* ISR_INT2_Init */
/* Parameters : N/A */
/* I/p : N/A */
/* O/p : N/A */
/* Return : void */
/* Function that initialize EXTERNAL INT2 */
void ISR_INT2_Init(void)
{
	Set_Bit(MCUCSR,ISC2);
	Set_Bit(GICR,INT2);
}


/* pwm1_init() */
/* Parameters : N/A */
/* I/p : N/A */
/* O/p : N/A */
/* Return : void */
/* Function that initialize pwm at fast mode 14 */	
void pwm1_init()
{
	TCNT1H = NUMBER_ZERO;
	TCNT1L = NUMBER_ZERO;
	
	ICR1H = (TOP_VALUE>>8); /* TOP REGISTER FOR MAX VALUE HIGH */
	ICR1L = TOP_VALUE;/* TOP REGISTER FOR MAX VALUE LOW */
	
	/*COMPARE REGISTER AS FAST PWM IN TIMER 1 TABLE MODE 14 INITIALIZE WITH ZERO AND CHANGED IN 
	SELECT_DUTY(uint8 duty) FUNCTION */
	OCR1AL=NUMBER_ZERO;
	OCR1AH=NUMBER_ZERO;
	OCR1BH=NUMBER_ZERO;
	OCR1BL=NUMBER_ZERO;

	DIO_SetPinDirection(OC1B,OUTPUT);/*ENABLE  PWM Pins as Out (OCR1B) NUMBER 28 FOR MOTOR A */
	DIO_SetPinDirection(OC1A,OUTPUT);/* ENABLE PWM Pins as Out (OCR1A) NUMBER 29 FOR MOTOR B  */
	
	/*MOTOR 1 AND 2 DIRECTION PINS AS OUTPUT */
	DIO_SetPinDirection(MOTOR1_DIR_A1,OUTPUT);
	DIO_SetPinDirection(MOTOR1_DIR_B1,OUTPUT);
	DIO_SetPinDirection(MOTOR2_DIR_A2,OUTPUT);
	DIO_SetPinDirection(MOTOR2_DIR_B2,OUTPUT);
	
	#if(DIRECTION == BACKWORD)
	DIO_WritePin(MOTOR1_DIR_A1,HIGH);
	DIO_WritePin(MOTOR1_DIR_B1,LOW);
	DIO_WritePin(MOTOR2_DIR_A2,HIGH);
	DIO_WritePin(MOTOR2_DIR_B2,LOW);
	#elif(DIRECTION == STOP)
	DIO_WritePin(MOTOR1_DIR_A1,LOW);
	DIO_WritePin(MOTOR1_DIR_B1,LOW);
	DIO_WritePin(MOTOR2_DIR_A2,LOW);
	DIO_WritePin(MOTOR2_DIR_B2,LOW);
	#elif(DIRECTION==FORWARD)
    DIO_WritePin(MOTOR1_DIR_A1,LOW);
    DIO_WritePin(MOTOR1_DIR_B1,HIGH);
	DIO_WritePin(MOTOR2_DIR_A2,LOW);
	DIO_WritePin(MOTOR2_DIR_B2,LOW);
	#endif
	/*TIMER 1 FAST PWM REGISTERS FOR MODE 14 AND PRESCALER 256 AND NON INVERTING MODE */
	Set_Bit(TCCR1A,COM1A1);/*NON INVERTING FAST PWM */
	Set_Bit(TCCR1A,COM1B1);/*NON INVERTING FAST PWM */
	Set_Bit(TCCR1A,WGM11);/*MODE 14 FAST PWM ICE1 */
	Set_Bit(TCCR1B,WGM12);/*MODE 14 FAST PWM ICE1 */
	Set_Bit(TCCR1B,WGM13);/*MODE 14 FAST PWM ICE1 */
	Set_Bit(TCCR1B,CS12);/*SELECT PRESCALER = 256*/
}


void SELECT_DUTY(float duty)
{  
	/*uint16 compare = (duty*TOP_VALUE)/100;*/
	/*OCR1AH=(compare>>8); 
	OCR1AL=(compare);
	OCR1BH=(compare>>8);
	OCR1BL=(compare);*/
	uint16 compare = (uint16)((duty/100)*(TOP_VALUE+1));
	OCR1AH = compare >> 8 ;
	OCR1AL = compare ;
	OCR1BH = compare >> 8 ;
	OCR1BL = compare ;
}