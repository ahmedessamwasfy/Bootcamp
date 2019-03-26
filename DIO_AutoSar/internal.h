#include "Platform_Types.h"
#ifndef INTERNAL_H_
#define INTERNAL_H_

#define PORTA_ 0U
#define PORTB_ 1U
#define PORTC_ 2U
#define PORTD_ 3U
#define PORTE_ 4U
#define PORTF_ 5U

#define ID0 (0U)  /*pin 0 ID */
#define ID1 (1U)  /*pin 1 ID --LED 0 ID  */
#define ID2 (2U)  /*pin 2 ID --LED 1 ID */
#define ID3 (3U)  /*pin 3 ID --LED 2 ID */
#define ID4 (4U)  /*pin 3 ID --BTN1 ON TIVE c Board  */

#define INVALID_ID 50

#define PF0 (0U) /*Bit 0 PORTF */
#define PF1 (1U) /*Bit 1 PORTF LED 0 */
#define PF2 (2U) /*Bit 2 PORTF LED 1  */
#define PF3 (3U) /*Bit 3 PORTF LED 2  */
#define PF4 (4U) /*Bit 4 PORTF BTN1 ON TIVE c Board  */


#define OP 1 /*OUTPUT*/
#define IP 0 /*INPUT*/

typedef struct
{   uint8 id ;
    uint8 Pin_Num;
    uint8 Port;
    uint8 Direction;
}Dio_ConfigChannel;

typedef struct
{   uint8 port_id ;
    uint8 Direction_port;
}Dio_ConfigPort;




#endif /* INTERNAL_H_ */
