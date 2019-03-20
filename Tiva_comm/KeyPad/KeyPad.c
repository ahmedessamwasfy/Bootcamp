#include "../Includes/Types.h"
#include "../Includes/Utilites.h"
#include "../Includes/Keypad.h"

#include "driverlib/sysctl.h"

/* keymap Global variable that contain the KEYPAD Values */
uint8 keymap[KEYPAD_ROW_NUM][KEYPAD_COL_NUM]={
                                               {NUM_1,NUM_2,NUM_3},
                                               {NUM_4,NUM_5,NUM_6},
                                               {NUM_7,NUM_8,NUM_9}
                                              };
/************************************************************************************
* Function Name:         Keypad_init
* Parameters (in):       void
* Parameters (inout):    void
* Parameters (out):      void
* Return value:          void
* Description:           Function that initialize the KEYPAD pin
************************************************************************************/
void Keypad_init(void)
{   uint32 dumydelay;
    SysCtlPeripheralEnable(KEYPAD_COL1_clk);
    SysCtlPeripheralEnable(KEYPAD_COL2_clk);
    SysCtlPeripheralEnable(KEYPAD_COL3_clk);

    SysCtlPeripheralEnable(KEYPAD_RAW1_clk);
    SysCtlPeripheralEnable(KEYPAD_RAW2_clk);
    SysCtlPeripheralEnable(KEYPAD_RAW3_clk);


    (*((volatile uint32_t *)0x40007520)) = 0x4C4F434B;





    /* Initialize KEYPAD_RAW1 as OUTPUT */
    GPIOPinTypeGPIOOutput(KEYPAD_RAW1_PORT,KEYPAD_RAW1_PIN);
    /* Initialize KEYPAD_RAW2 as OUTPUT */
    GPIOPinTypeGPIOOutput(KEYPAD_RAW2_PORT,KEYPAD_RAW2_PIN);
    /* Initialize KEYPAD_RAW3 as OUTPUT */
    GPIOPinTypeGPIOOutput(KEYPAD_RAW3_PORT,KEYPAD_RAW3_PIN);
    GPIOPinWrite (KEYPAD_RAW1_PORT, KEYPAD_RAW1_PIN,KEYPAD_RAW1_PIN);
    GPIOPinWrite (KEYPAD_RAW2_PORT, KEYPAD_RAW2_PIN,KEYPAD_RAW2_PIN);
    GPIOPinWrite (KEYPAD_RAW3_PORT, KEYPAD_RAW3_PIN,KEYPAD_RAW3_PIN);

    /* Initialize KEYPAD_COL1 as INPUT */
     GPIOPinTypeGPIOInput(KEYPAD_COL1_PORT,KEYPAD_COL1_PIN);
      /* Enable the PUR for KEYPAD_COL1 */
     GPIOPadConfigSet(KEYPAD_COL1_PORT,KEYPAD_COL1_PIN,GPIO_STRENGTH_2MA,GPIO_PIN_TYPE_STD_WPU);
      /* Initialize KEYPAD_COL2 as INPUT */
      GPIOPinTypeGPIOInput(KEYPAD_COL2_PORT,KEYPAD_COL2_PIN);
      /* Enable the PUR for KEYPAD_COL2 */
      GPIOPadConfigSet(KEYPAD_COL2_PORT,KEYPAD_COL2_PIN,GPIO_STRENGTH_2MA,GPIO_PIN_TYPE_STD_WPU);

      /* Initialize KEYPAD_COL3 as INPUT */
      GPIOPinTypeGPIOInput(KEYPAD_COL3_PORT,KEYPAD_COL3_PIN);
      /* Enable the PUR for KEYPAD_COL3 */
      GPIOPadConfigSet(KEYPAD_COL3_PORT,KEYPAD_COL3_PIN,GPIO_STRENGTH_2MA,GPIO_PIN_TYPE_STD_WPU);





}
/************************************************************************************
* Function Name:        Keypad_getPressedKey
* Parameters (in):      void
* Parameters (inout):   void
* Parameters (out):     key
* Return value:         uint8
* Description:          Function that return the keypad value
************************************************************************************/

