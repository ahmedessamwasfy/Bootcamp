#if 0
#include <stdint.h>
#include <stdbool.h>
#include "Types.h"

#include "include/FreeRTOS.h"
#include "include/task.h"
#include "inc/hw_gpio.h"
#include "driverlib/gpio.h"
#include "include/event_groups.h"
#include "inc/hw_memmap.h"
#include "include/queue.h"
#include "BUTTON/BUTTON.h"
#include "FSM/FSM.h"
#include "Maneger/Manager.h"
#include "SPI/spi.h"
#include "com_cfg.h"
#include "com.h"
#include "ROUTER/Router.h"
#include "UART/uart.h"
#include "driverlib/pin_map.h"

extern QueueHandle_t SPI_TRANSMIT_QUEE; /* SPI Transmit Queue */
extern QueueHandle_t UART_RECEIVE_QUEE; /* UART Receive Queue */

static uint8 PDU_TX[MAX_SIGNAL]; /* transmit buffer include PDU with (SDU & PCI) */

#define DATA_INIT_VALUE 0
#define INDEX_INIT_VALUE 0
#define MAIN_TX_PERIODICTY 50
#define PCI_BIT 6

/**********************************************/
/*the used MACROS*/
#define PRESSED 1
#define NOT_PRESSED 0
#define ZERO 0
#define ONE 1
#define FIVE 5
#define EIGHT 8
#define COMMAND_MASK 0xff
#define DATA_MASK 0x1f
#define TEN 10
#define TASK_TWO_DELAY 50
/**********************************************/
uint8_t Ignition_on = ZERO, count = ZERO;

/*Init_Task */
/* Parameters : void , void */
/* I/p : void , void  */
/* O/p : N/A */
/* Return : Void */
/* Function that initialize UART , SPI , BTN    */
void Init_Task(void *pvParameters)
{
    while (1)
    {
        /*UART Initialize*/
        UART_Init();

        /*SPI Initialize*/
        SPI_Init(ZERO);

        /*Button Initialize*/
        BUTTON_Init();

        vTaskSuspend(NULL);
    }
}

/*Allignment_Task */
/* Parameters :void *pvParameters */
/* I/p : void , void  */
/* O/p : N/A */
/* Return : Void */
/* Allignment_Task */
void Allignment_Task(void *pvParameters)
{

    uint8 Distance;
    uint8 Command;
    while (1)
    {
        if (ONE == Ignition_on)/*start the system */
        {
            /*Get the distance*/
            Distance = Get_Distance();
            /*Get the Command*/

            Command = FSM(Distance);
            Distance /= EIGHT;

            /* signal_arr[] will be initialized in these stage by using com_send_signal() fun */
            com_send_signal(0, Command); /* command in first index */
            com_send_signal(1, 1); /* ignition in second index */
            com_send_signal(2, Distance); /* distance in third index */

        }
        vTaskDelay(200);
    }
}

/*Button_Task */
/* Parameters :void *pvParameters */
/* I/p : void , void  */
/* O/p : N/A */
/* Return : Void */
/* Function to check if BTN is pressed or not  */
void Button_Task(void *pvParameters)
{
    while (1)
    {
        if (Get_BUTTON() == PRESSED) /* Check if BTN pressed increment counter to detect the debouncing */
        {
            count++; /* increment count */
        }
        if (Get_BUTTON() == NOT_PRESSED)
        {
            count = ZERO;
        }

        if (count == TEN) /* check if counter equal 10 so the BTN is pressed */
        {
            Ignition_on = ONE; /* set Ignition flag */
            GPIOPinWrite(GPIO_PORTF_BASE, GPIO_PIN_2, GPIO_PIN_2);
            vTaskSuspend(NULL);
        }
        vTaskDelay(50);
    }
}

/*com_init */
/* Parameters : void , void */
/* I/p : void , void  */
/* O/p : N/A */
/* Return : Void */
/* Function that initialize COM module   */
void com_init(void)
{

}

/*concatenate */
/* Parameters : void , void */
/* I/p : void , void  */
/* O/p : N/A */
/* Return : Void */
/* Function that concatenate the signal with ID in 1 byte    */
static void concatenate(void)
{
    uint8 index;

    /* loop in sig_tx[] array and clear all element and assign by zero and assign bit 6,7 in PDU id */
    for (index = INDEX_INIT_VALUE; index < MAX_PDU; index++)
    {
        PDU_TX[index] = 0; /* clear all pdu_arr[]  element and assign it to zero */
        PDU_TX[index] = pdu_arr[index].PCI << PCI_BIT; /* assign bit 6,7 as PDU ID from pdu_array */
    }

    /* loop in loop in sig_tx[] array and assign the data in bit from 0 to 5 after concatenate using this algorithm */
    for (index = INDEX_INIT_VALUE; index < MAX_SIGNAL; index++)
    {
        PDU_TX[signal_arr[index].PDUID] |= signal_arr[index].DATA
                << signal_arr[index].START_BIT; /* concatenate */
    }
}

