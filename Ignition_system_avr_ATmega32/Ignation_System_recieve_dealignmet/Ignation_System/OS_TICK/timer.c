#include "../includes/Std_Types.h"
#include "../includes/BitwiseOperations.h"
#include "../includes/numbers.h"
#include "../includes/atmega32.h"
#include "../includes/Timer.h"
#include <avr/interrupt.h>



/* Global pointer to function used to point upper layer functions
 * to be used in Call Back */
static  void(*timer0_callbackptr)(void);

/************************************************************************************
* Function Name:    timer0_setcallback
* Parameters (in):  (*ptrcallback )
* Parameters (inout):timer0_callbackptr
* Parameters (out): None 
* Return value: void
* Description:Function that save a callback pointer
************************************************************************************/
void timer0_setcallback(void(*ptr2Func )(void))
{
	timer0_callbackptr=ptr2Func;	
}
/*********************************************************************************************/

/************************************************************************************
* Function Name:        timer0_os_init
* Parameters (in):      void
* Parameters (inout):   TIMSK        Timer Interrupt Mask
*                       TCCR0        timer0/counter control register
*                       OCR0         Output Compare match Value
* Parameters (out):     void
* Return value:         void  
* Description:Initialize timer0 for OS usage with systec = 1 ms
************************************************************************************/
void timer0_os_init()
{
		 
		TCCR0=NUM_ZERO;                       /* Disable timer0 */ 
		Set_Bit(TIMSK,OCIE0);                 /* Enable OC Interrupt */
		
		/* Select timer0 clk mode for prescale 64 CS02=0 CS01=1 CS00=1 */
		Set_Bit(TCCR0,CS00);                  
		Set_Bit(TCCR0,CS01);
		Clear_Bit(TCCR0,CS02);
				
		/* Normal port operation, OC0 disconnected COM01=0, COM00=0 */
		Clear_Bit(TCCR0,COM00);
		Clear_Bit(TCCR0,COM01);
		
		/* Select mode 2(CTC)  WGM01= 1,WGM00=0 */
		Clear_Bit(TCCR0,WGM00);
		Set_Bit(TCCR0,WGM01);
		
		/* For non PWM operation FOC0=1 */
		Set_Bit(TCCR0,FOC0);
		
		OCR0=NUM_249;      /* OCR0= 16M /( 1KHZ (1 ms)  * 64 (prescale) -1 */
		
	}



/************************************************************************************
* Function Name:      PWM_timer1A
* Parameters (in):    uint8 duty_cycle
* Parameters (inout): OCR1AH
*                     OCR1AL
*                     TCNT1H
*                     TCNT1L
* Parameters (out):   void
* Return value:       void
* Description:        Function that generate PWM  with specific duty_cycle Value
************************************************************************************/

void PWM_timer1A(uint8 duty_cycle){
	if(duty_cycle<=NUM_100){
		uint16 compare_value=duty_cycle*MAX_10BITS/NUM_100;
		OCR1AH =(compare_value>>NUM_8);
		OCR1AL =compare_value;
		TCNT1H=NUM_ZERO;
		TCNT1L=NUM_ZERO;
		
	}
	else {}
	
	
	
}


