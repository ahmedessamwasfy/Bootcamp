/*
 * Wifi_Control.c
 *
 * Created: 3/30/2019 9:29:05 AM
 * Author : Ahmed.Magdy
 */ 

#include <stddef.h>
#include "DIO.h"
#include "uart_driver.h"
#include "ESP_Driver.h"
#include <avr/interrupt.h>

#define SYSTEM_FREQ	16000000UL
#define F_CPU 16000000UL

int main(void)
{
	int* DataReceived=NO_Response;
	DIO_SetPinDirection(11,OUTPUT);/* BUZZER OUTPUT */
	Disable_Interrupts();
	UART_Init(9600,ESP_FillResponseBuffer);
	Enable_Interrupts();
	WIFI_Service_Start(Server, "1111", "asdd", "1234567890", NULL, NULL, NULL, NULL);/* PORT NUM =1111 , WIFI_NAME=asdd , pwd=1234567890 */
	while(OK_Status!=ESP_SendData("Wifi Demo Started","17"));
	//DataReceived=NO_Response;
	
	while(1){/*loop untiles receiving data */
	DataReceived=ESP_ReceiveData();/* if received data by esp module */
	_delay_ms(1000);
	if(*DataReceived == 'a')/* if data which sent from hercules == a */
	{
		DIO_WritePin(11,HIGH);/* buzzer on */
	}
	else if(*DataReceived == 'b')/* if data which sent from hercules == b */
	{
	   DIO_WritePin(11,LOW);/* buzzer off */
	}
	}
	
		
}
