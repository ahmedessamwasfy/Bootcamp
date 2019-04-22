
#include <stdbool.h>
#include <stdint.h>
#include "commen.h"
#include "driverlib/sysctl.h"
#include "driverlib/ssi.h"
#include "driverlib/pin_map.h"
#include "inc/hw_memmap.h"
#include "driverlib/gpio.h"


void SPI_Init(uint8_t channel)
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



      }
      case NUM_3:
                 {
                     SysCtlPeripheralEnable(SYSCTL_PERIPH_SSI3);  //Enable ssi3
                                  SysCtlPeripheralEnable(SYSCTL_PERIPH_GPIOD); //Enable PORT D GPIO to be used with ssi3 data and frame signals

                                  GPIOPinConfigure(GPIO_PD0_SSI3CLK);
                                  GPIOPinConfigure(GPIO_PD1_SSI3FSS);
                                  GPIOPinConfigure(GPIO_PD2_SSI3RX);
                                  GPIOPinConfigure(GPIO_PD3_SSI3TX);
                                  GPIOPinTypeSSI(GPIO_PORTD_BASE,GPIO_PIN_0|GPIO_PIN_1|GPIO_PIN_2|GPIO_PIN_3);


                                  SSIConfigSetExpClk(SSI3_BASE,  SysCtlClockGet(), SSI_FRF_MOTO_MODE_0, SSI_MODE_SLAVE, 1000000, 16);

                                  SSIEnable(SSI3_BASE);
                                  break;
                 }
    }


}

uint32_t SPI_Transmit (uint32_t ui32Data)
{
  uint32_t Succes =FALSE;

  Succes=SSIDataPutNonBlocking(SSI0_BASE ,ui32Data);

  return Succes;

}

uint32_t SPI_Recieve (uint32_t* ui32Data)
{
  uint32_t Succes =FALSE;

  Succes=SSIDataGetNonBlocking(SSI3_BASE,ui32Data);

  return Succes;

}