uint8 Keypad_getPressedKey(void)
{
    /* int32_t GPIOPinRead (uint32_t ui32Port, uint8_t ui8Pins)*/
    /* void GPIOPinWrite (uint32_t ui32Port, uint8_t ui8Pins, uint8_t ui8Val) */
        uint8 key=NUM_ZERO;
        uint8 success_flag=NUM_ZERO;
        uint8 raw;
        uint8 col;


        GPIOPinWrite (KEYPAD_RAW1_PORT, KEYPAD_RAW1_PIN, LOW);
        GPIOPinWrite (KEYPAD_RAW2_PORT, KEYPAD_RAW2_PIN, KEYPAD_RAW2_PIN);
        GPIOPinWrite (KEYPAD_RAW3_PORT, KEYPAD_RAW3_PIN, KEYPAD_RAW3_PIN);
        if(!GPIOPinRead (KEYPAD_COL1_PORT, KEYPAD_COL1_PIN))
        {
           col=NUM_ZERO;
           raw=NUM_ZERO;
           success_flag=NUM_1;
        }
        else if(!GPIOPinRead (KEYPAD_COL2_PORT, KEYPAD_COL2_PIN))
        {
           col=NUM_1;
           raw=NUM_ZERO;
           success_flag=NUM_1;
        }
        else if(!GPIOPinRead (KEYPAD_COL3_PORT, KEYPAD_COL3_PIN))
        {
          col=NUM_2;
          raw=NUM_ZERO;
          success_flag=NUM_1;
        }

        GPIOPinWrite (KEYPAD_RAW1_PORT, KEYPAD_RAW1_PIN,KEYPAD_RAW1_PIN);
        GPIOPinWrite (KEYPAD_RAW2_PORT, KEYPAD_RAW2_PIN,LOW);
        GPIOPinWrite (KEYPAD_RAW3_PORT, KEYPAD_RAW3_PIN,KEYPAD_RAW3_PIN);
        if(!GPIOPinRead (KEYPAD_COL1_PORT, KEYPAD_COL1_PIN))
        {
          col=NUM_ZERO;
          raw=NUM_1;
          success_flag=NUM_1;
        }
        else if(!GPIOPinRead (KEYPAD_COL2_PORT, KEYPAD_COL2_PIN))
        {
          col=NUM_1;
          raw=NUM_1;
          success_flag=NUM_1;
        }
        else if(!GPIOPinRead (KEYPAD_COL3_PORT, KEYPAD_COL3_PIN))
        {
          col=NUM_2;
          raw=NUM_1;
          success_flag=NUM_1;
        }
        GPIOPinWrite (KEYPAD_RAW1_PORT, KEYPAD_RAW1_PIN,KEYPAD_RAW1_PIN);
        GPIOPinWrite (KEYPAD_RAW2_PORT, KEYPAD_RAW2_PIN,KEYPAD_RAW2_PIN);
        GPIOPinWrite (KEYPAD_RAW3_PORT, KEYPAD_RAW3_PIN,LOW);
        if(!GPIOPinRead (KEYPAD_COL1_PORT, KEYPAD_COL1_PIN))
        {
          col=NUM_ZERO;
          raw=NUM_2;
          success_flag=NUM_1;
        }
        else if(!GPIOPinRead (KEYPAD_COL2_PORT, KEYPAD_COL2_PIN))
        {
          col=NUM_1;
          raw=NUM_2;
          success_flag=NUM_1;
        }
        else if(!GPIOPinRead (KEYPAD_COL3_PORT, KEYPAD_COL3_PIN))
        {
          col=NUM_2;
          raw=NUM_2;
          success_flag=NUM_1;
        }



   if(NUM_1==success_flag)
   {
     key= keymap[raw][col];
   }
   else
   {
      key=0;
   }
return key;

}
