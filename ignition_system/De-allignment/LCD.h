

/*
 * LCD.h
 *
 * Created: 2/19/2019 11:14:29 AM
 *  Author: AVE-LAP-005
 */


#ifndef LCD_H_
#define LCD_H_
typedef char uint8;
/* define Commands */
#define LCD_INIT_PHASE_ONE 0x33
#define LCD_INIT_PHASE_TWO 0x32
#define LCD_INIT_PHASE_THREE 0x28
#define LCD_DISPLAY_OPTIONS 0x0E
#define LCD_CLEAR 0x01
#define LCD_INCREMENT_CURSOR 0x06
/* LCD APIS */
void LCD_init();
void LCD_sendCommand(uint8 command);
void LCD_displayChar(uint8 Char);
void LCD_displayString(uint8* data);
void LCD_displayStringRowColumn(uint8 row,uint8 col,uint8* data);
void LCD_clear();
void LCD_gotoRowColumn(uint8 row,uint8 col);
void LCD_displayData(uint8_t);


#endif /* LCD_H_ */

