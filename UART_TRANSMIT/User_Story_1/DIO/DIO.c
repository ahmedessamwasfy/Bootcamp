
#include "../includes/Types.h"
#include "../includes/BitwiseOperations.h"
#include "../includes/DIO.h"
/*DIO_WritePin */
/* Parameters : uint8 , uint8 */
/* I/p : uint8 , uint8  */
/* O/p : N/A */
/* Return : Void */
/* Function that initialize pin at any port from 0 to 39 pins in 4 ports  */
void DIO_WritePin(uint8 PinNum,uint8 PinValue){
	
	if( (PinNum >= ZERO) && (PinNum <= SEVEN) ){
		if(PinValue == ZERO){
			Clear_Bit(PORTA,PinNum);
		}
		else{
			Set_Bit(PORTA,PinNum);
		}
	}
	else if( (PinNum >= EIGHT) && (PinNum <= FIFTEEN) ){
		if(PinValue == ZERO){
			Clear_Bit(PORTB,PinNum-EIGHT);
		}
		else{
			Set_Bit(PORTB,PinNum-EIGHT);
		}
	}
	else if( (PinNum >= SIXTEEN) && (PinNum <= TWENTY_THREE) ){
		if(PinValue == ZERO){
			Clear_Bit(PORTC,PinNum-SIXTEEN);
		}
		else{
			Set_Bit(PORTC,PinNum-SIXTEEN);
		}
	}
	else if( (PinNum >= TWENTY_FOUR) && (PinNum <= THIRTY_ONE) ){
		if(PinValue == ZERO){
			Clear_Bit(PORTD,PinNum-TWENTY_FOUR);
		}
		else{
			Set_Bit(PORTD,PinNum-TWENTY_FOUR);
		}
	}
	else{
		
	}
	
}
/*DIO_ReadPin */
/* Parameters : uint8 */
/* I/p : uint8 */
/* O/p : N/A */
/* Return : uint8 */
/* Function that read pin at any port from 0 to 39 pins in 4 ports  */
uint8 DIO_ReadPin(uint8 PinNum){
	
	if( (PinNum >= ZERO) && (PinNum <= SEVEN) ){
		return Get_Bit(PINA,PinNum);
	}
	else if( (PinNum >= EIGHT) && (PinNum <= FIFTEEN) ){
		return Get_Bit(PINB,(PinNum-EIGHT));
	}
	else if( (PinNum >= SIXTEEN) && (PinNum <= TWENTY_THREE) ){
		return Get_Bit(PINC,(PinNum-16));
	}
	else if( (PinNum >= TWENTY_FOUR) && (PinNum <= THIRTY_ONE) ){
		return Get_Bit(PIND,(PinNum-TWENTY_FOUR));
	}
	else{
		
	}
	
}
/*DIO_SetPinDirection */
/* Parameters : uint8 , uint8 */
/* I/p : uint8 , uint8 */
/* O/p : N/A */
/* Return : void */
/* Function that initialize direction for pin at any port from 0 to 39 pins in 4 ports input or output   */
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
