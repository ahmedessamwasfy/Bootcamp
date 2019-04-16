
#include "LED.h"
void LED_INIT(void)
{
    //
        // Enable the GPIO port that is used for the on-board LED.
        //
        SysCtlPeripheralEnable(SYSCTL_PERIPH_GPIOF);
        //
        // Check if the peripheral access is enabled.
        //
        while(!SysCtlPeripheralReady(SYSCTL_PERIPH_GPIOF))
        {
        }
        GPIOPinTypeGPIOOutput(GPIO_PORTF_BASE,( GPIO_PIN_1 | GPIO_PIN_2 |GPIO_PIN_3));

}
void TOG_LED1(void)
{
    GPIOPinWrite(GPIO_PORTF_BASE, (GPIO_PIN_1) ,GPIO_PIN_1);
    SysCtlDelay(1600000/3);//100msec delay

    GPIOPinWrite(GPIO_PORTF_BASE, (GPIO_PIN_1) ,0x0);
    SysCtlDelay(1600000/3);//100msec delay

}
void TOG_LED2(void)
{
    GPIOPinWrite(GPIO_PORTF_BASE, (GPIO_PIN_2) ,GPIO_PIN_2);
    SysCtlDelay((1600000/3)*2);//100msec delay

    GPIOPinWrite(GPIO_PORTF_BASE, (GPIO_PIN_2) ,0x0);
    SysCtlDelay((1600000/3)*2);//100msec delay

}



