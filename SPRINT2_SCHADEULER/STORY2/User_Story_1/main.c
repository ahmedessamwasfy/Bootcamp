
#include "includes/Types.h"
#include "includes/_TIMER_.h"
#include "includes/BitwiseOperations.h"
#include "includes/Task.h"
#include "includes/schadular.h"

int main(void)
{
	
    timer0_init_CTC_mode; 
    DIO_SetPinDirection(LED1,OUTPUT); /*Set DDRB5 (LED1) Output*/
    DIO_SetPinDirection(LED2,OUTPUT); /*Set DDRB6 (LED2) Output*/
    DIO_SetPinDirection(LED3,OUTPUT); /*Set DDRB7 (LED3) Output*/
	
    Task task1;
	task1.ptr_func=GO;
	task1.Task_Periodicity=1000;
	task1.Remaining_Ticks=1000;
	
	Task task2;
	task2.ptr_func=STOP;
	task2.Task_Periodicity=2000;
	task2.Remaining_Ticks=2000;  
	  
    Task task3;
    task3.ptr_func=READY;
	task3.Task_Periodicity=3000;
	task3.Remaining_Ticks=3000;
	  
	scheduler_Add_Task(&task1);
	scheduler_Add_Task(&task2);
	scheduler_Add_Task(&task3);
	schadular_init_start();/*initialize the schadular*/
    

}
	

		
	 



