/*
 * Manager.c
 *
 *  Created on: Mar 20, 2019
 *      Author: AVE-LAP-005
 */
#include "../includes/Std_Types.h"
#include "../includes/numbers.h"
#include "../UART/uart.h"
#include "Manager.h"

/******************************Get_Distance()*******************
 *
 * I/P:NOTHING
 * O/p:uint8_t
 *
 **************************************************************/

uint8 Get_Distance()
{
    uint8 Distance=NUM_ZERO;
    uint8 Duty=UART_Receive();
    Distance = (2.55535 * Duty);
	UART_Transmit(Distance);
    return Distance;

}
