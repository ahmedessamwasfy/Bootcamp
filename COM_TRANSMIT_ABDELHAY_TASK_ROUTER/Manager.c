/*
 * Manager.c
 *
 *  Created on: Mar 20, 2019
 *      Author: AVE-LAP-005
 */
#include <stdint.h>
#include "Manager.h"
#include "uart.h"
/******************************Get_Distance()*******************
 *
 * I/P:NOTHING
 * O/p:uint8_t
 *
 **************************************************************/

uint8_t Get_Distance(){
    uint8_t Distance=0;
    uint8_t Duty=UART_Recive();
 Distance = (2.55535 * Duty);
 return Distance;

}
