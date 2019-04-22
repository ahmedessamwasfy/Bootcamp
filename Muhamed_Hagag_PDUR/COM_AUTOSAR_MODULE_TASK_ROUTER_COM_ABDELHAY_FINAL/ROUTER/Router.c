#include <stdint.h>
#include <stdbool.h>
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
#include "COM_MODULE_AUTOSAR/com_cfg.h"
#include "COM_MODULE_AUTOSAR/com_cfg.h"
#include "Router.h"
#include "Router.h"
#include "Router_cfg.h"

extern QueueHandle_t UART_RECEIVE_QUEE; /* UART Receive queue by UART */
extern QueueHandle_t SPI_TRANSMIT_QUEE; /* SPI Transmit queue by SPI */

/*router_send */
/* Parameters : uint8 */
/* I/p : uint8   */
/* O/p : N/A */
/* Return : Void */
/* router send and select channel   */
void router_send(uint8_t PDU)
{
    /* switch on PDU to know which channel and which comm protocal will be used  depend on configuratiuon in ROUTER CFG */
    switch (protocal_arr[(PDU >> PCI_BIT)])
    {
    case UART:
        xQueueSendToBack(UART_RECEIVE_QUEE, &PDU, 10); /* send to UART queue*/
        break;

    case SPI:
        xQueueSendToBack(SPI_TRANSMIT_QUEE, &PDU, 10); /* send to SPI queue*/
        break;

    default:
        break;
    }

}

/*router_receive */
/* Parameters : void */
/* I/p : void  */
/* O/p : N/A */
/* Return : Void */
/* router receive and select channel   */
uint8 router_receive(void)
{
    return 0 ;
}

