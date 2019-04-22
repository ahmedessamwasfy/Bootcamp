#include "com_cfg.h"







/* array of structure from signal_cfg_s type,
 *  we have 3 signal in our system (CMD >> 5 bits ) (ignition state 1 bit ) (DIS >> 6 bit ) */
signal_cfg_s signal_arr[MAX_SIGNAL] = { { PDU0_ID , SIGNAL_SIZE_3_BIT , START_BIT_0 , DATA_INIT_VALUE  },

                                        { PDU0_ID , SIGNAL_SIZE_1_BIT , START_BIT_3 , DATA_INIT_VALUE  },

                                        { PDU1_ID , SIGNAL_SIZE_6_BIT , START_BIT_0 , DATA_INIT_VALUE  }
                                      };






/* array of structure from pdu_cfg_s type ,
 * in our system we have 2 PDU , (PDU0 >> CMD+IGN+PDU ID (PCI) ) , (PDU1 >> DIS+PDU ID (PCI )*/
pdu_cfg_s pdu_arr[MAX_PDU] = { { PDU0_ID, 4, 50  ,  50  },
                               { PDU1_ID, 4, 100 , 100 }
                             };
