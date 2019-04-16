#include <stdbool.h>
#include <stdint.h>
#include "inc/hw_i2c.h"
#include "inc/hw_memmap.h"
#include "inc/hw_types.h"
#include "driverlib/gpio.h"
#include "driverlib/i2c.h"
#include "driverlib/pin_map.h"
#include "driverlib/sysctl.h"
#include "driverlib/uart.h"
#include "utils/uartstdio.h"
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

/*i2c_init*/
/* Parameters :  void  */
/* I/p : void  */
/* O/p : N/A */
/* Return : Void */
/* Function that initialize I2C CHANNEL 1 PROTOCAL   */
void i2c_init()
{
    SysCtlClockSet(SYSCTL_SYSDIV_1 | SYSCTL_USE_OSC | SYSCTL_OSC_MAIN |
    SYSCTL_XTAL_16MHZ);
    SysCtlPeripheralEnable(SYSCTL_PERIPH_I2C1);
    SysCtlPeripheralEnable(SYSCTL_PERIPH_GPIOA);
    GPIOPinConfigure(GPIO_PA6_I2C1SCL);
    GPIOPinConfigure(GPIO_PA7_I2C1SDA);
    GPIOPinTypeI2CSCL(GPIO_PORTA_BASE, GPIO_PIN_6);
    GPIOPinTypeI2C(GPIO_PORTA_BASE, GPIO_PIN_7);
    I2CMasterInitExpClk(I2C1_BASE, SysCtlClockGet(), false);
}



/*init_slave_i2c */
/* Parameters :  uint8_t  */
/* I/p : void  */
/* O/p : N/A */
/* Return : Void */
/* Function that initialize slave I2C  */
void init_slave_i2c(uint8_t SLAVE_ADDR)
{
    I2CSlaveEnable(I2C1_BASE);
    I2CSlaveInit(I2C1_BASE, SLAVE_ADDR);
}




/*init_master */
/* Parameters :  void  */
/* I/p : void  */
/* O/p : N/A */
/* Return : Void */
/* Function that initialize master I2C1    */
void init_master()
{
    I2CMasterEnable(I2C1_BASE);
}



/* mode */
/* Parameters :  uint8 , uint8  */
/* I/p : void  */
/* O/p : N/A */
/* Return : Void */
/* Function that select the mode of master to read or write from slave     */
void mode(uint8_t SLAVE_ADDR, uint8_t mode)
{
    if (mode == READ) /* if mode == READ , = 1 that master read from slave */
    {
        I2CMasterSlaveAddrSet(I2C1_BASE, SLAVE_ADDRESS, true);
    }

    else if (mode == WRITE)/* if mode == WRITE , = 0 that master write in slave */
    {
        I2CMasterSlaveAddrSet(I2C1_BASE, SLAVE_ADDRESS, false);
    }
}



/*I2c_Read_Slave */
/* Parameters :  void  */
/* I/p : void  */
/* O/p : N/A */
/* Return : uint32 */
/* Function that read the value in slave device  */
uint32_t I2c_Read_Slave()
{
    uint32_t data = 0;
    data = I2CSlaveDataGet(I2C1_BASE);
    // I2CMasterControl(I2C1_BASE, I2C_MASTER_CMD_SINGLE_RECEIVE);
    return data;

}



/* I2c_master_Write */
/* Parameters :  uint32_t , uint32_t  */
/* I/p : void  */
/* O/p : N/A */
/* Return : Void */
/* Function that let master write in slave deveice   */
void I2c_master_Write(uint32_t Data, uint32_t Slave_address)
{
    I2CMasterSlaveAddrSet(I2C1_BASE, Slave_address, false);
    I2CMasterDataPut(I2C1_BASE, Data);
    I2CMasterControl(I2C1_BASE, I2C_MASTER_CMD_SINGLE_SEND);
}




/*I2c_master_read */
/* Parameters :  uint32  */
/* I/p : void  */
/* O/p : N/A */
/* Return : uint32 */
uint32_t I2c_master_read(uint32_t Slave_address)
{
    uint32 data = 0; /* variable to store the data after read from slave device */
    I2CMasterSlaveAddrSet(I2C1_BASE, Slave_address, true);
    data = I2CMasterDataGet(I2C1_BASE); /* read data from slave and store it in data variable  */
    I2CMasterControl(I2C1_BASE, I2C_MASTER_CMD_SINGLE_RECEIVE);
    return data;

}
