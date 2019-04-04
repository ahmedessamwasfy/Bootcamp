#ifndef CAN_H_
#define CAN_H_
#include <stdint.h>

extern void vTaskCode_startup(void * pvParameters);/*startup TASK*/
extern void vTaskCode4(void * pvParameters);/*RECIVE TASK*/
extern void CANIntHandler(void);
extern void vTaskCode3(void * pvParameters);/*INIT task */
extern void vTaskCode5(void * pvParameters);/*transmit task */
extern void vTaskCode_NODE_ZERO_RX(void * pvParameters);/*NODE 0 RECIVE TASK*/
extern void vTaskCode_NODE_ONE_RX(void * pvParameters);/*NODE 1 RECIVE TASK*/
extern void vTaskCode_NODE_ZERO_START(void * pvParameters);/*startup TASK*/

extern void vTaskCode_NODE_ONE_TX(void * pvParameters);/*NODE ONE transmit task */
extern void vTaskCode_NODE_ZERO_TX(void * pvParameters);/*NODE ZERO transmit task */
#endif /* CAN_H_ */
