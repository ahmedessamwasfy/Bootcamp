


#include "../includes/Std_Types.h"
#include "../includes/numbers.h"
#include "../Free_RTOS/FreeRTOS.h"
#include "../Free_RTOS/task.h"

#include "../FSM/FSM.h"
#include "../Manger/Manager.h"

#include "../UART/uart.h"
#include "../SPI/spi.h"
#include "../_LCD/lcd.h"
#include "De-Allignment.h"
/***********************************************/
              /* the used MACROS*/
/***********************************************/

#define DATA_MASK 0x000000ff
#define DISTANCE_MASK 0x1f
uint8 InitFlag=NUM_ZERO ;
uint8 Data_to_recieve ;
/***********************************************/
              /* Initialization Task*/
/***********************************************/
void Init_Task(void){
    while(1){
        if(!InitFlag){
        /*LCD initialization*/
        LCD_init();
        LCD_displayChar('A');
		LCD_displayChar('B');
		LCD_displayChar('C');
		LCD_displayChar('D');
		LCD_displayChar('E');

        /*SPI initialization*/
        SPI_SlaveInit();
        
        InitFlag=NUM_1;
        }
		
        vTaskSuspend(NULL);
    }
}


/***********************************************/
              /*Reciever Task*/
/***********************************************/
void LCD_displayData(uint8_t data){
	uint8_t i;
	uint8_t remind;
	if(data>=100)
	{
		i=data/100;
		LCD_displayChar(i+'0');
		data=data-(i*100);
	}
	if(data>=10)
	{
		i=data/10;
		LCD_displayChar(i+'0');
		data=data-(i*10);
	}
	LCD_displayChar(data+'0');

}
void De_allignment_Task(void){
    

        
        uint8 Distance ;
        uint8 Command ;
        while(1)
        {
            /* check if there is smth in the queue*/
            Data_to_recieve=SPI_Recieve();
            if(Data_to_recieve)
                    {
                        /*CLEAR_DISPLAY*/
                        LCD_clear();
                        /* De-allign the data from the queue */
                        Data_to_recieve&=(DATA_MASK);
                        /*set the distance*/
                        Distance=(uint8)((Data_to_recieve&DISTANCE_MASK)*NUM_8);
                        /*Set the command*/
                        Command=(uint8)(Data_to_recieve >>NUM_5);
						Data_to_recieve=NUM_ZERO;

                        /*Display the commend*/
                        switch(Command){
                            case NUM_1:
                                LCD_displayString("Maintain Speed",NUM_15);
                                break ;
                            case NUM_2:
                                LCD_displayString("Increase Speed",NUM_15);
                                break;
                            case NUM_3:
                                LCD_displayString("Decrease speed",NUM_15);
                                break ;
                            case NUM_4:
                                LCD_displayString("Brake",NUM_6);
                                break ;
                            case NUM_5:
                                LCD_displayString("Fire Air-bag",NUM_13);
                                break ;
                        }
                       


					    if(Command<NUM_5){
                            /*Display the Distance*/
                            LCD_gotoRowColumn(LCD_RAW1,LCD_COLUMN0);
                            LCD_displayString("distance: ",NUM_10);
                            LCD_gotoRowColumn(LCD_RAW1,LCD_COLUMN9);
                            LCD_displayData(Distance);

                        }
						

					}
        }
    
}

/***********************************************/
              /* SPI Task*/
/***********************************************/
void SPI_Task(void){
    
        uint32_t Data_to_send;
        while(1)
		{
			   
               

               vTaskDelay(NUM_50/portTICK_RATE_MS);
           

      }
}