/*com_send_signal */
/* Parameters : uint8 , uint8 */
/* I/p : uint8 , uint8  */
/* O/p : N/A */
/* Return : Void */
/* Function that send signal 1 byte contain (SIGNAL , SIGNAL ID)  by COM module  */
void com_send_signal(uint8 id, uint8 data)
{
    signal_arr[id].DATA = data; /* access the signal_arr which include the structure of signals and access the data element */
}

/*com_receive_signal */
/* Parameters : uint8 */
/* I/p : uint8  */
/* O/p : N/A */
/* Return : uint8 */
/* Function that receive signal 1 byte contain (SIGNAL , SIGNAL ID)  by COM module  */
uint8 com_receive_signal(uint8 id)
{
    return 0;
}

/*ComMAIN_TX */
/* Parameters : void *pvParameters */
/* I/p : void */
/* O/p : N/A */
/* Return : Void */
/* Function that send signal 1 byte contain (SIGNAL , SIGNAL ID)  by COM module and control periodicty  */
void ComMAIN_TX(void *pvParameters)
{
    uint8 index = INDEX_INIT_VALUE; /*index for loop  in PDU_TX array */
    while (1)
    {
        //concatenate(); /* concatenate the 6 bit data and 2 bit PCI in 1 byte and add it to PDU_TX array */
        for (index = INDEX_INIT_VALUE; index < MAX_PDU; index++)
        {
            if (pdu_arr[PDU_TX[index] >> PCI_BIT].PERIDICTY == 0)
            {
                concatenate(); /* concatenate the 6 bit data and 2 bit PCI in 1 byte and add it to PDU_TX array */
                router_send(PDU_TX[index]); /* Routing based on configuration on ROUTER_CFG */
                pdu_arr[PDU_TX[index] >> PCI_BIT].PERIDICTY =
                        pdu_arr[PDU_TX[index] >> PCI_BIT].CNST_PERIODICTY;/*Assign periodicty with const periodicty */
            }
            else
            {
                pdu_arr[PDU_TX[index] >> PCI_BIT].PERIDICTY -=
                MAIN_TX_PERIODICTY;
            }

        }

        vTaskDelay(MAIN_TX_PERIODICTY);
    }
}

/*SPI_Task */
/* Parameters : void *pvParameters*/
/* I/p :  void  */
/* O/p : N/A */
/* Return : Void */
/* Function that send signal 1 byte SPI using QUEE   */
void SPI_Task(void *pvParameters)
{
    uint8 data;
    while (1)
    {
        if (ONE == Ignition_on) /* check if system is ON or OFF by this flag which set by BTN1 */
        {
            while (uxQueueMessagesWaiting(SPI_TRANSMIT_QUEE)) /* check if data assigned in spi queue */
            {
                xQueueReceive(SPI_TRANSMIT_QUEE, &data, 0);
                SPI_Transmit(data); /* Transmit data by SPI */
            }
        }
        vTaskDelay(250);

    }
}

/*UART0_Recv */
/* Parameters : void  , void   */
/* I/p : uint8 , void  */
/* O/p : N/A */
/* Return : uint8_t */
/* Function that receive data by UART0  */
uint8_t UART0_Recv(void)
{
    uint8_t data = DATA_INIT_VALUE;
    if (UARTCharsAvail(UART0_BASE))
    {
        data = UARTCharGetNonBlocking(UART0_BASE); /* get data from UART without Blocking*/
    }
    return data;
}

/*UartRecv_Task */
/* Parameters : void *pvParameters , void *pvParameters  */
/* I/p : uint8 , void  */
/* O/p : N/A */
/* Return : Void */
/* Function that receive data by UART0 and use the FIFO in QUEE which is first come first out   */
void UartRecv_Task(void *pvParameters)
{

    while (1)
    {
        uint8_t data = DATA_INIT_VALUE; /* variable to store the UART0 data */

        if (UARTCharsAvail(UART0_BASE)) /* check if there is any data avilable by UART0 */
        {
            data = UART0_Recv(); /* UART receive function */

            xQueueSendToBack(UART_RECEIVE_QUEE, &data, 10); /*   FIFO queue */

        }
        vTaskDelay(50);
    }
}
#endif


