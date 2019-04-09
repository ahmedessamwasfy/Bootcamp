#include "includes/Types.h"
#include "includes/BitwiseOperations.h"
#include "includes/DIO.h"
#include "includes/LCD.h"
#include "includes/ADC.h"
#include "includes/TempSensor.h"
#include <avr/delay.h>

int main(void)
{
	DIO_SetPinDirection(BUZZER,OUTPUT);/*set buzzer as output */
	uint16 temp;
	uint16 t ; /* variable will display on LCD */
	LCD_init();/* LCD INIT */
    ADC_Initialize();/* ADC initialize */
	ADC_Enable(); /*enable ADC */
   _delay_ms(20);
   LCD_displayStringRowColumn(ROW_ZERO,COL_ZERO,"temp=");
	while(1)
	{
		temp = ADC_StartConversion(0); /* Start convert and return value in temp */
		t = (double)((temp*VREF)/(254)); /*  equation to calculate temp LM35 */
		t = ((temp*TEN)/TEN);
		LCD_displayStringRowColumn(ROW_ZERO,COL_SIX," ");
		PrintDecimalNum(t); /* FUN to print temp on LCD */
         if(t >FOURTY_CEL_DEGREE)/*check if temp > 40 */
		 {
			 DIO_WritePin(BUZZER,HIGH);/* if temp > 40 turn on buzzer */
		 }
		 else/*check if temp < 40 */
		 {
			 DIO_WritePin(BUZZER,LOW);/* if temp < 40 turn off buzzer */
		 }
		_delay_ms(5000);
	}
	
}






