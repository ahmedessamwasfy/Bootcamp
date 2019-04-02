
#ifndef SPI_H_
#define SPI_H_

#include "Types.h"
#include "micro_config.h"
#include "common_macros.h"

/*******************************************************************************
 *                      Functions Prototypes                                   *
 *******************************************************************************/
void SPI_initMaster(void); 
void SPI_initSlave(void);
void SPI_sendByte(const uint8 data);


#endif
