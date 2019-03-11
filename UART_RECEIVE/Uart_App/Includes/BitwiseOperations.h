/*
 * BitwiseOperations.h
 *
 * Created: 2/13/2019 11:15:18 AM
 *  Author: Ahmed Abdlrehem
 */ 


#ifndef BITWISEOPERATIONS_H_
#define BITWISEOPERATIONS_H_
#define Set_Bit(Register,Bit)      Register|=(1<<Bit)
#define Clear_Bit(Register,Bit)    Register&= ~(1<<Bit)
#define Get_Bit(Register,Bit)  (((uint8)Register&(1<<Bit))>>Bit)
#define Toggle_Bit(Register,Bit)   Register^=(1<<Bit)




#endif /* BITWISEOPERATIONS_H_ */