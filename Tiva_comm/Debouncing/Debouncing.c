/*
 * Keypad_Debounce.c
 *
 *  Created on: Mar 12, 2019
 *      Author: AVE-LAP-44
 */
#include "../Includes/Types.h"
#include "../Includes/Utilites.h"
#include "../Includes/Debouncing.h"
#include "../Includes/Keypad.h"
#include "../Includes/Keypad_cfg.h"


uint8 keypad_state=0;
static uint8 state_count=0;
static uint8 prev_state=0;

void Button_Pressed(void)
{   uint8 current_state=NUM_1;
    GPIOPinWrite (KEYPAD_RAW1_PORT, KEYPAD_RAW1_PIN,LOW);
    GPIOPinWrite (KEYPAD_RAW2_PORT, KEYPAD_RAW2_PIN,KEYPAD_RAW2_PIN);
    GPIOPinWrite (KEYPAD_RAW3_PORT, KEYPAD_RAW3_PIN,KEYPAD_RAW3_PIN);

    current_state =current_state&&GPIOPinRead(KEYPAD_COL1_PORT, KEYPAD_COL1_PIN)&&GPIOPinRead(KEYPAD_COL2_PORT, KEYPAD_COL2_PIN)
                    &&GPIOPinRead(KEYPAD_COL3_PORT, KEYPAD_COL3_PIN);

    GPIOPinWrite (KEYPAD_RAW1_PORT, KEYPAD_RAW1_PIN,KEYPAD_RAW1_PIN);
    GPIOPinWrite (KEYPAD_RAW2_PORT, KEYPAD_RAW2_PIN,LOW);
    GPIOPinWrite (KEYPAD_RAW3_PORT, KEYPAD_RAW3_PIN,KEYPAD_RAW3_PIN);
    current_state =current_state&&GPIOPinRead(KEYPAD_COL1_PORT, KEYPAD_COL1_PIN)&&GPIOPinRead(KEYPAD_COL2_PORT, KEYPAD_COL2_PIN)
                        &&GPIOPinRead(KEYPAD_COL3_PORT, KEYPAD_COL3_PIN);

    GPIOPinWrite (KEYPAD_RAW1_PORT, KEYPAD_RAW1_PIN,KEYPAD_RAW1_PIN);
    GPIOPinWrite (KEYPAD_RAW2_PORT, KEYPAD_RAW2_PIN,KEYPAD_RAW2_PIN);
    GPIOPinWrite (KEYPAD_RAW3_PORT, KEYPAD_RAW3_PIN,LOW);
    current_state =current_state&&GPIOPinRead(KEYPAD_COL1_PORT, KEYPAD_COL1_PIN)&&GPIOPinRead(KEYPAD_COL2_PORT, KEYPAD_COL2_PIN)
                            &&GPIOPinRead(KEYPAD_COL3_PORT, KEYPAD_COL3_PIN);

    if(current_state==prev_state)
    {
        state_count +=NUM_1;
    }
    else
    {
        state_count=NUM_ZERO;
        prev_state=current_state;
    }
    if(NUM_5==state_count)
    {
        keypad_state=!current_state;
    }



}