#include <stdint.h>
#include <stdbool.h>
#include "Types.h"

#include "include/FreeRTOS.h"
#include "include/task.h"
#include "inc/hw_gpio.h"
#include "driverlib/gpio.h"
#include "include/event_groups.h"
#include "inc/hw_memmap.h"
#include "include/queue.h"
#include "BUTTON/BUTTON.h"
#include "FSM/FSM.h"
#include "Maneger/Manager.h"
#include "SPI/spi.h"
#include "com_cfg.h"
#include "com.h"
#include "ROUTER/Router.h"
#include "UART/uart.h"
#include "driverlib/pin_map.h"

extern QueueHandle_t SPI_TRANSMIT_QUEE; /* SPI Transmit Queue */
extern QueueHandle_t UART_RECEIVE_QUEE; /* UART Receive Queue */

static uint8 PDU_TX[MAX_SIGNAL]; /* transmit buffer include PDU with (SDU & PCI) */

#define DATA_INIT_VALUE 0
#define INDEX_INIT_VALUE 0
#define MAIN_TX_PERIODICTY 50
#define PCI_BIT 6

/**********************************************/
/*the used MACROS*/
#define PRESSED 1
#define NOT_PRESSED 0
#define ZERO 0
#define ONE 1
#define FIVE 5
#define EIGHT 8
#define COMMAND_MASK 0xff
#define DATA_MASK 0x1f
#define TEN 10
#define TASK_TWO_DELAY 50
/**********************************************/
uint8_t Ignition_on = ZERO, count = ZERO;

/*Init_Task */
/* Parameters : void , void */
/* I/p : void , void  */
/* O/p : N/A */
/* Return : Void */
/* Function that initialize UART , SPI , BTN    */
void Init_Task(void *pvParameters)
{
    while (1)
    {
        /*UART Initialize*/
        UART_Init();

        /*SPI Initialize*/
        SPI_Init(ZERO);

        /*Button Initialize*/
        BUTTON_Init();

        vTaskSuspend(NULL);
    }
}

/*Allignment_Task */
/* Parameters :void *pvParameters */
/* I/p : void , void  */
/* O/p : N/A */
/* Return : Void */
/* Allignment_Task */
void Allignment_Task(void *pvParameters)
{

    uint8 Distance;
    uint8 Command;
    while (1)
    {
        if (ONE == Ignition_on)/*start the system */
        {
            /*Get the distance*/
            Distance = Get_Distance();
            /*Get the Command*/

                Command = FSM(Distance);
                   Distance /= EIGHT;

                   /* signal_arr[] will be initialized in these stage by using com_send_signal() fun */
                   com_send_signal(0, Command); /* command in first index */
                   com_send_signal(1, 1); /* ignition in second index */
                   com_send_signal(2, Distance); /* distance in third index */


        }
        vTaskDelay(200);
    }
}

/*Button_Task */
/* Parameters :void *pvParameters */
/* I/p : void , void  */
/* O/p : N/A */
/* Return : Void */
/* Function to check if BTN is pressed or not  */
void Button_Task(void *pvParameters)
{
    while (1)
    {
        if (Get_BUTTON() == PRESSED) /* Check if BTN pressed increment counter to detect the debouncing */
        {
            count++; /* increment count */
        }
        if (Get_BUTTON() == NOT_PRESSED)
        {
            count = ZERO;
        }

        if (count == TEN) /* check if counter equal 10 so the BTN is pressed */
        {
            Ignition_on = ONE; /* set Ignition flag */
            GPIOPinWrite(GPIO_PORTF_BASE, GPIO_PIN_2, GPIO_PIN_2);
            vTaskSuspend(NULL);
        }
        vTaskDelay(50);
    }
}

/*com_init */
/* Parameters : void , void */
/* I/p : void , void  */
/* O/p : N/A */
/* Return : Void */
/* Function that initialize COM module   */
void com_init(void)
{

}

/*concatenate */
/* Parameters : void , void */
/* I/p : void , void  */
/* O/p : N/A */
/* Return : Void */
/* Function that concatenate the signal with ID in 1 byte    */
static void concatenate(void)
{
    uint8 index;

    /* loop in sig_tx[] array and clear all element and assign by zero and assign bit 6,7 in PDU id */
    for (index = INDEX_INIT_VALUE; index < MAX_PDU; index++)
    {
        PDU_TX[index] = 0; /* clear all pdu_arr[]  element and assign it to zero */
        PDU_TX[index] = pdu_arr[index].PCI << PCI_BIT; /* assign bit 6,7 as PDU ID from pdu_array */
    }

    /* loop in loop in sig_tx[] array and assign the data in bit from 0 to 5 after concatenate using this algorithm */
    for (index = INDEX_INIT_VALUE; index < MAX_SIGNAL; index++)
    {
        PDU_TX[signal_arr[index].PDUID] |= signal_arr[index].DATA
                << signal_arr[index].START_BIT; /* concatenate */
    }
}

