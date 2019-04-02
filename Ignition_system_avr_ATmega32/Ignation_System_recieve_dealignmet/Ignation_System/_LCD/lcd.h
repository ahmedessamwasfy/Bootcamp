
#ifndef LCD_H
#define LCD_H




#define LCD_RAW0     0
#define LCD_RAW1     1

#define LCD_COLUMN0     0
#define LCD_COLUMN1     1
#define LCD_COLUMN2     2
#define LCD_COLUMN3     3
#define LCD_COLUMN4     4
#define LCD_COLUMN5     5
#define LCD_COLUMN6     6
#define LCD_COLUMN7     7
#define LCD_COLUMN8     8
#define LCD_COLUMN9     9
#define LCD_COLUMN10    10
#define LCD_COLUMN11    11
#define LCD_COLUMN12    12
#define LCD_COLUMN13    13
#define LCD_COLUMN14    14
#define LCD_COLUMN15    15







void LCD_init(void);
void LCD_sendCommand(uint8 command);
void LCD_displayChar(uint8 data);
void LCD_displayString(uint8 lcd_string[],uint8 string_size);
void LCD_displayStringRowColumn(uint8 lcd_string[],uint8 string_size,uint8  row, uint8 col);
void LCD_clear(void);
void LCD_gotoRowColumn(uint8 row ,uint8 column);
void LCD_smile_init(void);
void LCD_sad_init(void);
void LCD_sad_display(void);
void LCD_smile_display(void);
void LCD_like_init(void);
void LCD_like_display(void);
void LCD_balona_init(void);
void LCD_balona_display(void);


#endif