
#include "include/FreeRTOS.h"
#include "include/task.h"
#include "include/event_groups.h"
#include "include/queue.h"
#include "LCD.h"
#include "spi.h"
#include "De-Allignment.h"

/***********************************************/
              /* the used MACROS*/
/***********************************************/
#define ZERO 0
#define EIGHT 8
#define THREE 3
#define ONE 1
#define FIVE 5
#define DATA_MASK 0x000000ff
#define DISTANCE_MASK 0x1f
#define FIVE 5
#define CLEAR_DISPLAY 0x01
uint8_t InitFlag=ZERO ;
QueueHandle_t SPI_Queue;

/***********************************************/
              /* Initialization Task*/
/***********************************************/
void Init_Task(void){
    while(1){
        if(!InitFlag){
        /*LCD initialization*/
        LCD_init();

        /*SPI initialization*/
        SPI_Init(THREE);

        InitFlag=ONE;
        }
        vTaskSuspend(NULL);
    }
}

/***********************************************/
              /*Reciever Task*/
/***********************************************/
void De_allignment_Task(void){
    if (InitFlag)
    {

        uint32_t Data_to_recieve ;
        uint8_t Distance ;
        uint8_t Command ;
        while(1)
        {
            /* check if there is smth in the queue*/

            if( xQueueReceive( SPI_Queue, &( Data_to_recieve ), ( TickType_t ) 10 ) )
                    {
                        /*CLEAR_DISPLAY*/
                        LCD_sendCommand(CLEAR_DISPLAY);
                        /* De-allign the data from the queue */
                        Data_to_recieve&=(DATA_MASK);
                        /*set the distance*/
                        Distance=(uint8_t)((Data_to_recieve&DISTANCE_MASK)*EIGHT);
                        /*Set the command*/
                        Command=(uint8_t)(Data_to_recieve >>FIVE);
                        /*Display the commend*/
                        switch(Command){
                            case 1:
                                LCD_displayString("Maintain Speed");
                                break ;
                            case 2:
                                LCD_displayString("Increase Speed");
                                break;
                            case 3:
                                LCD_displayString("Decrease speed");
                                break ;
                            case 4:
                                LCD_displayString("Brake");
                                break ;
                            case 5:
                                LCD_displayString("Fire Air-bag");
                                break ;
                        }
                        if(Command<5){
                            /*Display the Distance*/
                            LCD_gotoRowColumn(2,0);
                            LCD_displayString("distance: ");
                            LCD_gotoRowColumn(2,9);
                            LCD_displayData(Distance);

                        }
                    }

            vTaskDelay(100);
        }
    }
}

/***********************************************/
              /* SPI Task*/
/***********************************************/
void SPI_Task(void){
    if (InitFlag)
    {

        uint32_t Data_to_send;
        while(1){
            /*Recive the Message from The SPI and put it in the SPIQueue*/
            if(SPI_Recieve(&Data_to_send))
            {
                /*Put the data in the queue*/
                xQueueOverwrite( SPI_Queue, &(Data_to_send) );
            }
            vTaskDelay(190);
        }

    }
}
