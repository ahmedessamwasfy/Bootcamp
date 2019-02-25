/*
 * Bitwise_Operations.h
 *
 * Created: 2/13/2019 10:54:34 AM
 *  Author: Mohamed Hagag
 */ 
#ifndef __BITWISEOPERATIONS_H__
#define __BITWISEOPERATIONS_H__

#include "Types.h"

#define Set_Bit(Register,Bit)		((Register)|=(1U<<(uint8)(Bit)))

#define Clear_Bit(Register,Bit)		((Register)&=~(1U<<(uint8)(Bit)))

#define Get_Bit(Register,Bit)		(Register & (1<<Bit))

#define Toggle_Bit(Register,Bit)	((Register)^=(uint8)(1U<<(Bit)))

/* Check if a specific bit is set in any register and return true if yes */
#define BIT_IS_SET(REG,BIT) ( REG & (1<<BIT) )

/* Check if a specific bit is cleared in any register and return true if yes */
#define BIT_IS_CLEAR(REG,BIT) ( !(REG & (1<<BIT)) )

#endif