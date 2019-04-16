#include <stdint.h>
#include <stdbool.h>
#include "inc/hw_memmap.h"
#include "driverlib/debug.h"
#include "driverlib/gpio.h"
#include "driverlib/sysctl.h"
#include "driverlib/eeprom.h"
#include "driverlib/i2c.h"
#include "Types.h"
#include "driverlib/pin_map.h"
#include "Magic_Num.h"
#include "Internal_EEPROM/eeprom.h"
#include "../I2C/i2c.h"
#include "External_EEPROM/external_eeprom.h"
#include "eeprom_maneger.h"

/* Eep_init */
/* Parameters :  void  */
/* I/p : void  */
/* O/p : N/A */
/* Return : Void */
/* Function that initialize EEPROM internal & external   */
void Eep_init()
{
    i2c_init(); /* initialize I2C to communicate with EEPROM  */
    init_master(); /* initialize MC  as master to write or read from  external EEPROM  */

    uint32_t ui32EEPROMInit;

    /* Enable the EEPROM module.*/
    SysCtlPeripheralEnable(SYSCTL_PERIPH_EEPROM0);

    /* Wait for the EEPROM module to be ready*/
    while (!SysCtlPeripheralReady(SYSCTL_PERIPH_EEPROM0))
    {
    }

    /* Wait for the EEPROM Initialization to complete*/
    ui32EEPROMInit = EEPROMInit();

    /*Check if the EEPROM Initialization returned an error*/
    /* and inform the application*/
    if (ui32EEPROMInit != EEPROM_INIT_OK)
    {
        while (1)
        {
        }
    }
}

/* Eep_Write */
/* Parameters :  uint16 , uint8 , uint16  */
/* I/p : void  */
/* O/p : N/A */
/* Return : Void */
/* Function that write in  EEPROM internal & external   */
uint8_t Eep_Write(uint32_t address, uint32_t * data, uint32_t length)
{

    if (address >= 34816) /*  if address > 34816 which is the last address in internal and external */
    {
        return error; /* return error which is invalid address */
    }

    if (address < 2047) /*  if address < 2047 and address <32767 which is internal EEPROM */
    {
        length = length * 4;
        Eeprom_Int_Write(data, address, length);/* internal EEPROM write */
        return valid; /* return valid */
    }

    if ((address >= 2047) && (address < 34816)) /*  if address > 2047 and address <34816 which is external EEPROM*/
    {
        address = address - 2048; /* subtract from 2048 to start from zero in external EEPROM */
        Eeprom_Ext_Write(address, data, length); /* external EEPROM write */
        return valid; /* return valid */
    }
return 0 ;
}

/* Eep_Read */
/* Parameters :  uint16 , uint8 , uint16  */
/* I/p : void  */
/* O/p : N/A */
/* Return : Void */
/* Function that read from  EEPROM internal & external   */
uint8_t Eep_Read(uint32_t address, uint32_t * data, uint32_t length)
{
    if (address >= 34816) /*  if address > 34816 which is the last address in internal and external */
       {
           return error; /* return error which is invalid address */
       }

       if (address < 2047) /*  if address < 2047 and address <32767 which is internal EEPROM */
       {
           length = length * 4;
           Eeprom_Int_Read(data, address, length);/* internal EEPROM write */
           return valid; /* return valid */
       }

       if ((address >= 2047) && (address < 34816)) /*  if address > 2047 and address <34816 which is external EEPROM*/
       {
           address = address - 2048; /* subtract from 2048 to start from zero in external EEPROM */
           Eeprom_Ext_Read(address, data, length); /* external EEPROM read */
           return valid; /* return valid */
       }

return 0;
}

