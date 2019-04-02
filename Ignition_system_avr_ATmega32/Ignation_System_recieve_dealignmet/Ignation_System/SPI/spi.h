
#ifndef SPI_H_
#define SPI_H_

#define SPI_SS      IDB4
#define SPI_MOSI    IDB5
#define SPI_MISO    IDB6
#define SPI_CLK     IDB7

extern void SPI_MasterInit(void);
extern void SPI_SlaveInit(void);
extern void SPI_send(uint8 data);
extern uint8 SPI_Recieve(void);

#endif /* SPI_H_ */