#include <stdint.h>
#include "includes/Types.h"
#include "Manager.h"
#include "FSM.h"
/*******************************************/
/*the used MARCROS*/
#define ZERO 0
#define NUM_160 160
#define NUM_90 90
#define NUM_255 255
#define NUM_20 20
#define NUM_5 5
/*******************************************/
uint8 FSM(uint8 distance)
{
//uint8_t distance = Get_Distance();
uint8 state=0 ;

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

else if((distance == ZERO) && (distance <= NUM_5)  )
{
    state=STATE_FIVE_t; /*fire speed*/
}

return state;/* return state */
}


