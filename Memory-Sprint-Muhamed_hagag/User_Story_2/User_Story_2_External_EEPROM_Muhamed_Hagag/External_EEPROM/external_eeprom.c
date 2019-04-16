#include <stdint.h>
#include <stdbool.h>
#include "Types.h"
#include "driverlib/i2c.h"
#include "driverlib/sysctl.h"
#include "driverlib/gpio.h"
#include "driverlib/pin_map.h"
#include "driverlib/rom.h"
#include "inc/hw_memmap.h"
#include "external_eeprom.h"
#include "Types.h"
#include "driverlib/pin_map.h"
#include "Magic_Num.h"
#include "../I2C/i2c.h"
#include "Internal_EEPROM/eeprom.h"

/******************************* EEPROM EXTERNAL ************************************************/


/******************************************/
#define MASK_HIGH_BITS 0xFF00

#define MASK_LOW_BITS 0x00FF

#define SLAVE_ADD 0x50
/******************************************/

/* Eeprom_Ext_init */
/* Parameters :  void  */
/* I/p : void  */
/* O/p : N/A */
/* Return : Void */
/* Function that initialize EEPROM external   */
void Eeprom_Ext_init()
{
    i2c_init(); /* initialize I2C to communicate with EEPROM  */
    init_master(); /* initialize MC  as master to write or read from  external EEPROM  */
}

/* Eeprom_Ext_Write */
/* Parameters :  uint16 , uint32 ,uint16  */
/* I/p : void  */
/* O/p : N/A */
/* Return : Void */
/* Function that write in EEPROM external   */
void Eeprom_Ext_Write(uint16_t Address, uint32_t* data, uint16_t length)
{
    uint8 High_Bits_Address = 0;
    uint8 Low_Bits_Address = 0;
    uint32 index = 0;

    High_Bits_Address |= (MASK_HIGH_BITS & Address) >> 8; /* mask cause the I2C send only 1 byte per frame */
    Low_Bits_Address |= (MASK_LOW_BITS & Address); /* mask cause the I2C send only 1 byte per frame */

    while (I2CMasterBusy(I2C1_BASE)) /* wait when the master is busy */
    {
    }

    I2CMasterSlaveAddrSet(I2C1_BASE, SLAVE_ADD, false); /* set slave address which is macro 0x50 */
    I2CMasterDataPut(I2C1_BASE, High_Bits_Address); /* write High_Bits_Address as data */
    I2CMasterControl(I2C1_BASE, I2C_MASTER_CMD_BURST_SEND_START); /* continue write and master still have the bus */

    while (I2CMasterBusy(I2C1_BASE) == true)/* wait when the master is busy */
    {
    }

    I2CMasterDataPut(I2C1_BASE, Low_Bits_Address); /* write Low_Bits_Address as data */
    I2CMasterControl(I2C1_BASE, I2C_MASTER_CMD_BURST_SEND_CONT); /* continue write and master still have the bus */
    while (I2CMasterBusy(I2C1_BASE) == true)/* wait when the master is busy */
    {
    }

    for (index = 0; index < length; index++) /* loop in data buffer that will be write in external eeprom */
    {
        I2CMasterDataPut(I2C1_BASE, data[index]); /* write data[i] in external eeprom */
        I2CMasterControl(I2C1_BASE, I2C_MASTER_CMD_BURST_SEND_CONT);/* continue write and master still have the bus */
        while (I2CMasterBusy(I2C1_BASE) == true)/* wait when the master is busy */
        {
        }

    }
    I2CMasterControl(I2C1_BASE, I2C_MASTER_CMD_BURST_SEND_FINISH); /* leave the bus */
    //I2CMasterControl(I2C1_BASE, I2C_MASTER_CMD_BURST_SEND_STOP);
    while (I2CMasterBusy(I2C1_BASE))/* wait when the master is busy */
    {
    }

}

/* Eeprom_Ext_Read */
/* Parameters :  uint16 , uint32 ,uint16  */
/* I/p : void  */
/* O/p : N/A */
/* Return : Void */
/* Function that read EEPROM external   */
void Eeprom_Ext_Read(uint16_t Address, uint32_t * data, uint16_t length)
{
    uint32 index = 0;
    uint8 High_Bits_Address = 0;
    uint8 Low_Bits_Address = 0;

    High_Bits_Address |= (MASK_HIGH_BITS & Address) >> 8; /* mask cause the I2C send only 1 byte per frame */
    Low_Bits_Address |= (MASK_LOW_BITS & Address); /* mask cause the I2C send only 1 byte per frame */

    while (I2CMasterBusy(I2C1_BASE))/* wait when the master is busy */
    {
    }
    I2CMasterSlaveAddrSet(I2C1_BASE, SLAVE_ADD, false); /* set slave address which is macro 0x50 */
    I2CMasterDataPut(I2C1_BASE, High_Bits_Address); /* write High_Bits_Address as data */
    I2CMasterControl(I2C1_BASE, I2C_MASTER_CMD_BURST_SEND_START);/* continue write and master still have the bus */

    while (I2CMasterBusy(I2C1_BASE) == true)/* wait when the master is busy */
    {
    }

    I2CMasterDataPut(I2C1_BASE, Low_Bits_Address); /* write Low_Bits_Address as data */
    I2CMasterControl(I2C1_BASE, I2C_MASTER_CMD_BURST_SEND_CONT);/* continue write and master still have the bus */
    while (I2CMasterBusy(I2C1_BASE) == true)/* wait when the master is busy */
    {
    }

    I2CMasterSlaveAddrSet(I2C1_BASE, SLAVE_ADD, true);/* set slave address which is macro 0x50 */
    I2CMasterControl(I2C1_BASE, I2C_MASTER_CMD_BURST_RECEIVE_START);/* continue write and master still have the bus */

    while (I2CMasterBusy(I2C1_BASE) == true)/* wait when the master is busy */
    {
    }
    data[index] = I2CMasterDataGet(I2C1_BASE); /* read data from EEPROM and store it in data[0]*/
    for (index = 1; index < length; index++)
    {

        I2CMasterControl(I2C1_BASE, I2C_MASTER_CMD_BURST_RECEIVE_CONT);/* continue write and master still have the bus */

        while (I2CMasterBusy(I2C1_BASE) == true)/* wait when the master is busy */
        {
        }
        data[index] = I2CMasterDataGet(I2C1_BASE); /* read data from EEPROM and store it in data[index]*/
    }
    I2CMasterControl(I2C1_BASE, I2C_MASTER_CMD_BURST_RECEIVE_FINISH);/* leave the bus */

    while (I2CMasterBusy(I2C1_BASE))/* wait when the master is busy */
    {
    }

}

