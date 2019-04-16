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
#include "LCD/LCD.h"
#include "Magic_Num.h"
#include "Internal_EEPROM/eeprom.h"

int main()
{
    LCD_INIT(); /* initialize LCD to read data from EEPROM */
    Eeprom_Int_init(); /* initialize internal EEPROM */

    uint32_t pui32Data[2] = { 2, 3 }; /* Buffer contain data to write in internal EEPROM */
    uint32_t pui32Read[2] = { 0 }; /* Buffer contain data to read from internal EEPROM */

    Eeprom_Int_Write(pui32Data, 0x400, sizeof(pui32Data)); /* write in EEPROM */
    Eeprom_Int_Read(pui32Read, 0x400, sizeof(pui32Data)); /* read from EEPROM */
    while(1)
    {

    }

}
