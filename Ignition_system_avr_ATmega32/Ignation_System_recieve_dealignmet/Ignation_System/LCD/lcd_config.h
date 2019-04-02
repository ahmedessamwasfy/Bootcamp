
#ifndef LCD_CFG_H_
#define LCD_CFG_H_

#define DATA_BITS_MODE 4  /*4BIT MACRO */


/* Use higher 4 bits in the data port */
#if (DATA_BITS_MODE == 4)/* MACRO CHECK THE MODE */
#define UPPER_PORT_PINS
#endif

/* CONTROL PINS LCD */
#define RS 1   /*RS PIN 0>>COMMAND 1>>DATA*/
#define RW 2   /*RW PIN 0>>WRITE 1>>READ */
#define E  3   /* ENABEL PIN 1>>ENABLE 0 >> DISBALE*/
/* DATA PINS LCD */
#define D4 4
#define D5 5
#define D6 6
#define D7 7

#define LCD_CTRL_PORT        PORTA
#define LCD_CTRL_PORT_DIR    DDRA
#define LCD_DATA_PORT        PORTA
#define LCD_DATA_PORT_DIR    DDRA


/* LCD Commands */
#define CLEAR_COMMAND                0x01 /*COMMAND FOR CLEAR LCD */
#define FOUR_BITS_DATA_MODE          0x02 /*COMMAND FOR SELECT 4 BIT MODE */
#define TWO_LINE_LCD_Four_BIT_MODE   0x28 /*COMMAND FOR SELECT TWO LINE 4 BIT MODE */
#define TWO_LINE_LCD_Eight_BIT_MODE  0x38 /*COMMAND FOR SELECT TWO LINE 8 BIT MODE */
#define CURSOR_OFF                   0x0C /*CURSOR OFF */
#define CURSOR_ON                    0x0E /*CURSOR ON8*/
#define SET_CURSOR_LOCATION          0x80 /*SET CURSOR AT BEGIN */
#define FORCE_CURSOR_FIRST_LINE      0x80 /*SET CURSOR AT FIRST LINE */
#define FORCE_CURSOR_SECOND_LINE     0xC0 /*SET CURSOR AT SECOND LINE*/
#define FOUR_BIT_COMMAND             0x32 /*FOUR BIT COMMED */
#define FOUR_BIT_MODE_COMMAND        0x33
#define INCREMENT_CURSOR             0x06

#define MASK_UPPER_BIT                0xF0 /*MASK FOR MSB 11110000*/
#define MASK_LOWER_BIT                0x0F /*MASK FOR LBS 00001111*/
#define MASK_PORT_HIGH                0xFF /*MASK FOR 11111111*/
#define MASK_PORT_LOW                 0x00 /*MASK FOR 00000000*/

#define FIRST_ROW_ADDRESS            0x00 /*FIRST ADDRESS IN ROW 0 */
#define SECOND_ROW_ADDRESS           0x40 /*FIRST ADDRESS IN ROW 1 */


#define NUMBER_ONE                    1
#define NUMBER_TWO                    2
#define NUMBER_ZERO                   0
#define NUMBER_THREE                  3
#define NUMBER_FOUR                   4
#define NUMBER_EGIGH                  8
#define NUMBER_TEN                    10


void LCD_sendCommand(uint8 command);
void LCD_displayCharacter(uint8 data);
void LCD_displayString(const char *Str);
void LCD_init(void);
void LCD_clearScreen(void);
void LCD_displayStringRowColumn(uint8 row,uint8 col,const char *Str);

void LCD_goToRowColumn(uint8 row,uint8 col);

#endif /* LCD_CFG_H_ */