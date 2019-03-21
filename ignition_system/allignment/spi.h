/*
 * spi.h
 *
 *  Created on: Mar 20, 2019
 *      Author: AVE-LAP-44
 */

#ifndef SPI_SPI_H_
#define SPI_SPI_H_



void SPI_Init(uint8_t channel);
uint32_t SPI_Transmit (uint32_t ui32Data);
uint32_t SPI_Recieve (uint32_t* ui32Data);

#endif /* SPI_SPI_H_ */
