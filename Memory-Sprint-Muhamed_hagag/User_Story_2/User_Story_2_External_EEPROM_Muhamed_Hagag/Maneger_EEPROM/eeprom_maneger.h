#ifndef EEPROM_MANEGER_H_
#define EEPROM_MANEGER_H_

#include "Types.h"
#include <stdint.h>
#include <stdbool.h>

extern void Eep_init();
extern uint8_t Eep_Write(uint32_t address, uint32_t * data, uint32_t length);
extern uint8_t Eep_Read(uint32_t address, uint32_t * data, uint32_t length);
#define error 0
#define valid 1

#endif /* EEPROM_MANEGER_H_ */
