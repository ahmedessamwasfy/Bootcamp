#include "../LCD/lcd.h"
#include "../LCD/lcd_config.h"

void LCD_init(void)
{
	LCD_CTRL_PORT_DIR |= (NUMBER_ONE<<E) | (NUMBER_ONE<<RS) | (NUMBER_ONE<<RW); //CTRL PINS OUTPUT DIRESTION
	
	#if (DATA_BITS_MODE == NUMBER_FOUR)
	#ifdef UPPER_PORT_PINS//4,5,6,7 BITS 
	LCD_DATA_PORT_DIR |= MASK_UPPER_BIT; // DATA BITS OUTPUT
	#else
	LCD_DATA_PORT_DIR |= MASK_LOWER_BIT; 
	#endif
	LCD_sendCommand(FOUR_BIT_MODE_COMMAND); 
	LCD_sendCommand(FOUR_BIT_COMMAND); 
	LCD_sendCommand(TWO_LINE_LCD_Four_BIT_MODE);

	#elif (DATA_BITS_MODE == NUMBER_EGIGH)
	LCD_DATA_PORT_DIR = MASK_PORT_HIGH;
	LCD_sendCommand(TWO_LINE_LCD_Eight_BIT_MODE); 
	#endif
	
	LCD_sendCommand(CURSOR_ON); 
	LCD_sendCommand(CLEAR_COMMAND);
	LCD_sendCommand(INCREMENT_CURSOR); 
}


void LCD_sendCommand(uint8 command)
{
	CLEAR_BIT(LCD_CTRL_PORT,RS); //RS =0 FOR SEND COMMAND 
	CLEAR_BIT(LCD_CTRL_PORT,RW); // RW =0 FOR WRITE
	_delay_ms(NUMBER_ONE); 
	
	#if (DATA_BITS_MODE == NUMBER_FOUR)

	#ifdef UPPER_PORT_PINS
	LCD_DATA_PORT = (LCD_DATA_PORT & MASK_LOWER_BIT) | (command & MASK_UPPER_BIT);
	#else
	LCD_DATA_PORT = (LCD_DATA_PORT & MASK_UPPER_BIT) | ((command & MASK_UPPER_BIT) >> NUMBER_FOUR);
	#endif
	SET_BIT(LCD_CTRL_PORT,E); // ENABLE=1
	_delay_ms(NUMBER_ONE);

	CLEAR_BIT(LCD_CTRL_PORT,E);//ENBLE=0
	_delay_ms(NUMBER_ONE); 
	

	
	#ifdef UPPER_PORT_PINS
	LCD_DATA_PORT = (LCD_DATA_PORT & MASK_LOWER_BIT) | (command<< NUMBER_FOUR);
	#else
	LCD_DATA_PORT = (LCD_DATA_PORT & MASK_UPPER_BIT) | (command & MASK_LOWER_BIT);
	#endif
	SET_BIT(LCD_CTRL_PORT,E);
	_delay_ms(NUMBER_ONE); 
	CLEAR_BIT(LCD_CTRL_PORT,E); 
	_delay_ms(NUMBER_ONE);
	
	#elif (DATA_BITS_MODE == NUMBER_EGIGH)
	LCD_DATA_PORT = command;
	_delay_ms(NUMBER_ONE);
	CLEAR_BIT(LCD_CTRL_PORT,E); 
	_delay_ms(NUMBER_ONE); 
	#endif
}
void LCD_displayCharacter(uint8 data)
{
	SET_BIT(LCD_CTRL_PORT,RS); 
	CLEAR_BIT(LCD_CTRL_PORT,RW); 
	_delay_ms(NUMBER_ONE); 
	
	#if (DATA_BITS_MODE == NUMBER_FOUR)
	
	#ifdef UPPER_PORT_PINS
	LCD_DATA_PORT = (LCD_DATA_PORT & MASK_LOWER_BIT) | (data & MASK_UPPER_BIT);
	#else
	LCD_DATA_PORT = (LCD_DATA_PORT & MASK_UPPER_BIT) | ((data & MASK_UPPER_BIT) >> NUMBER_FOUR);
	#endif
	SET_BIT(LCD_CTRL_PORT,E);
	_delay_ms(NUMBER_TWO);
	CLEAR_BIT(LCD_CTRL_PORT,E); 
	_delay_ms(NUMBER_TWO);
	

	#ifdef UPPER_PORT_PINS
	LCD_DATA_PORT = (LCD_DATA_PORT & MASK_LOWER_BIT) | (data<< NUMBER_FOUR);
	#else
	LCD_DATA_PORT = (LCD_DATA_PORT & MASK_UPPER_BIT) | (data & MASK_LOWER_BIT);
	#endif
	SET_BIT(LCD_CTRL_PORT,E);
	_delay_ms(NUMBER_TWO); 
	CLEAR_BIT(LCD_CTRL_PORT,E); 
	_delay_ms(NUMBER_TWO); 
	#elif (DATA_BITS_MODE == NUMBER_EGIGH)
	LCD_DATA_PORT = data;
	_delay_ms(NUMBER_ONE);
	CLEAR_BIT(LCD_CTRL_PORT,E);
	_delay_ms(NUMBER_ONE); 
	#endif
}

void LCD_displayString(const char *Str)
{
	uint8 i = NUMBER_ZERO;
	while(Str[i] != '\0')
	{
		LCD_displayCharacter(Str[i]);
		i++;
	}
	
}
void LCD_clearScreen(void)
{
	LCD_sendCommand(CLEAR_COMMAND); //clear display
}
void LCD_goToRowColumn(uint8 row,uint8 col)
{
	uint8 Address;
	
	/* first of all calculate the required address */
	switch(row)
	{
		case 0:
				Address=col;
				break;
		case 1:
				Address=col+0x40;
				break;
		
	}					
	/* to write to a specific address in the LCD 
	 * we need to apply the corresponding command 0b10000000+Address */
	LCD_sendCommand(Address | SET_CURSOR_LOCATION); 
}



void LCD_displayStringRowColumn(uint8 row,uint8 col,const char *Str)
{
	LCD_goToRowColumn(row,col);
	LCD_displayString(Str);
}






