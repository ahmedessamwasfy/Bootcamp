
#ifndef ROUTER_CFG_H_
#define ROUTER_CFG_H_
#include "Types.h"
#define PCI_BIT 6

enum protocal
{
    UART , SPI
};

#define MAX_PDU_ID 4
extern uint8 protocal_arr[MAX_PDU_ID];

#endif /* ROUTER_CFG_H_ */
