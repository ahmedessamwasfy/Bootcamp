#ifndef EEPROM_H_
#define EEPROM_H_

#include "Types.h"
#include <stdint.h>
#include <stdbool.h>

extern void Eeprom_Int_init();
extern uint32_t Eeprom_Int_Write(uint32_t * data , uint32_t address , uint32_t length);
extern void Eeprom_Int_Read(uint32_t * data , uint32_t address , uint32_t length);



#endif /* EEPROM_H_ */
