

#ifndef KEYPAD_H_
#define KEYPAD_H_
#include "KeyPad_cfg.h"
#include "DIO.h"
#include "BitwiseOperations.h"
#include "Types.h"


void KeyPad_Init(void);
uint8 KeyPad_GetPressedKey(void);


#endif /* KEYPAD_H_ */