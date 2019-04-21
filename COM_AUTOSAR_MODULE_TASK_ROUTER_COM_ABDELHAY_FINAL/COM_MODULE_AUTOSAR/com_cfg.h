#ifndef COM_CFG_H_
#define COM_CFG_H_
#include "Types.h"



/* signal configuration  */
typedef struct
{
    uint8 PDUID ;
    uint8 SIGNAL_SIZE ;
    uint8 START_BIT ;
    uint8 DATA;
} signal_cfg_s;


/* PDU configuration  */
typedef struct
{
    uint8 PCI ;
    uint8 PRIORITY ;
    uint8 PERIDICTY ;
    const uint8 CNST_PERIODICTY;
} pdu_cfg_s ;


#define MAX_SIGNAL 3

#define MAX_PDU 2

#define SIGNAL_SIZE_6_BIT   6
#define SIGNAL_SIZE_5_BIT   5
#define SIGNAL_SIZE_1_BIT   1
#define SIGNAL_SIZE_3_BIT   3

#define START_BIT_0 0
#define START_BIT_3 3
#define START_BIT_5 5

#define PDU0_ID 0
#define PDU1_ID 1
#define PDU2_ID 2
#define PDU3_ID 3

#define DATA_INIT_VALUE 0

extern pdu_cfg_s pdu_arr[MAX_PDU] ;
extern signal_cfg_s signal_arr[MAX_SIGNAL];

#endif /* COM_CFG_H_ */
