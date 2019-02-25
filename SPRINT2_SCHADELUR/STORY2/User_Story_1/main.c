
#include "includes/Types.h"
#include "includes/_TIMER_.h"
#include "includes/BitwiseOperations.h"
#include "includes/Task.h"
#include "includes/schadular.h"

int main(void)
{
	
    timer0_init_CTC_mode;            /*Timer compare mode initialization */
    DIO_SetPinDirection(LED1,OUTPUT); /*Set DDRB5 (LED1) Output*/
    DIO_SetPinDirection(LED2,OUTPUT); /*Set DDRB6 (LED2) Output*/
    DIO_SetPinDirection(LED3,OUTPUT); /*Set DDRB7 (LED3) Output*/
	
	/*temporary structure to assign them inside the add fun in each element of array of structure */
    Task task1; 
	task1.ptr_func=GO;
	task1.Task_Periodicity=ONE_SECOUND;
	task1.Remaining_Ticks=ONE_SECOUND;
	
	
	/*temporary structure to assign them inside the add fun in each element of array of structure */
	Task task2;
	task2.ptr_func=STOP;
	task2.Task_Periodicity=TWO_SECOND;
	task2.Remaining_Ticks=TWO_SECOND; 
	 
	 /*temporary structure to assign them inside the add fun in each element of array of structure */
    Task task3;
    task3.ptr_func=READY;
	task3.Task_Periodicity=THREE_SECOUND;
	task3.Remaining_Ticks=THREE_SECOUND;

	 /*call add task function that take structure and we assign the elements of each structure */
	scheduler_Add_Task(&task1);/* send the address of structure task1 to add function */
	scheduler_Add_Task(&task2);/* send the address of structure task2 to add function */
	scheduler_Add_Task(&task3);/* send the address of structure task3 to add function */
	schadular_init_start();/*initialize the scheduler */
    

}
	

		
	 



