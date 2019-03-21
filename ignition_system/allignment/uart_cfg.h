
#ifndef UART_CFG_H_
#define UART_CFG_H_



#define F_CPU 16000000UL
#define FREQUENCY 16

/**********************/
#define BAUDRATE     115200 /* Baud rate */
#define NO_STOPBIT   UART_CONFIG_STOP_ONE
#define PARITYMODE   UART_CONFIG_PAR_NONE
#define DATASIZE     UART_CONFIG_WLEN_8

/*********************/

typedef struct{
    uint32_t BaudRate;
    uint8_t No_StopBits;
    uint8_t Parity_Mode;
    uint8_t Data_Size;
    uint8_t SpeedMode;
    } UART_STRCT;


#endif /* UART_CFG_H_ */