/*com_send_signal */
/* Parameters : uint8 , uint8 */
/* I/p : uint8 , uint8  */
/* O/p : N/A */
/* Return : Void */
/* Function that send signal 1 byte contain (SIGNAL , SIGNAL ID)  by COM module  */
void com_send_signal(uint8 id, uint8 data)
{
    signal_arr[id].DATA = data; /* access the signal_arr which include the structure of signals and access the data element */
}

/*com_receive_signal */
/* Parameters : uint8 */
/* I/p : uint8  */
/* O/p : N/A */
/* Return : uint8 */
/* Function that receive signal 1 byte contain (SIGNAL , SIGNAL ID)  by COM module  */
uint8 com_receive_signal(uint8 id)
{
    return 0;
}

/*ComMAIN_TX */
/* Parameters : void *pvParameters */
/* I/p : void */
/* O/p : N/A */
/* Return : Void */
/* Function that send signal 1 byte contain (SIGNAL , SIGNAL ID)  by COM module and control periodicty  */
void ComMAIN_TX(void *pvParameters)
{
    uint8 index = INDEX_INIT_VALUE; /*index for loop  in PDU_TX array */
    while (1)
    {
        //concatenate(); /* concatenate the 6 bit data and 2 bit PCI in 1 byte and add it to PDU_TX array */
        for (index = INDEX_INIT_VALUE; index < MAX_PDU; index++)
        {
            if (pdu_arr[PDU_TX[index] >> PCI_BIT].PERIDICTY == 0)
            {
                concatenate(); /* concatenate the 6 bit data and 2 bit PCI in 1 byte and add it to PDU_TX array */
                router_send(PDU_TX[index]); /* Routing based on configuration on ROUTER_CFG */
                pdu_arr[PDU_TX[index] >> PCI_BIT].PERIDICTY =
                        pdu_arr[PDU_TX[index] >> PCI_BIT].CNST_PERIODICTY;/*Assign periodicty with const periodicty */
            }
            else
            {
                pdu_arr[PDU_TX[index] >> PCI_BIT].PERIDICTY -=
                MAIN_TX_PERIODICTY;
            }

        }

        vTaskDelay(MAIN_TX_PERIODICTY);
    }
}

/*SPI_Task */
/* Parameters : void *pvParameters*/
/* I/p :  void  */
/* O/p : N/A */
/* Return : Void */
/* Function that send signal 1 byte SPI using QUEE   */
void SPI_Task(void *pvParameters)
{
    uint8 data;
    while (1)
    {
        if (ONE == Ignition_on) /* check if system is ON or OFF by this flag which set by BTN1 */
        {
            while (uxQueueMessagesWaiting(SPI_TRANSMIT_QUEE)) /* check if data assigned in spi queue */
            {
                xQueueReceive(SPI_TRANSMIT_QUEE, &data, 0);
                SPI_Transmit(data); /* Transmit data by SPI */
            }
        }
        vTaskDelay(250);

    }
}

/*UART0_Recv */
/* Parameters : void  , void   */
/* I/p : uint8 , void  */
/* O/p : N/A */
/* Return : uint8_t */
/* Function that receive data by UART0  */
uint8_t UART0_Recv(void)
{
    uint8_t data = DATA_INIT_VALUE;
    if (UARTCharsAvail(UART0_BASE))
    {
        data = UARTCharGetNonBlocking(UART0_BASE); /* get data from UART without Blocking*/
    }
    return data;
}

/*UartRecv_Task */
/* Parameters : void *pvParameters , void *pvParameters  */
/* I/p : uint8 , void  */
/* O/p : N/A */
/* Return : Void */
/* Function that receive data by UART0 and use the FIFO in QUEE which is first come first out   */
void UartRecv_Task(void *pvParameters)
{

    while (1)
    {
        uint8_t data = DATA_INIT_VALUE; /* variable to store the UART0 data */

        if (UARTCharsAvail(UART0_BASE)) /* check if there is any data avilable by UART0 */
        {
            data = UART0_Recv(); /* UART receive function */

            xQueueSendToBack(UART_RECEIVE_QUEE, &data, 10); /*   FIFO queue */

        }
        vTaskDelay(50);
    }
}


