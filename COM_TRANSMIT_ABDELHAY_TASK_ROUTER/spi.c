/*
 * spi.c
 *
 *  Created on: Mar 20, 2019
 *      Author: AVE-LAP-44
 */
#include <stdbool.h>
#include <stdint.h>
#include "commen.h"
#include "driverlib/sysctl.h"
#include "driverlib/ssi.h"
#include "driverlib/pin_map.h"
#include "inc/hw_memmap.h"
#include "driverlib/gpio.h"
#include"spi.h"

void SPI_Init(uint8 channel)
{
    switch (channel)
    {
      case NUM_ZERO :
      {
             /* The SSI0 peripheral must be enabled for use. */

             SysCtlPeripheralEnable(SYSCTL_PERIPH_SSI0);

             SysCtlPeripheralEnable(SYSCTL_PERIPH_GPIOA);

             /* Configure the pin muxing for SSI0 functions on port A2, A3, A4, and A5. */

             GPIOPinConfigure(GPIO_PA2_SSI0CLK);
             GPIOPinConfigure(GPIO_PA3_SSI0FSS);
             GPIOPinConfigure(GPIO_PA4_SSI0RX);
             GPIOPinConfigure(GPIO_PA5_SSI0TX);


             GPIOPinTypeSSI(GPIO_PORTA_BASE, GPIO_PIN_5 | GPIO_PIN_4 | GPIO_PIN_3 |
                                GPIO_PIN_2);

             SSIConfigSetExpClk(SSI0_BASE, SysCtlClockGet(), SSI_FRF_MOTO_MODE_0,
                                    SSI_MODE_MASTER, 1000000, 16);

             SSIEnable(SSI0_BASE);
             break;
      }
      case NUM_2:
             {

                 SysCtlPeripheralEnable(SYSCTL_PERIPH_SSI2);  //Enable ssi2
                 SysCtlPeripheralEnable(SYSCTL_PERIPH_GPIOB); //Enable PORT B GPIO to be used with ssi2 data and frame signals

                 GPIOPinConfigure(GPIO_PB4_SSI2CLK);
                 GPIOPinConfigure(GPIO_PB5_SSI2FSS);
                 GPIOPinConfigure(GPIO_PB6_SSI2RX);
                 GPIOPinConfigure(GPIO_PB7_SSI2TX);
                 GPIOPinTypeSSI(GPIO_PORTB_BASE,GPIO_PIN_4|GPIO_PIN_5|GPIO_PIN_6|GPIO_PIN_7);

                 SSIConfigSetExpClk(SSI2_BASE,  SysCtlClockGet(), SSI_FRF_MOTO_MODE_0, SSI_MODE_SLAVE, 1000000, 16);

                 SSIEnable(SSI2_BASE);
                  break;
             }
    }


}

uint32_t SPI_Transmit (uint32_t ui32Data)
{
  uint32_t Succes =FALSE;
  /* Send data using spi0  */
  Succes=SSIDataPutNonBlocking(SSI0_BASE ,ui32Data);

  return Succes;

}

uint32_t SPI_Recieve (uint32_t* ui32Data)
{
  uint32_t Succes =FALSE;

  Succes=SSIDataGetNonBlocking(SSI2_BASE,ui32Data);

  return Succes;

}

