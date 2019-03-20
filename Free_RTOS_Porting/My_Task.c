#include "BUZZER.h"
#include "LED.h"
#include "BTN.h"
#include "LCD.h"
#include "FreeRTOS.h"
#include "include/task.h"
#include "queue.h"
QueueHandle_t    Quee;

/*uint8_t BTN2_FLAG = 0 ;led
uint8_t BTN1_FLAG = 0 ;lcd*/
volatile uint8_t BTN2_COUNTER = 0 ;
volatile uint8_t BTN1_COUNTER = 0 ;

/* INIT tasks  */
/* Parameters : N/A */
/* I/p : N/A */
/* O/p : N/A */
/* Return : void  */
/* Function that initilize LED , buzzer , BTN , LCD */
void vTaskCode( void * pvParameters )
    {

        for( ;; )
        {

            LEDTaskInit();
            Buzzer_Init();
            Btns_Init();
            LCD_INIT();
            vTaskSuspend(NULL);
        }
    }



/* BTN2 tasks  */
/* Parameters : N/A */
/* I/p : N/A */
/* O/p : N/A */
/* Return : void  */
/* Function that get status of BTN2 */
void vTaskCode3( void * pvParameters )
    {
         static uint8_t state=0;
         uint8_t data_btn2 =1 ;
         uint8_t BTN2_FLAG=0;
        for( ;; )
        {
           state = Btn2_Read();

           if(state == BTN1_ON && BTN2_FLAG==0)
           {
               xQueueSend(Quee,&data_btn2,10);
           }
           BTN2_FLAG = state ;
           vTaskDelay(30);

        }
    }



/* BTN1 tasks  */
/* Parameters : N/A */
/* I/p : N/A */
/* O/p : N/A */
/* Return : void  */
/* Function that get status of BTN1 */
void vTaskCode6( void * pvParameters )
    {
         static uint8_t state=0;
         uint8_t BTN1_FLAG=0;
         uint8_t data_btn1 =2 ;

        for( ;; )
        {
           state = Btn1_Read();
           if(state == BTN1_ON && BTN1_FLAG==0)
           {
               xQueueSend(Quee,&data_btn1,10);

           }
           BTN1_FLAG = state ;

           vTaskDelay(30);

        }
    }






/* LCD tasks  */
/* Parameters : N/A */
/* I/p : N/A */
/* O/p : N/A */
/* Return : void  */
/* Function that display LCD  */
void vTaskCode5( void * pvParameters )
{
    uint8_t recive =0;
    for( ;; )
    {
        xQueueReceive(Quee, &recive, 10);
       if(recive==1)
       {
           LCD_DISPLAY1(BTN1_COUNTER);
           BTN1_COUNTER++;
           vTaskDelay(5);
           if(BTN1_COUNTER>9)
            {
             BTN1_COUNTER=0;
            }
           recive = 0 ;
       }
       else if(recive==2)
       {
           LCD_DISPLAY2(BTN2_COUNTER);
           BTN2_COUNTER++;
           vTaskDelay(5);
           if(BTN2_COUNTER>9)
           {
            BTN2_COUNTER=0;
           }
           recive = 0 ;
       }

        vTaskDelay( 20 );
    }
}
