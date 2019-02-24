

#include "../includes/KeyPad.h"


void KeyPad_Init(void)
{
	DIO_SetPinDirection(COL1,OUTPUT);
	DIO_SetPinDirection(COL2,OUTPUT);
	DIO_SetPinDirection(COL3,OUTPUT);
	DIO_SetPinDirection(ROW1,INPUT);
	DIO_SetPinDirection(ROW2,INPUT);
	DIO_SetPinDirection(ROW3,INPUT);
	DIO_WritePin(COL1,HIGH);
	DIO_WritePin(COL2,HIGH);
	DIO_WritePin(COL3,HIGH);
	DIO_WritePin(ROW1,HIGH);
	DIO_WritePin(ROW2,HIGH);
	DIO_WritePin(ROW3,HIGH);
}




uint8 KeyPad_GetPressedKey(void)
{
	while(1){
		for (uint8 i=0; i<COL_NUM; i++)
		{
			KeyPad_Init();
			DIO_WritePin(COL1+i,LOW);
			for (uint8 j=0; j<ROW_NUM; j++)
			{
				if (!(DIO_ReadPin(ROW1+j)))
				{
					uint8 result = ((j*COL_NUM)+i+1);
					return result;
				}
			}
		}
	}
}


