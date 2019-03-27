#include "Dio.h"
#include "Dio_MemMap.h"
#include "internal.h"

Dio_ConfigPort  Port_g[MAX_SIZE]={PORTF_,OP};

Dio_ConfigChannel  Channel_struct[MAX_SIZE]={{ID4,PF4,PORTF_,IP},{ID2,PF2,PORTF_,OP},{ID1,PF1,PORTF_,OP},{ID3,PF3,PORTF_,OP}};

Dio_ChannelGroupType channel_group[MAX_CHANNEL_GROUP]={{0X0f,ZERO,PORTF_}};
