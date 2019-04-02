#include <stdint.h>
#include <stdbool.h>
#include "Free_RTOS/FreeRTOS.h"
#include "Free_RTOS/task.h"
#include "Free_RTOS/event_groups.h"
#include "Free_RTOS/queue.h"
#include "includes/DIO.h"
#include "includes/uart.h"
#include "FSM.h"
#include "Manager.h"
#include "allignment.h"
#include "includes/spi.h"
/**********************************************/
/*the used MACROS*/
#define PRESSED 1
#define NOT_PRESSED 0
#define ZERO 0
#define ONE 1
#define FIVE 5
#define EIGHT 8
#define COMMAND_MASK 0xff
#define DATA_MASK 0x1f
#define TEN 10
#define TASK_TWO_DELAY 50


/*********************************************/
/*Transmitter Task*/
/*********************************************/

void Allignment_Task(void){

    uint8 Distance , Command; /* command which send by SPI to receiver */
    uint32 Data_to_send=ZERO; /* data which send by SPI to Receiver */
    while(!DIO_ReadPin(BUTTON1));/*if BUTTUN1 is pressed start system */
    while(1)
    {
        /*start the system */
        Data_to_send=ZERO;
        /*Get the distance*/
        Distance=Get_Distance();
        /*Get the Command*/
        Command=FSM(Distance);
        /* divide on EIGHT to scale the data to 5 bits */
        Distance /=EIGHT;
        /* Allignment the data least 5 bits contains the distance and the most 3 bits contains the command  */
        Data_to_send =(((Data_to_send & COMMAND_MASK)|Command)<<FIVE) |((Data_to_send & DATA_MASK)|Distance);
        /* Transmit the data */
       UART_Transmit(Data_to_send);/*check the sent data by echo it using UART */
	    SPI_sendByte(Data_to_send); /* send data by SPI to reciver */
        
    }


}


