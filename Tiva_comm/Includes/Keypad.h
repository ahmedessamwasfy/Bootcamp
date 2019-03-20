#ifndef KEYPAD_H
#define KEYPAD_H

#include <stdint.h>
#include <stdbool.h>
#include "driverlib/gpio.h"
#include "Keypad_cfg.h"
void Keypad_init(void);
uint8 Keypad_getPressedKey(void);


#endif
