
/*
 * Timer0.c
 *
 * Created: 2/14/2019 9:38:01 AM
 *  Author: AVE-LAP-005 */
#define F_CPU 16000000
#include "../Includes/Types.h"
#include "TM4C123GH6PM.h"
#include "../Includes/Utilites.h"
#include <stdbool.h>
#include <stdint.h>
#include "driverlib/interrupt.h"
#include "driverlib/systick.h"
#include "inc/hw_ints.h"
#include "inc/hw_nvic.h"
#include "../Includes/BitwiseOperations.h"
#include "../Includes/TIMER_Confg.h"
#include <Includes/Systick.h>
#include <stdio.h>



void (*Call_Back)(void)=NULL;
 
/****************************************************************************
*  INPUT:NOTHING
*  OUTPUT:NOTHING
* Description: This function Initilaize timer1 to be in the ctc mode
* with tick time equal to one millisecond

****************************************************************************/

 
 void Timer_Init()
 {	
    SYSCTL->RCGCGPIO|=0x20;
    GPIOF->DIR=0x0E;
    GPIOF->DEN=0x0E;
    SysTick->LOAD=TIMER_TICK;
    IntMasterEnable();
    SysTickIntEnable();
    SysTickIntRegister(SystickHandler);
    SysTickEnable();

	  
 }

/****************************************************************************
*  INPUT:Pointer to function
*  OUTPUT:NOTHING
* Description: This function used to set the callBack pinter to function to be equal 
* to the argument void (*ptr)(void)

****************************************************************************/
void Set_CallBack(void (*ptr)(void))
{
	
	Call_Back=ptr;
	
}

 
void SystickHandler(void)
{
     Call_Back();

 }

 
 
 

