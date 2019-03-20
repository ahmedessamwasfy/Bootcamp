/*
 * Timer.h
 *
 * Created: 2/21/2019 1:32:01 PM
 *  Author: AVE-LAP-005
 */ 


#ifndef TIMER_H_
#define TIMER_H_


#define NO_OF_TASKS 3
/*Choose The Interval you want for the tick timer witch n ms */
#define OS_TICK_INTERVAl_MSEC  1
/*APIS of Timer1 */
void Timer_Init();
void SystickHandler(void);
void Set_CallBack(void (*ptr)(void));

#endif
