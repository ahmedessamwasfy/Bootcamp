
#include "../includes/Std_Types.h"
#include "../includes/numbers.h"
#include "../Free_RTOS/FreeRTOS.h"
#include "../Free_RTOS/task.h"
#include "../includes/BitwiseOperations.h"
#include "../Dio/DIO_prog.h"
#include "../includes/Timer.h"
#include "lcd_config.h"
#include "lcd.h"

#define LCD_CLEAR       0X01
#define LCD_HOME        0X02
#define LCD_INCREMENT   0X14
#define	LCD_DISPLAY_ON  0X0F
#define LCD_FIRST_LINE  0X80
#define LCD_SECOND_LINE 0XC0
#define LCD_4BIT_MODE   0X28
#define LCD_8BIT_MODE   0X38
#define LCD_WAKEUP      0X30
#define LCD_CURSOR_OFF  0X0C
#define LCD_CUSTOM_1    0x40
#define LCD_CUSTOM_2    0x48
#define LCD_CUSTOM_3    0x50
#define LCD_CUSTOM_4    0x58
#define LCD_CUSTOM_5    0x60
#define LCD_CUSTOM_6    0x68
#define LCD_CUSTOM_7    0x70
#define LCD_CUSTOM_8    0x78



#if(LCD_TYPE==LCD_4BIT_TYPE)
/************************************************************************************
* Function Name:        LCD_init
* Parameters (in):      void
* Parameters (inout):   LCD_RS ,LCD_RW,LCD_E,LCD_D4,LCD_D5,LCD_D6,LCD_D7 
* Parameters (out):     void
* Return value:         void
* Description:          Function that initialize the LCD 
************************************************************************************/
void LCD_init()
{
	
	DIO_SetPinDirection(LCD_RS,OUTPUT);     /* Set LCD_RS OUTPUT */
	DIO_SetPinDirection(LCD_RW,OUTPUT);     /* Set LCD_RW OUTPUT */
	DIO_SetPinDirection(LCD_E,OUTPUT);      /* Set LCD_E OUTPUT */
	
	DIO_SetPinDirection(LCD_D4,OUTPUT);     /* Set LCD_D4 OUTPUT */
	DIO_SetPinDirection(LCD_D5,OUTPUT);     /* Set LCD_D5 OUTPUT */
    DIO_SetPinDirection(LCD_D6,OUTPUT);     /* Set LCD_D6 OUTPUT */
	DIO_SetPinDirection(LCD_D7,OUTPUT);     /* Set LCD_D7 OUTPUT */
	timer_mdelay(TIME_10MS);
	//vTaskDelay(TIME_10MS/portTICK_RATE_MS);             /* Delay 10m second until the power steady */
	LCD_sendCommand(LCD_WAKEUP);          /* Send command to wake up #1 */
	timer_mdelay(TIME_5MS);
	//vTaskDelay(TIME_5MS/portTICK_RATE_MS);              /* Must delay more than 5m second */
	LCD_sendCommand(LCD_WAKEUP);          /* Send command to wake up #2 */
	
	//vTaskDelay(TIME_5MS/portTICK_RATE_MS);                /* Must delay more than 1m second */
	LCD_sendCommand(LCD_WAKEUP);          /* Send command to wake up #3 */
	timer_mdelay(TIME_5MS);               /* Must delay more than 1m second */
	LCD_sendCommand(LCD_HOME);            /* Send Home (0x02) command which initializes LCD 16x2 in 4-bit mode */
	LCD_sendCommand(LCD_4BIT_MODE);       /* Send 4BIT_MODE (0x28) command which configures LCD in 2-line, 4-bit mode and 5x8 dots */
    LCD_sendCommand(LCD_DISPLAY_ON);      /* SEND LCD_DISPLAY_ON(0X0F) display on,CURSOR_ON*/
	LCD_sendCommand(LCD_CLEAR);           /* Clear Screen */
	
	

}
/************************************************************************************
* Function Name:       LCD_sendCommand
* Parameters (in):     uint8 command
* Parameters (inout):  LCD_RS ,LCD_RW,LCD_E,LCD_D4,LCD_D5,LCD_D6,LCD_D7
* Parameters (out):    void
* Return value:        void
* Description:         Function that send acommand to the LCD
************************************************************************************/
void LCD_sendCommand(uint8 command)
{
	uint8 LCD_D4_value;                   
	uint8 LCD_D5_value;
	uint8 LCD_D6_value;
	uint8 LCD_D7_value;
	/* For 4_bit_Mode we have to divide the uint8 to 2 (4bits) and send the most 4bits then send the least 4bits
	 * for example :command = 0x52 which is 0b 0101 0010
	 * so we have to send 0b0101 (0x5) first then send 0b0010 (0x2)
	 * first  send   LCD_D7_value =0 ,LCD_D6_value=1 LCD_D5_value=0  LCD_D4_value=1
	 * second send   LCD_D7_value =0 ,LCD_D6_value=0 LCD_D5_value=1  LCD_D4_value=0
	 *  sequence : 1- Make E 0 RS O (Command) RW 0 (write) 
	              2- Get #1 LCD_D4:D7_value using Get_Bit
	              3- Write Data Pins with Values
				  4- Enable
				  5- delay
				  6- disable
				  7- Get #2 LCD_D4:D7_value using Get_Bit
				  8- Write Data Pins with Values
				  9- Enable
				  10-delay
				  11-disable*/
    DIO_WritePin(LCD_E,STD_LOW);              /* Disable LCD*/
	DIO_WritePin(LCD_RS,STD_LOW);             /* LCD_RS =0, Command*/
	DIO_WritePin(LCD_RW,STD_LOW);             /* LCD_Rw =0, Write */
	
	
	LCD_D4_value=Get_Bit(command,BIT4);     /* Get #1 LCD_D4:D7_value using Get_Bit*/
	LCD_D5_value=Get_Bit(command,BIT5);
	LCD_D6_value=Get_Bit(command,BIT6);
	LCD_D7_value=Get_Bit(command,BIT7);
	DIO_WritePin(LCD_D4,LCD_D4_value);     /* Write Data Pins with Values */
	DIO_WritePin(LCD_D5,LCD_D5_value);
	DIO_WritePin(LCD_D6,LCD_D6_value);
	DIO_WritePin(LCD_D7,LCD_D7_value);

	DIO_WritePin(LCD_E,STD_HIGH);              /* Enable */

    timer_mdelay(TIME_3MS);

	//vTaskDelay(TIME_1MS/portTICK_RATE_MS);                /* delay */
	DIO_WritePin(LCD_E,STD_LOW);               /* disable */
	LCD_D4_value=Get_Bit(command,BIT0);    /* Get #2 LCD_D4:D7_value using Get_Bit */
	LCD_D5_value=Get_Bit(command,BIT1);
	LCD_D6_value=Get_Bit(command,BIT2);
	LCD_D7_value=Get_Bit(command,BIT3);
	DIO_WritePin(LCD_D4,LCD_D4_value);     /* Write Data Pins with Values */
	DIO_WritePin(LCD_D5,LCD_D5_value);
	DIO_WritePin(LCD_D6,LCD_D6_value);
	DIO_WritePin(LCD_D7,LCD_D7_value);
	DIO_WritePin(LCD_E,STD_HIGH);              /* Enable */
	timer_mdelay(TIME_3MS);
	//vTaskDelay(TIME_1MS/portTICK_RATE_MS);               /* delay */
	DIO_WritePin(LCD_E,STD_LOW);	           /* disable */
}


