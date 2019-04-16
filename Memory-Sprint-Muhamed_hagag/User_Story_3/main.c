#include <stdint.h>
#include <stdbool.h>
#include "inc/hw_memmap.h"
#include "driverlib/debug.h"
#include "driverlib/gpio.h"
#include "driverlib/sysctl.h"
#include "driverlib/uart.h"
#include "driverlib/eeprom.h"
#include "Types.h"
#include "driverlib/pin_map.h"
#include "Magic_Num.h"
#include "I2C/i2c.h"
#include "External_EEPROM/external_eeprom.h"
#include "Maneger_EEPROM/eeprom_maneger.h"

int main()
{
    Eep_init();
    uint32_t pui32Data[2] = { 1, 3 }; /* Buffer contain data to write in internal EEPROM */
    uint32_t pui32Read[2] = { 0 }; /* Buffer contain data to read from internal EEPROM */

    Eep_Write(2050, pui32Data, sizeof(pui32Data));
    Eep_Read(2050, pui32Read, sizeof(pui32Read));
    while (1)
    {
    }
}
