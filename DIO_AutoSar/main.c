#include "Dio.h"
#include "Reg.h"
Dio_ChannelGroupType structx = { 0X1f, 0, PORTF_ };
#define SYSCTL_RCGC2_R (*((volatile unsigned long *)0x400FE108))
void PortF_Init(void);
int main(void);

int main(void)
{
    PortF_Init();/*PORTF init FUN */

    //Dio_WriteChannel(INVALID_ID, STD_HIGH);/*CHECK DET function to detect invalid id reporting error and turn on led2*/

    PortF_Init();/*PORTF init FUN */

    while (1)
    {
        //Dio_WriteChannel(ID2, STD_HIGH); /*Test_WriteChannel*/
        // Dio_WritePort(PORTF_, 0xE);/*Led1,2,0 should turn on*/
        //Dio_WriteChannel(INVALID_ID, STD_HIGH);/*CHECK DET function to detect invalid id reporting error and turn on led2*/
        if (!Dio_ReadChannelGroup(&structx))/*CHECK Read channel group  */
        {
            Dio_WriteChannel(ID2, STD_HIGH);
        }
    }

}

void PortF_Init(void)
{
    /*Activate PORTF Clock*/
    volatile uint8 delay;
    SYSCTL_RCGC2_R |= 0x00000020; /* 1) activate clock for Port F*/
    delay = SYSCTL_RCGC2_R; /* allow time for clock to start*/
    /*Disable Analog Function of PORTF*/
    PORTF->AMSEL = (uint32) 0x00;
    /*Set Direction of PF1 , PF2 , PF3 output , PF4 i/p */
    PORTF->DIR |= (uint32) 0x0E;
    /*Disable Alternate Function of PORTF*/
    PORTF->AFSEL = (uint32) 0x00;
    /*Enable digital I/O on PF1 , PF2 , PF3 */
    PORTF->DEN = (uint32) 0xff;
    /* Enable internal pull up */
    PORTF->PUR = (uint32) 0x11;
    PORTF->DATA = (uint32) 0x00;
}