/************************************************************************************
* Function Name:      PWM_timer1B
* Parameters (in):    uint8 duty_cycle
* Parameters (inout): OCR1BH
*                     OCR1BL
*                     TCNT1H
*                     TCNT1L
* Parameters (out):   void
* Return value:       void
* Description:        Function that generate PWM  with specific duty_cycle Value
************************************************************************************/
void PWM_timer1B(uint8 duty_cycle){
	if(duty_cycle<=NUM_100){
		uint16 compare_value=duty_cycle*MAX_10BITS/NUM_100;
		OCR1BH =(compare_value>>NUM_8);
		OCR1BL =compare_value;
		TCNT1H=NUM_ZERO;
		TCNT1L=NUM_ZERO;
		
	}
	else {}
	
	
	
}
/************************************************************************************
* Function Name:       PWM_init
* Parameters (in):     void
* Parameters (inout):  TCCR1A
*                      TCCR1B
* Parameters (out):    void
* Return value:        void
* Description:         Function that initialize timer1 as PWM 10BITS on non_inverting mode
************************************************************************************/
void PWM_init(){
	/* TCCR1A         COM1A1 COM1A0 COM1B1 COM1B0 FOC1A FOC1B WGM11 WGM10  */
	/* for 10 bit        1      0      1     0      0      0     1     1
      non_inverting mode
	 */ 
	
	TCNT1H=NUM_ZERO;
	TCNT1L=NUM_ZERO;
	Set_Bit(TCCR1A,WGM10);
	Set_Bit(TCCR1A,WGM11);
	Clear_Bit(TCCR1A,FOC1B);
	Clear_Bit(TCCR1A,FOC1A);
	Clear_Bit(TCCR1A,COM1B0);
	Set_Bit(TCCR1A,COM1B1);
	Clear_Bit(TCCR1A,COM1A0);
	Set_Bit(TCCR1A,COM1A1);
    /*   TCCR1B         ICNC1 ICES1  –  WGM13 WGM12 CS12 CS11 CS10 110 */
    /* for 10 bit
      non_inverting mode  0      0   0    0     1     0     0    1 
    */
	 
	Set_Bit(TCCR1B,CS10);
	Clear_Bit(TCCR1B,CS11);
	Clear_Bit(TCCR1B,CS12);
	Set_Bit(TCCR1B,WGM12);
	Clear_Bit(TCCR1B,WGM13);
	Clear_Bit(TCCR1B,ICES1);
	Clear_Bit(TCCR1B,ICNC1);
		
}
/************************************************************************************
* Function Name:        timer_mdelay
* Parameters (in):      uint16 delay  delay time in ms
* Parameters (inout):   TIMSK         Timer Interrupt Mask
*                       TCCR2         timer2/counter control register
*                       OCR2          Output Compare match Value
* Parameters (out):     void
* Return value:         void
* Description:Initialize timer2 for OS usage with systec = 1 ms
************************************************************************************/

volatile static uint16 timer2_counter; /* static global variable count timer2 oc counts*/ 
void timer_mdelay(uint16 delay)
{   
	
	timer2_counter=NUM_ZERO;
	/* Disable timer2 */
	TCCR2=NUM_ZERO;
    /* Enable timer2 compare match Interrupt*/
	Set_Bit(TIMSK,OCIE2);
	
	/* Select timer2 clk mode for prescale 64 CS22=1 CS21=0 CS20=0 */
	Clear_Bit(TCCR2,CS20);
	Clear_Bit(TCCR2,CS21);
	Set_Bit(TCCR2,CS22);
			
	/* Normal port operation, OC2 disconnected COM21=0, COM20=0 */
	Clear_Bit(TCCR2,COM20);
	Clear_Bit(TCCR2,COM21);

    /* Select mode 2(CTC)  WGM21 =1,WGM00 =0 */
	Clear_Bit(TCCR2,WGM20);
	Set_Bit(TCCR2,WGM21);
	
	Set_Bit(TCCR2,FOC2);
	OCR2=NUM_249;      /* OCR2= 16M /( 1KHZ (1 ms)  * 64 (prescale)-1 */
	while (delay !=timer2_counter)
	{
	}
	timer2_counter=NUM_ZERO;
}

/* Interrupt Service Routine for Timer0 compare mode */
ISR(TIMER0_COMP_vect)
{
	
	
	/* Check if the Timer0_setCallBack is already called */
	if(timer0_callbackptr != NULL)
	{
		(*timer0_callbackptr)(); /*call the function in the scheduler using call-back concept */
	}
		
}
/* Interrupt Service Routine for Timer2 compare mode */
ISR(TIMER2_COMP_vect){
	
	timer2_counter +=NUM_1;     /* Increment timer2_counter */
	
}
	

	

	
	