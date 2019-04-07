#ifndef CAN_H_
#define CAN_H_
#include <stdint.h>

#define ID_TX 2  /*THE ADDRESS WILL BE TRANSMIT BY CAN ON MAILBOX 1 IN TRANSMIT NODE */
#define DATA 1 /* DATA WILL BE SEND IN CAN FRAME */

#define ID_RX 1 /*THE ADDRESS WILL BE RECEIVED BY MAILBOX 2 IN RECEIVE NODE */
#define DATA_RECEIVE 1 /* DATA WILL BE RECEIVED IN CAN FRAME */


extern void CANIntHandler(void);
extern void vTaskCode_INIT_CAN_ZERO(void * pvParameters);/*INIT task */
extern void vTaskCode_NODE_ZERO_START(void * pvParameters);/*Startup node Task */
extern void vTaskCode_NODE_RX(void * pvParameters);/*RECIVE TASK*/
extern void vTaskCode_NODE_TX(void * pvParameters);

#endif /* CAN_H_ */
