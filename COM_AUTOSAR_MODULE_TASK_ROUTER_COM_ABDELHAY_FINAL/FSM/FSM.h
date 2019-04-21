/*
 * FSM.h
 *
 *  Created on: Mar 20, 2019
 *      Author: AVE-LAP-005
 */

#ifndef FSM_FSM_H_
#define FSM_FSM_H_

typedef enum STATE_t{
    STATE_ONE_t=1 ,
    STATE_TWO_t,
    STATE_THREE_t,
    STATE_FOUR_t,
    STATE_FIVE_t,
}STATE_t;
uint8_t FSM(uint8_t distance);



#endif /* FSM_FSM_H_ */
