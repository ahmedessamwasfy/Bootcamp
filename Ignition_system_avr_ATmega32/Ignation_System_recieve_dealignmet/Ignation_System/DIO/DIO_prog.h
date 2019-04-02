
#ifndef DIO_PROG_H
#define DIO_PROG_H
#define IDA0    0
#define IDA1    1
#define IDA2    2
#define IDA3    3
#define IDA4    4
#define IDA5    5
#define IDA6    6
#define IDA7    7

#define IDB0    8
#define IDB1    9
#define IDB2    10
#define IDB3    11
#define IDB4    12
#define IDB5    13
#define IDB6    14
#define IDB7    15

#define IDC0    16
#define IDC1    17
#define IDC2    18
#define IDC3    19
#define IDC4    20
#define IDC5    21
#define IDC6    22
#define IDC7    23

#define IDD0    24
#define IDD1    25
#define IDD2    26
#define IDD3    27
#define IDD4    28
#define IDD5    29
#define IDD6    30
#define IDD7    31

#define OUTPUT    1
#define INPUT     0

void DIO_WritePin(uint8 PinNum,uint8 PinValue);
/************************************************************************************
* Function Name:       DIO_WritePin
* Parameters (in):     uint8 PinNum      PIN Number
                       uint8 PinValue    Value (HIGH 1),(LOW 0)
* Parameters (inout):  GPIO_PORTx_OUTPUT   the GPIO_OUTPUT register
* Parameters (out):    void
* Return value:        void
* Description:         Write on GPIO Pin
************************************************************************************/

uint8 DIO_ReadPin(uint8 PinNum);
/************************************************************************************
* Function Name:       DIO_ReadPin
* Parameters (in):     uint8 PinNum          GPIO PIN number
                       GPIO_PORTx_INPUT      GPIO PORTX INPUT register
* Parameters (inout): void
* Parameters (out):uint8 PinValue
* Return value:(HIGH=1) (LOW=0) 
* Description:Function that return GPIO PIN Value
************************************************************************************/	


void DIO_SetPinDirection(uint8 PinNum,uint8 PinDirection);
/************************************************************************************
* Function Name:       DIO_SetPinDirection
* Parameters (in):     uint8 PinNum          the pin number
                       uint8 PinDirection    the pin direction (OUTPUT =1) ,(INPUT=0)
* Parameters (inout):  GPIO_PORT0_DIR
* Parameters (out):    void
* Return value:        void
* Description:         Function that Set a GPIO PIN Direction
************************************************************************************/

void DIO_TogglePin(uint8 PinNum);
/************************************************************************************
* Function Name:       DIO_TogglePin
* Parameters (in):     uint8 PinNum
* Parameters (inout):  GPIO_PORT0_OUTPUT
* Parameters (out):    void
* Return value:        void
* Description:         Function that toggle a GPIO PIN
************************************************************************************/
#endif
