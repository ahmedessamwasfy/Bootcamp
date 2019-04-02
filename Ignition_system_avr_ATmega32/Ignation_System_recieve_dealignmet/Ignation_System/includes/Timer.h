
#ifndef TIMER_DELAY
#define TIMER_DELAY

 void timer_mdelay(uint16 delay);
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
 void timer0_os_init();
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
 void PWM_init();
 /************************************************************************************
 * Function Name:       PWM_init
 * Parameters (in):     void
 * Parameters (inout):  TCCR1A
 *                      TCCR1B
 * Parameters (out):    void
 * Return value:        void
 * Description:         Function that initialize timer1 as PWM 10BITS on non_inverting mode
 ************************************************************************************/
 
 void PWM_timer1A(uint8 duty_cycle);
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
 
 void PWM_timer1B(uint8 duty_cycle);
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
 void timer0_setcallback(void(*ptr2Func )(void));
 /************************************************************************************
 * Function Name:    timer0_setcallback
 * Parameters (in):  (*ptrcallback )
 * Parameters (inout):timer0_callbackptr
 * Parameters (out): None
 * Return value: void
 * Description:Function that save a callback pointer
 ************************************************************************************/
 
#endif
