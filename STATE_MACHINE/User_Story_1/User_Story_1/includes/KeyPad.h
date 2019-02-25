

#ifndef KEYPAD_H_
#define KEYPAD_H_
#include "KeyPad_cfg.h"
#include "DIO.h"
#include "BitwiseOperations.h"
#include "Types.h"

#define HIGH     1
#define LOW      0
#define OUTPUT   1
#define INPUT    0



void KeyPad_Init(void);
uint8 KeyPad_GetPressedKey(void);


#endif /* KEYPAD_H_ */