
#ifndef LCD_H_
#define LCD_H_

#include "../includes/BitwiseOperations.h"
#include "../includes/DIO.h"
#include "../includes/Types.h"
#include "../includes/LCD_CFG.h"
#include <util/delay.h>


void LCD_sendCommand(uint8 command);
void LCD_displayCharacter(uint8 data);
void LCD_displayString(const char *Str);
//void LCD_displayString(uint8 str[]);
void PrintDecimalNum(uint16 NUM);

void LCD_init(void);
void LCD_clearScreen(void);
void LCD_displayStringRowColumn(uint8 row,uint8 col,const char *Str);
void LCD_goToRowColumn(uint8 row,uint8 col);
void LCD_intgerToString(int data);




#endif /* LCD_H_ */