/************************************************************************************
* Function Name:       LCD_displayChar
* Parameters (in):     uint8 data
* Parameters (inout):  LCD_RS ,LCD_RW,LCD_E,LCD_D4,LCD_D5,LCD_D6,LCD_D7 
* Parameters (out):    void
* Return value:        void
* Description:         Function that display a char on the LCD
************************************************************************************/
void LCD_displayChar(uint8 data)
{
	uint8 LCD_D4_value;
	uint8 LCD_D5_value;
	uint8 LCD_D6_value;
	uint8 LCD_D7_value;
	/* For 4_bit_Mode we have to divide the uint8 to 2 (4bits) and send the most 4bits then send the least 4bits
	   for example :data = 0x52 which is 0b 0101 0010
	   so we have to send 0b0101 (0x5) first then send 0b0010 (0x2)
	   first  send   LCD_D7_value =0 ,LCD_D6_value=1 LCD_D5_value=0  LCD_D4_value=1
	   second send   LCD_D7_value =0 ,LCD_D6_value=0 LCD_D5_value=1  LCD_D4_value=0
	   sequence : 1- Make E 0 RS 1 (data) RW 0 (write) 
	              2- Get #1 LCD_D4:D7_value using Get_Bit
	              3- Write Data Pins with Values
				  4- Enable
				  5- delay
				  6- disable
				  7- Get #2 LCD_D4:D7_value using Get_Bit
				  8- Write Data Pins with Values
				  9- Enable
				  10-delay
				  11-disable*/
	DIO_WritePin(LCD_E,STD_LOW);                 /* Make E 0 RS 1 (data) RW 0 (write) */
	DIO_WritePin(LCD_RS,STD_HIGH);
	DIO_WritePin(LCD_RW,STD_LOW);
	LCD_D4_value=Get_Bit(data,BIT4);         /* Get #1 LCD_D4:D7_value using Get_Bit */
	LCD_D5_value=Get_Bit(data,BIT5);
	LCD_D6_value=Get_Bit(data,BIT6);
	LCD_D7_value=Get_Bit(data,BIT7);
	DIO_WritePin(LCD_D4,LCD_D4_value);       /* Write Data Pins with Values */
	DIO_WritePin(LCD_D5,LCD_D5_value);
	DIO_WritePin(LCD_D6,LCD_D6_value);
	DIO_WritePin(LCD_D7,LCD_D7_value);

	DIO_WritePin(LCD_E,STD_HIGH);                /* Enable */
		timer_mdelay(TIME_3MS);

	//vTaskDelay(TIME_5MS/portTICK_RATE_MS);                 /* Delay */
	DIO_WritePin(LCD_E,STD_LOW);                 /* Disable */
	LCD_D4_value=Get_Bit(data,BIT0);         /* Get #2 LCD_D4:D7_value using Get_Bit */
	LCD_D5_value=Get_Bit(data,BIT1);
	LCD_D6_value=Get_Bit(data,BIT2);
	LCD_D7_value=Get_Bit(data,BIT3);
	DIO_WritePin(LCD_D4,LCD_D4_value);       /* Write Data Pins with Values */
	DIO_WritePin(LCD_D5,LCD_D5_value);
	DIO_WritePin(LCD_D6,LCD_D6_value);
	DIO_WritePin(LCD_D7,LCD_D7_value);
	DIO_WritePin(LCD_E,STD_HIGH);                /* Enable */
		timer_mdelay(TIME_3MS);

	//vTaskDelay(TIME_5MS/portTICK_RATE_MS);                 /* Delay */
	DIO_WritePin(LCD_E,STD_LOW);                 /* Disable */
	
}

