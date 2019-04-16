#if 0

/****************************** story 1 *****************************/
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
#include "LCD.h"
#include "Magic_Num.h"
#include "LED.h"
#include "BUZZER.h"
#include "eeprom.h"

int main()
{
    LCD_INIT(); /* initialize LCD to read data from EEPROM */
    Eeprom_Int_init(); /* initialize internal EEPROM */

    uint32_t pui32Data[2]; /* Buffer contain data to write in internal EEPROM */
    uint32_t pui32Read[2]; /* Buffer contain data to read from internal EEPROM */

    pui32Data[0] = 'A';
    pui32Data[1] = 'r';

    Eeprom_Int_Write(pui32Data, 0x400, sizeof(pui32Data)); /* write in EEPROM */
    Eeprom_Int_Read(pui32Read , 0x400 , sizeof(pui32Data)); /* read from EEPROM */

    LCD_Send_Data( pui32Read[0]); /*LCD Display */

}

/****************************  story 2 *********************************/
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
#include "LCD.h"
#include "Magic_Num.h"
#include "LED.h"
#include "BUZZER.h"
#include "eeprom.h"
#include "i2c.h"

int main()
{
    i2c_init(); /* I2C init 1 */
    //uint32_t value;
    init_master();
    //LED_INIT();
    //init_slave_i2c(0x12);

    while (1)
    {
        I2c_master_Write(5, 0x12);

        //value = I2c_Read_Slave();
        //if (value == 5)
        //{
        //TOG_LED1();
        //}

    }

}
#endif

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
#include "i2c.h"
#include "external_eeprom.h"

int main()
{
    Eeprom_Ext_init(); /* initialize  form I2C and make it as master */
    uint32_t pui32Data[2]; /* Buffer contain data to write in internal EEPROM */
    uint32_t pui32Read[2] = { 0 }; /* Buffer contain data to read from internal EEPROM */

    pui32Data[0] = 6;
    pui32Data[1] = 9;

    Eeprom_Ext_Write(0x00, pui32Data, sizeof(pui32Data));
    Eeprom_Ext_Read(0x00, pui32Read, sizeof(pui32Read));
    while (1)
    {

    }
}
