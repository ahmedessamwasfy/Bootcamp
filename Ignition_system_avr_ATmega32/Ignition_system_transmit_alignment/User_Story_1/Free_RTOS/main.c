#include <avr/io.h>
#include "../includes/DIO.h"
#include "../includes/Types.h"
#include "../includes/BitwiseOperations.h"
#include "../allignment.h"
#include "FreeRTOS.h"
#include "task.h"

/****************************MASTER alignment*************************/
int main(void)
{
	SPI_initMaster();/*INIT master */
	UART_Inti();/*INIT FUN FOR UART */
	DIO_SetPinDirection(BUTTON1,INPUT);/* BUTTON1 as input */ 
	
	/*********************************
	1-Start system by press the BUTTON1 on MASTER ECU
	 
	2-call get_distance(); function which take the duty cycle which come from UART 
	and make calculation to get distance the return distance .
	
	3-call FSM(); function which responce to calculate the current state depend on 
	distance which came from get_distance(); function .
	
	4-make alignment algorithm for distance and command.
	 
	5- final data to send variable equal the data least 5 bits contains 
	the distance and the most 3 bits contains the command.
	
	6- send data to send variable by SPI to dealignment data and receive it by receiver .
	***********************************/
	
	Allignment_Task();

	
}