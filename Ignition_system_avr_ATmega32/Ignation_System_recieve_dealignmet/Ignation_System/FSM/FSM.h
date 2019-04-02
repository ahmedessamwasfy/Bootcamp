/*
 * FSM.h
 *
 *  Created on: Mar 20, 2019
 *      Author:Muhamed Hagag
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

extern uint8 FSM(uint8 distance);



#endif /* FSM_FSM_H_ */
