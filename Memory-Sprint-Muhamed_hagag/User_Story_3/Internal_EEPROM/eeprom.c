#include <stdint.h>
#include <stdbool.h>
#include "inc/hw_memmap.h"
#include "driverlib/debug.h"
#include "driverlib/gpio.h"
#include "driverlib/sysctl.h"
#include "driverlib/eeprom.h"
#include "Types.h"
#include "driverlib/pin_map.h"
#include "Magic_Num.h"
#include "eeprom.h"

/******************************* EEPROM INTERNAL ************************************************/


/*Eeprom_Int_init */
/* Parameters :  void  */
/* I/p : void  */
/* O/p : N/A */
/* Return : Void */
/* Function that initialize EEPROM internal   */
void Eeprom_Int_init()
{
    uint32_t ui32EEPROMInit;

    // Enable the EEPROM module.
    SysCtlPeripheralEnable(SYSCTL_PERIPH_EEPROM0);

    // Wait for the EEPROM module to be ready
    while (!SysCtlPeripheralReady(SYSCTL_PERIPH_EEPROM0))
    {
    }

    // Wait for the EEPROM Initialization to complete
    ui32EEPROMInit = EEPROMInit();

    // Check if the EEPROM Initialization returned an error
    // and inform the application
    if (ui32EEPROMInit != EEPROM_INIT_OK)
    {
        while (1)
        {
        }
    }
}

/* Eeprom_Int_Write */
/* Parameters :  uint32_t , uint32_t , uint32_t   */
/* I/p : void  */
/* O/p : N/A */
/* Return : uint32_t */
/* Function that write data in EEPROM internal   */
uint32_t Eeprom_Int_Write(uint32_t * data, uint32_t address, uint32_t length)
{
    return EEPROMProgram(data, address, length);
}


/* Eeprom_Int_Read */
/* Parameters :  uint32_t , uint32_t , uint32_t   */
/* I/p : void  */
/* O/p : N/A */
/* Return : void  */
/* Function that read data from EEPROM internal   */
void Eeprom_Int_Read(uint32_t * data, uint32_t address, uint32_t length)
{
    EEPROMRead(data, address, length);
}
