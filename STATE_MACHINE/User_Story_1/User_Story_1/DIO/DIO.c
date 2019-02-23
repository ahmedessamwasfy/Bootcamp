/*
 * DIO.c
 *
 * Created: 2/13/2019 2:03:28 PM
 *  Author: Mohamed Mostafa Abdel Karim
 */ 

#include "../includes/Types.h"
#include "../includes/BitwiseOperations.h"
#include "../includes/DIO.h"

void DIO_WritePin(uint8 PinNum,uint8 PinValue){
	
	if( (PinNum >= 0U) && (PinNum <= 7U) ){
		if(PinValue == 0U){
			Clear_Bit(PORTA,PinNum);
		}
		else{
			Set_Bit(PORTA,PinNum);
		}
	}
	else if( (PinNum >= 8U) && (PinNum <= 15U) ){
		if(PinValue == 0U){
			Clear_Bit(PORTB,PinNum-8U);
		}
		else{
			Set_Bit(PORTB,PinNum-8U);
		}
	}
	else if( (PinNum >= 16U) && (PinNum <= 23U) ){
		if(PinValue == 0U){
			Clear_Bit(PORTC,PinNum-16);
		}
		else{
			Set_Bit(PORTC,PinNum-16);
		}
	}
	else if( (PinNum >= 24U) && (PinNum <= 31U) ){
		if(PinValue == 0U){
			Clear_Bit(PORTD,PinNum-24);
		}
		else{
			Set_Bit(PORTD,PinNum-24);
		}
	}
	else{
		
	}
	
}
uint8 DIO_ReadPin(uint8 PinNum){
	
	if( (PinNum >= 0U) && (PinNum <= 7U) ){
		return Get_Bit(PINA,PinNum);
	}
	else if( (PinNum >= 8U) && (PinNum <= 15U) ){
		return Get_Bit(PINB,PinNum-8);
	}
	else if( (PinNum >= 16U) && (PinNum <= 23U) ){
		return Get_Bit(PINC,PinNum-16);
	}
	else if( (PinNum >= 24U) && (PinNum <= 31U) ){
		return Get_Bit(PIND,PinNum-24);
	}
	else{
		
	}
	
}
void DIO_SetPinDirection(uint8 PinNum,uint8 PinDirection){
	
	if( (PinNum >= 0U) && (PinNum <= 7U) ){
		if(PinDirection == 0U){
			Clear_Bit(DDRA,PinNum);
		}
		else{
			Set_Bit(DDRA,PinNum);
		}
	}
	else if( (PinNum >= 8U) && (PinNum <= 15U) ){
		if(PinDirection == 0U){
			Clear_Bit(DDRB,PinNum-8U);
		}
		else{
			Set_Bit(DDRB,PinNum-8U);
		}
	}
	else if( (PinNum >= 16U) && (PinNum <= 23U) ){
		if(PinDirection == 0U){
			Clear_Bit(DDRC,PinNum-16);
		}
		else{
			Set_Bit(DDRC,PinNum-16);
		}
	}
	else if( (PinNum >= 24U) && (PinNum <= 31U) ){
		if(PinDirection == 0U){
			Clear_Bit(DDRD,PinNum-24);
		}
		else{
			Set_Bit(DDRD,PinNum-24);
		}
	}
	else{
		
	}
	
	
}
