
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
			CLEAR_BIT(PORTA,PinNum);
		}
		else{
			SET_BIT(PORTA,PinNum);
		}
	}
	else if( (PinNum >= EIGHT) && (PinNum <= FIFTEEN) ){
		if(PinValue == ZERO){
			CLEAR_BIT(PORTB,PinNum-EIGHT);
		}
		else{
			SET_BIT(PORTB,PinNum-EIGHT);
		}
	}
	else if( (PinNum >= SIXTEEN) && (PinNum <= TWENTY_THREE) ){
		if(PinValue == ZERO){
			CLEAR_BIT(PORTC,PinNum-SIXTEEN);
		}
		else{
			SET_BIT(PORTC,PinNum-SIXTEEN);
		}
	}
	else if( (PinNum >= TWENTY_FOUR) && (PinNum <= THIRTY_ONE) ){
		if(PinValue == ZERO){
			CLEAR_BIT(PORTD,PinNum-TWENTY_FOUR);
		}
		else{
			SET_BIT(PORTD,PinNum-TWENTY_FOUR);
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
		return GET_BIT(PINA,PinNum);
	}
	else if( (PinNum >= EIGHT) && (PinNum <= FIFTEEN) ){
		return GET_BIT(PINB,(PinNum-EIGHT));
	}
	else if( (PinNum >= SIXTEEN) && (PinNum <= TWENTY_THREE) ){
		return GET_BIT(PINC,(PinNum-16));
	}
	else if( (PinNum >= TWENTY_FOUR) && (PinNum <= THIRTY_ONE) ){
		return GET_BIT(PIND,(PinNum-TWENTY_FOUR));
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
			CLEAR_BIT(DDRA,PinNum);
		}
		else{
			SET_BIT(DDRA,PinNum);
		}
	}
	else if( (PinNum >= 8U) && (PinNum <= 15U) ){
		if(PinDirection == 0U){
			CLEAR_BIT(DDRB,PinNum-8U);
		}
		else{
			SET_BIT(DDRB,PinNum-8U);
		}
	}
	else if( (PinNum >= 16U) && (PinNum <= 23U) ){
		if(PinDirection == 0U){
			CLEAR_BIT(DDRC,PinNum-16);
		}
		else{
			SET_BIT(DDRC,PinNum-16);
		}
	}
	else if( (PinNum >= 24U) && (PinNum <= 31U) ){
		if(PinDirection == 0U){
			CLEAR_BIT(DDRD,PinNum-24);
		}
		else{
			SET_BIT(DDRD,PinNum-24);
		}
	}
	else{
		
	}
	
	
}
