/*
 * FSM.c
 *
 *  Created on: Mar 20, 2019
 *      Author: Muhamed Hagag
 */
#include "../includes/Std_Types.h"
#include "../includes/numbers.h"

#include "FSM.h"

/*******************************************/
/*the used MARCROS*/

/*******************************************/
uint8 FSM(uint8 distance)
{
//uint8_t distance = Get_Distance();
uint8 state=NUM_ZERO ;

if((distance <= NUM_160) && (distance>NUM_90))
{
    state=STATE_ONE_t; /*Maintain speed*/
}

else if((distance<= NUM_255) && (distance > NUM_160)  )
{
    state=STATE_TWO_t; /*increase speed*/
}

else if((distance > NUM_20) && (distance <= NUM_90)  )
{
    state=STATE_THREE_t; /*decrease speed*/
}

else if((distance > NUM_5) && (distance <= NUM_20)  )
{
    state=STATE_FOUR_t; /*break speed*/
}

else if((distance == NUM_ZERO) && (distance <= NUM_5)  )
{
    state=STATE_FIVE_t; /*fire speed*/
}

return state;/* return state */
}