/************************************************************************************
* Function Name:         LCD_displayString
* Parameters (in):       uint8 lcd_string[]   String
*                        uint8 string_size    string_size
* Parameters (inout):    void
* Parameters (out):      void
* Return value:          void
* Description:           Function that display a string
************************************************************************************/
void LCD_displayString(uint8 lcd_string[],uint8 string_size)
{
	uint8 string_index =0;                         
	while(--string_size)                            /*  decrement size for every print*/
	{
		LCD_displayChar(lcd_string[string_index]);  /* print char with the specif index */   
		string_index++;
	};
	
		
}

/************************************************************************************
* Function Name:        LCD_gotoRowColumn
* Parameters (in):      uint8 row ,uint8 column
* Parameters (inout):   void
* Parameters (out):     void
* Return value:         void
* Description:          function that go to specific row and column in the LCD
************************************************************************************/
void LCD_gotoRowColumn(uint8 row ,uint8 column){

	if (LCD_RAW0==row)                     /* Check the row number */
	{
	  LCD_sendCommand(LCD_FIRST_LINE);        
	  while(column--)
	  {
		LCD_sendCommand(LCD_INCREMENT);    /* Increment until reaching the specific column    */
	  }
	}
	else if (LCD_RAW1==row)
	{
		LCD_sendCommand(LCD_SECOND_LINE);
		while(column--)
		{
			LCD_sendCommand(LCD_INCREMENT);  /* Increment until reaching the specific column    */
		}
	}
	
	
}
/************************************************************************************
* Function Name:        LCD_displayStringRowColumn
* Parameters (in):      uint8 lcd_string[],uint8 string_size,uint8  row, uint8 col
* Parameters (inout):   void
* Parameters (out):     void
* Return value:         void
* Description:          Function that display a string in specific row and column
************************************************************************************/
void LCD_displayStringRowColumn(uint8 lcd_string[],uint8 string_size,uint8  row, uint8 col)
{
	LCD_gotoRowColumn(row,col);                    /* Go to  column */
	LCD_displayString(lcd_string,string_size);     
	
}
/************************************************************************************
* Function Name:        LCD_clear
* Parameters (in):      void
* Parameters (inout):   void
* Parameters (out):     void
* Return value:         void
* Description:          Function that clear the LCD
************************************************************************************/
void LCD_clear(void){
	
	LCD_sendCommand(LCD_CLEAR);                    /* Send command clear */
	
}
/************************************************************************************
* Function Name:       LCD_smile_init
* Parameters (in):     void
* Parameters (inout):  void
* Parameters (out):    void
* Return value:        void
* Description:         Function that create smile face
************************************************************************************/
void LCD_smile_init(void)
{
	LCD_sendCommand(LCD_CUSTOM_1);        /* Go to the first custom char place */
	LCD_displayChar(NUM_ZERO);
	LCD_displayChar(NUM_ZERO);
	LCD_displayChar(NUM_10);
	LCD_displayChar(NUM_ZERO);
	LCD_displayChar(NUM_17);
	LCD_displayChar(NUM_14);
	LCD_displayChar(NUM_ZERO);
	LCD_displayChar(NUM_ZERO);
	timer_mdelay(TIME_5MS);
	LCD_sendCommand(LCD_FIRST_LINE);      /* Return to the Default config */

}
/************************************************************************************
* Function Name:       LCD_smile_display
* Parameters (in):     void
* Parameters (inout):  void
* Parameters (out):    void
* Return value:        void
* Description:         Function that display smile face
************************************************************************************/
void LCD_smile_display(void)
{
		LCD_displayChar(0);
}



#endif