
#ifndef __BITWISEOPERATIONS_H__
#define __BITWISEOPERATIONS_H__

#include "Types.h"

#define SET_BIT(Register,Bit)		((Register)|=(1U<<(uint8)(Bit)))

#define CLEAR_BIT(Register,Bit)		((Register)&=~(1U<<(uint8)(Bit)))

#define GET_BIT(Register,Bit)		(((Register)>>(uint8)(Bit))&1U)

#define Toggle_Bit(Register,Bit)	((Register)^=(uint8)(1U<<(Bit)))

#endif