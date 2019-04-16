#ifndef EXTERNAL_EEPROM_H_
#define EXTERNAL_EEPROM_H_

#include "Types.h"
#include <stdint.h>
#include <stdbool.h>
#include "i2c.h"

void Eeprom_Ext_init();
void Eeprom_Ext_Write(uint16_t Address, uint32_t* data, uint16_t length);
void Eeprom_Ext_Read(uint16_t Address, uint32_t * data, uint16_t length);



#endif /* EXTERNAL_EEPROM_H_ */
