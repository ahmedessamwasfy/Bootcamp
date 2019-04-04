#include <stdbool.h>
#include <stdint.h>
#include "inc/hw_can.h"
#include "inc/hw_ints.h"
#include "inc/hw_memmap.h"
#include "driverlib/can.h"
#include "driverlib/gpio.h"
#include "driverlib/interrupt.h"
#include "driverlib/pin_map.h"
#include "driverlib/sysctl.h"
#include "driverlib/uart.h"
#include "utils/uartstdio.h"
#include "utils/uartstdio.h"
#include "FreeRTOS.h"
#include "task.h"
#include "BTN.h"
#include "LED.h"

volatile uint8_t FLAG_ZERO_TX = 0;
volatile uint8_t FLAG_ONE_TX = 0;
volatile uint8_t FLAG_ZERO_RX = 0;
volatile uint8_t FLAG_ONE_RX = 0;
/*****************************************************************************
 A counter that keeps track of the number of times the TX interrupt has
 occurred, which should match the number of TX messages that were sent.
 *****************************************************************************/
volatile uint32_t g_ui32MsgCount = 0;

//*****************************************************************************
// A flag for the interrupt handler to indicate that a message was received.
//*****************************************************************************
volatile bool g_bRXFlag = 0;
volatile bool g_bRXFlag1 = 0;
volatile bool g_bRXFlag2 = 0;
volatile bool g_bRXFlag3 = 0;

//*****************************************************************************
// A flag to indicate that some reception error occurred.
//*****************************************************************************
volatile bool g_bErrFlag = 0;
/*****************************************************************************
 This function sets up UART0 to be used for a console to display information
 as the example is running.
 *****************************************************************************/
void vTaskCode3(void * pvParameters)/* init task for transmit ecu */
{

    while (1)
    {
#if defined(TARGET_IS_TM4C129_RA0) ||                                         \
    defined(TARGET_IS_TM4C129_RA1) ||                                         \
    defined(TARGET_IS_TM4C129_RA2)
        uint32_t ui32SysClock;
#endif

        /* Set the clocking to run directly from the external crystal/oscillator.
         TODO: The SYSCTL_XTAL_ value must be changed to match the value of the
         crystal used on your board. */

#if defined(TARGET_IS_TM4C129_RA0) ||                                         \
    defined(TARGET_IS_TM4C129_RA1) ||                                         \
    defined(TARGET_IS_TM4C129_RA2)
        ui32SysClock = SysCtlClockFreqSet((SYSCTL_XTAL_25MHZ |
                        SYSCTL_OSC_MAIN |
                        SYSCTL_USE_OSC)
                25000000);
#else
        SysCtlClockSet(SYSCTL_SYSDIV_1 | SYSCTL_USE_OSC | SYSCTL_OSC_MAIN |
        SYSCTL_XTAL_16MHZ);
#endif

        /* Set up the serial console to use for displaying messages.  This is
         just for this example program and is not needed for CAN operation.
         */
        /*
         Enable GPIO port A which is used for UART0 pins.
         TODO: change this to whichever GPIO port you are using.
         */
        SysCtlPeripheralEnable(SYSCTL_PERIPH_GPIOA);

        /* Configure the pin muxing for UART0 functions on port A0 and A1.
         This step is not necessary if your part does not support pin muxing.
         TODO: change this to select the port/pin you are using.
         */
        GPIOPinConfigure(GPIO_PA0_U0RX);
        GPIOPinConfigure(GPIO_PA1_U0TX);

        /* Enable UART0 so that we can configure the clock.*/

        SysCtlPeripheralEnable(SYSCTL_PERIPH_UART0);

        /* Use the internal 16MHz oscillator as the UART clock source.*/

        UARTClockSourceSet(UART0_BASE, UART_CLOCK_PIOSC);

        /* Select the alternate (UART) function for these pins.
         TODO: change this to select the port/pin you are using.
         */
        GPIOPinTypeUART(GPIO_PORTA_BASE, GPIO_PIN_0 | GPIO_PIN_1);

        /* Initialize the UART for console I/O.*/

        UARTStdioConfig(0, 115200, 16000000);

        /* For this example CAN0 is used with RX and TX pins on port B4 and B5.
         The actual port and pins used may be different on your part, consult
         the data sheet for more information.
         GPIO port B needs to be enabled so these pins can be used.
         TODO: change this to whichever GPIO port you are using
         */
        SysCtlPeripheralEnable(SYSCTL_PERIPH_GPIOB);

        /* Configure the GPIO pin muxing to select CAN0 functions for these pins.
         This step selects which alternate function is available for these pins.
         This is necessary if your part supports GPIO pin function muxing.
         Consult the data sheet to see which functions are allocated per pin.
         TODO: change this to select the port/pin you are using
         */
        GPIOPinConfigure(GPIO_PB4_CAN0RX);
        GPIOPinConfigure(GPIO_PB5_CAN0TX);

        /* Enable the alternate function on the GPIO pins.  The above step selects
         which alternate function is available.  This step actually enables the
         alternate function instead of GPIO for these pins.
         TODO: change this to match the port/pin you are using
         */
        GPIOPinTypeCAN(GPIO_PORTB_BASE, GPIO_PIN_4 | GPIO_PIN_5);

        // The GPIO port and pins have been set up for CAN.  The CAN peripheral
        // must be enabled.
        SysCtlPeripheralEnable(SYSCTL_PERIPH_CAN0);

        // Initialize the CAN controller
        CANInit(CAN0_BASE);

        // Set up the bit rate for the CAN bus.  This function sets up the CAN
        // bus timing for a nominal configuration.  You can achieve more control
        // over the CAN bus timing by using the function CANBitTimingSet() instead
        // of this one, if needed.
        // In this example, the CAN bus is set to 500 kHz.  In the function below,
        // the call to SysCtlClockGet() or ui32SysClock is used to determine the
        // clock rate that is used for clocking the CAN peripheral.  This can be
        // replaced with a  fixed value if you know the value of the system clock,
        // saving the extra function call.  For some parts, the CAN peripheral is
        // clocked by a fixed 8 MHz regardless of the system clock in which case
        // the call to SysCtlClockGet() or ui32SysClock should be replaced with
        // 8000000.  Consult the data sheet for more information about CAN
        // peripheral clocking.
#if defined(TARGET_IS_TM4C129_RA0) ||                                         \
    defined(TARGET_IS_TM4C129_RA1) ||                                         \
    defined(TARGET_IS_TM4C129_RA2)
        CANBitRateSet(CAN0_BASE, ui32SysClock, 500000);
#else
        CANBitRateSet(CAN0_BASE, SysCtlClockGet(), 500000);
#endif

        //
        // Enable interrupts on the CAN peripheral.  This example uses static
        // allocation of interrupt handlers which means the name of the handler
        // is in the vector table of startup code.  If you want to use dynamic
        // allocation of the vector table, then you must also call CANIntRegister()
        // here.
        //
        // CANIntRegister(CAN0_BASE, CANIntHandler); // if using dynamic vectors
        //
        CANIntEnable(CAN0_BASE,
        CAN_INT_MASTER | CAN_INT_ERROR | CAN_INT_STATUS);

        /* Enable the CAN interrupt on the processor (NVIC). */
        IntEnable(INT_CAN0);

        /*Enable the CAN for operation.*/
        CANEnable(CAN0_BASE);
        LEDTaskInit();
        Btns_Init();
        vTaskSuspend(NULL); /*susspend for init tasks */

    }
}

//*****************************************************************************
//
// This function provides a 1 second delay using a simple polling method.
//
//*****************************************************************************
void SimpleDelay(void)
{
    //
    // Delay cycles for 1 second
    //
    SysCtlDelay(16000000 / 3);
}
#if 0
//*****************************************************************************
//
// This function is the interrupt handler for the CAN peripheral.  It checks
// for the cause of the interrupt, and maintains a count of all messages that
// have been received.
//
//*****************************************************************************

void
CANIntHandler(void)
{
    uint32_t ui32Status;

    //
    // Read the CAN interrupt status to find the cause of the interrupt
    //
    ui32Status = CANIntStatus(CAN0_BASE, CAN_INT_STS_CAUSE);

    //
    // If the cause is a controller status interrupt, then get the status
    //
    if(ui32Status == CAN_INT_INTID_STATUS)
    {
        //
        // Read the controller status.  This will return a field of status
        // error bits that can indicate various errors.  Error processing
        // is not done in this example for simplicity.  Refer to the
        // API documentation for details about the error status bits.
        // The act of reading this status will clear the interrupt.
        //
        ui32Status = CANStatusGet(CAN0_BASE, CAN_STS_CONTROL);

        //
        // Set a flag to indicate some errors may have occurred.
        //
        g_bErrFlag = 1;
    }

    //
    // Check if the cause is message object 1, which what we are using for
    // receiving messages.
    //
    else if(ui32Status == 1)
    {
        //
        // Getting to this point means that the RX interrupt occurred on
        // message object 1, and the message reception is complete.  Clear the
        // message object interrupt.
        //
        CANIntClear(CAN0_BASE, 1);

        //
        // Increment a counter to keep track of how many messages have been
        // received.  In a real application this could be used to set flags to
        // indicate when a message is received.
        //
        g_ui32MsgCount++;

        //
        // Set flag to indicate received message is pending.
        //
        g_bRXFlag = 1;

        //
        // Since a message was received, clear any error flags.
        //
        g_bErrFlag = 0;
    }

    //
    // Otherwise, something unexpected caused the interrupt.  This should
    // never happen.
    //
    else
    {
        //
        // Spurious interrupt handling can go here.
        //
    }
}
#endif

void CANIntHandler(void)
{
    uint32_t ui32Status;

    //
    // Read the CAN interrupt status to find the cause of the interrupt
    //
    ui32Status = CANIntStatus(CAN0_BASE, CAN_INT_STS_CAUSE);

    //
    // If the cause is a controller status interrupt, then get the status
    //
    if (ui32Status == CAN_INT_INTID_STATUS)
    {
        //
        // Read the controller status.  This will return a field of status
        // error bits that can indicate various errors.  Error processing
        // is not done in this example for simplicity.  Refer to the
        // API documentation for details about the error status bits.
        // The act of reading this status will clear the interrupt.
        //
        ui32Status = CANStatusGet(CAN0_BASE, CAN_STS_CONTROL);

        //
        // Set a flag to indicate some errors may have occurred.
        //
        g_bErrFlag = 1;
    }

    //
    // Check if the cause is message object 1, which what we are using for
    // receiving messages.
    //
    else if (ui32Status == 1)
    {
        //
        // Getting to this point means that the RX interrupt occurred on
        // message object 1, and the message reception is complete.  Clear the
        // message object interrupt.
        //
        CANIntClear(CAN0_BASE, 1);

        //
        // Increment a counter to keep track of how many messages have been
        // received.  In a real application this could be used to set flags to
        // indicate when a message is received.
        //
        g_ui32MsgCount++;

        //
        // Set flag to indicate received message is pending.
        //
        g_bRXFlag1 = 1;

        //
        // Since a message was received, clear any error flags.
        //
        g_bErrFlag = 0;
    }

    //
    // Otherwise, something unexpected caused the interrupt.  This should
    // never happen.
    //

    else if (ui32Status == 2)
    {
        CANIntClear(CAN0_BASE, 2);
        g_ui32MsgCount++;
        g_bRXFlag2 = 1;
        g_bErrFlag = 0;
    }

//
// Check if the cause is message object 3.
//
    else if (ui32Status == 3)
    {
        CANIntClear(CAN0_BASE, 3);
        g_ui32MsgCount++;
        g_bRXFlag3 = 1;
        g_bErrFlag = 0;
    }

//
// Otherwise, something unexpected caused the interrupt.  This should
// never happen.
//
    else
    {
        //
        // Spurious interrupt handling can go here.
        //
    }
}

//*****************************************************************************
//
// Configure the CAN and enter a loop to transmit periodic CAN messages.
//
//*****************************************************************************
void vTaskCode_startup(void * pvParameters)/*startup TASK*/
{
    volatile uint8_t flag;
    /************REVERS MODE *************/
    tCANMsgObject sCANMessage_startup_revers;
    uint32_t ui32MsgData_startup_revers;
    uint8_t *pui8MsgData_startup_revers;/* pointer to check data */

    /*************NORMAL MODE *************/
    tCANMsgObject sCANMessage_startup_normal;
    uint32_t ui32MsgData_startup_normal;
    uint8_t *pui8MsgData_startup_normal;/* pointer to check data */

    //
    // Initialize the message object that will be used for sending CAN
    // messages.  The message will be 4 bytes that will contain an incrementing
    // value.  Initially it will be set to 0.
    //
    /********************normal mode structure *************/

    ui32MsgData_startup_normal = 4; /*data = 4 normal mode*/
    pui8MsgData_startup_normal = (uint8_t *) &ui32MsgData_startup_normal;/*make pointer points to flag to check sys. is normal or revers */
    sCANMessage_startup_normal.ui32MsgID = 2; /* ID FOR NODE 2 */
    sCANMessage_startup_normal.ui32MsgIDMask = 0;
    sCANMessage_startup_normal.ui32Flags = MSG_OBJ_TX_INT_ENABLE;
    sCANMessage_startup_normal.ui32MsgLen = sizeof(pui8MsgData_startup_normal);
    sCANMessage_startup_normal.pui8MsgData = pui8MsgData_startup_normal;

    /********************revers mode structure *************/
    ui32MsgData_startup_revers = 6;/*data = 6 revers mode */
    pui8MsgData_startup_revers = (uint8_t *) &ui32MsgData_startup_revers;/*make pointer points to flag to check sys. is normal or revers */
    sCANMessage_startup_revers.ui32MsgID = 3;/* ID FOR NODE 3 */
    sCANMessage_startup_revers.ui32MsgIDMask = 0;
    sCANMessage_startup_revers.ui32Flags = MSG_OBJ_TX_INT_ENABLE;
    sCANMessage_startup_revers.ui32MsgLen = sizeof(pui8MsgData_startup_revers);
    sCANMessage_startup_revers.pui8MsgData = pui8MsgData_startup_revers;
    //
    // Enter loop to send messages.  A new message will be sent once per
    // second.  The 4 bytes of message content will be treated as an uint32_t
    // and incremented by one each time.
    //
    //
    while (1)
    {
        //
        // Print a message to the console showing the message count and the
        // contents of the message being sent.
        //
        //UARTprintf("Sending msg: 0x%02X %02X %02X %02X", pui8MsgData[0],
        //        pui8MsgData[1], pui8MsgData[2], pui8MsgData[3]);
        // Send the CAN message using object number 1 (not the same thing as
        // CAN ID, which is also 1 in this example).  This function will cause
        // the message to be transmitted right away.
        if (!GPIOPinRead(GPIO_PORTF_BASE, GPIO_PIN_4))/* if btn is pressed send flag = 4 revers mode */
        {
            CANMessageSet(CAN0_BASE, 1, &sCANMessage_startup_revers,
                          MSG_OBJ_TYPE_TX);/*REVERS MODE */
        }
        else
        {
            CANMessageSet(CAN0_BASE, 1, &sCANMessage_startup_normal,
                          MSG_OBJ_TYPE_TX);/* NORMAL MODE */
        }
        // Now wait 1 second before continuing

        SimpleDelay();

        // Check the error flag to see if errors occurred
        if (g_bErrFlag)
        {
            UARTprintf(" error - cable connected?\n");
        }
        else
        {
            // If no errors then print the count of message sent
            UARTprintf(" ID = %u\n", sCANMessage_startup_revers.ui32MsgID);
        }

        // Increment the value in the message data.
        //ui32MsgData++;
        vTaskSuspend(NULL); /*susspend for STARAT UP tasks */
    }

}
#if 0
//*****************************************************************************
//
// Configure the CAN and enter a loop to transmit periodic CAN messages.
//
//*****************************************************************************
void vTaskCode5(void * pvParameters)
{
    tCANMsgObject sCANMessage;
    uint32_t ui32MsgData;
    uint8_t *pui8MsgData;/* pointer to check data */

    //
    // Initialize the message object that will be used for sending CAN
    // messages.  The message will be 4 bytes that will contain an incrementing
    // value.  Initially it will be set to 0.
    //
    ui32MsgData = 3;
    pui8MsgData = (uint8_t *) &ui32MsgData;
    sCANMessage.ui32MsgID = 2;
    sCANMessage.ui32MsgIDMask = 0;
    sCANMessage.ui32Flags = MSG_OBJ_TX_INT_ENABLE;
    sCANMessage.ui32MsgLen = sizeof(pui8MsgData);
    sCANMessage.pui8MsgData = pui8MsgData;

    //
    // Enter loop to send messages.  A new message will be sent once per
    // second.  The 4 bytes of message content will be treated as an uint32_t
    // and incremented by one each time.
    //
    //
    while (1)
    {
        //
        // Print a message to the console showing the message count and the
        // contents of the message being sent.
        //
        UARTprintf("Sending msg: 0x%02X %02X %02X %02X", pui8MsgData[0],
                pui8MsgData[1], pui8MsgData[2], pui8MsgData[3]);
        // Send the CAN message using object number 1 (not the same thing as
        // CAN ID, which is also 1 in this example).  This function will cause
        // the message to be transmitted right away.

        CANMessageSet(CAN0_BASE, 1, &sCANMessage, MSG_OBJ_TYPE_TX);

        // Now wait 1 second before continuing

        SimpleDelay();

        // Check the error flag to see if errors occurred
        if (g_bErrFlag)
        {
            UARTprintf(" error - cable connected?\n");
        }
        else
        {
            // If no errors then print the count of message sent
            UARTprintf(" total count = %u\n", g_ui32MsgCount);
        }

        // Increment the value in the message data.
        //ui32MsgData++;
        vTaskDelay(20);
    }

}

//*****************************************************************************
//
// Configure the CAN and enter a loop to receive CAN messages.
//
//*****************************************************************************
void vTaskCode4(void * pvParameters)/*RECIVE TASK*/
{
    tCANMsgObject sCANMessage;
    uint8_t pui8MsgData[8];
//
// Initialize a message object to be used for receiving CAN messages with
// any CAN ID.  In order to receive any CAN ID, the ID and mask must both
// be set to 0, and the ID filter enabled.
//
    sCANMessage.ui32MsgID = 0;
    sCANMessage.ui32MsgIDMask = 0;
    sCANMessage.ui32Flags = MSG_OBJ_RX_INT_ENABLE | MSG_OBJ_USE_ID_FILTER;
    sCANMessage.ui32MsgLen = 8;

//
// Now load the message object into the CAN peripheral.  Once loaded the
// CAN will receive any message on the bus, and an interrupt will occur.
// Use message object 1 for receiving messages (this is not the same as
// the CAN ID which can be any value in this example).
//
    CANMessageSet(CAN0_BASE, 2, &sCANMessage, MSG_OBJ_TYPE_RX);

//
// Enter loop to process received messages.  This loop just checks a flag
// that is set by the interrupt handler, and if set it reads out the
// message and displays the contents.  This is not a robust method for
// processing incoming CAN data and can only handle one messages at a time.
// If many messages are being received close together, then some messages
// may be dropped.  In a real application, some other method should be used
// for queuing received messages in a way to ensure they are not lost.  You
// can also make use of CAN FIFO mode which will allow messages to be
// buffered before they are processed.
//
    while (1)
    {
        unsigned int uIdx;

        //
        // If the flag is set, that means that the RX interrupt occurred and
        // there is a message ready to be read from the CAN
        //
        if (g_bRXFlag2)
        {
            //
            // Reuse the same message object that was used earlier to configure
            // the CAN for receiving messages.  A buffer for storing the
            // received data must also be provided, so set the buffer pointer
            // within the message object.
            //
            sCANMessage.pui8MsgData = pui8MsgData;

            //
            // Read the message from the CAN.  Message object number 1 is used
            // (which is not the same thing as CAN ID).  The interrupt clearing
            // flag is not set because this interrupt was already cleared in
            // the interrupt handler.
            //
            CANMessageGet(CAN0_BASE, 2, &sCANMessage, 0);
            if (sCANMessage.ui32MsgID == 2)
            {
                ON_LED1();
            }
            else if (sCANMessage.ui32MsgID == 4)
            {
                OFF_LED1();
            }
            //
            // Clear the pending message flag so that the interrupt handler can
            // set it again when the next message arrives.
            //
            g_bRXFlag = 0;

            //
            // Check to see if there is an indication that some messages were
            // lost.
            //
            if (sCANMessage.ui32Flags & MSG_OBJ_DATA_LOST)
            {
                UARTprintf("CAN message loss detected\n");
            }

            //
            // Print out the contents of the message that was received.
            //
            UARTprintf("Msg ID=0x%08X len=%u data=0x", sCANMessage.ui32MsgID,
                    sCANMessage.ui32MsgLen);
            for (uIdx = 0; uIdx < sCANMessage.ui32MsgLen; uIdx++)
            {
                UARTprintf("%02X ", pui8MsgData[uIdx]);
            }
            UARTprintf("total count=%u\n", g_ui32MsgCount);
            if (*pui8MsgData == 3)
            {
                ON_LED1();
            }
        }
        vTaskDelay(10);

    }
}
#endif

//*****************************************************************************
//
// Configure the CAN and enter a loop to transmit periodic CAN messages.
//
//*****************************************************************************
void vTaskCode_NODE_ZERO_TX(void * pvParameters)
{
    tCANMsgObject sCANMessage;
    uint32_t ui32MsgData;
    uint8_t *pui8MsgData;/* pointer to check data */

    //
    // Initialize the message object that will be used for sending CAN
    // messages.  The message will be 4 bytes that will contain an incrementing
    // value.  Initially it will be set to 0.
    //
    ui32MsgData = 1; /* DATA = 1 LED ON */
    pui8MsgData = (uint8_t *) &ui32MsgData;
    sCANMessage.ui32MsgID = 1; /* NODE 1 ID */
    sCANMessage.ui32MsgIDMask = 0;
    sCANMessage.ui32Flags = MSG_OBJ_TX_INT_ENABLE;
    sCANMessage.ui32MsgLen = sizeof(pui8MsgData);
    sCANMessage.pui8MsgData = pui8MsgData;

    //
    // Enter loop to send messages.  A new message will be sent once per
    // second.  The 4 bytes of message content will be treated as an uint32_t
    // and incremented by one each time.
    //
    //
    while (1)
    {
        //
        // Print a message to the console showing the message count and the
        // contents of the message being sent.
        //
        //UARTprintf("Sending msg: 0x%02X %02X %02X %02X", pui8MsgData[0],
        //         pui8MsgData[1], pui8MsgData[2], pui8MsgData[3]);
        // Send the CAN message using object number 1 (not the same thing as
        // CAN ID, which is also 1 in this example).  This function will cause
        // the message to be transmitted right away.
        if (FLAG_ZERO_TX == 1)
        {
            CANMessageSet(CAN0_BASE, 1, &sCANMessage, MSG_OBJ_TYPE_TX);
        }
        // Now wait 1 second before continuing

        SimpleDelay();

        // Check the error flag to see if errors occurred
        if (g_bErrFlag)
        {
            UARTprintf(" error - cable connected?\n");
        }
        //else
        //{
        // If no errors then print the count of message sent
        //  UARTprintf(" ID = %u\n", sCANMessage.ui32MsgID);
        //}

        // Increment the value in the message data.
        //ui32MsgData++;
        vTaskDelay(150);
    }

}

//*****************************************************************************
//
// Configure the CAN and enter a loop to transmit periodic CAN messages.
//
//*****************************************************************************
void vTaskCode_NODE_ONE_TX(void * pvParameters)
{
    tCANMsgObject sCANMessage;
    uint32_t ui32MsgData;
    uint8_t *pui8MsgData;/* pointer to check data */

    //
    // Initialize the message object that will be used for sending CAN
    // messages.  The message will be 4 bytes that will contain an incrementing
    // value.  Initially it will be set to 0.
    //
    ui32MsgData = 1; /* LED ON */
    pui8MsgData = (uint8_t *) &ui32MsgData;
    sCANMessage.ui32MsgID = 0; /* NODE 0 ID */
    sCANMessage.ui32MsgIDMask = 0;
    sCANMessage.ui32Flags = MSG_OBJ_TX_INT_ENABLE;
    sCANMessage.ui32MsgLen = sizeof(pui8MsgData);
    sCANMessage.pui8MsgData = pui8MsgData;

    //
    // Enter loop to send messages.  A new message will be sent once per
    // second.  The 4 bytes of message content will be treated as an uint32_t
    // and incremented by one each time.
    //
    //
    while (1)
    {
        //
        // Print a message to the console showing the message count and the
        // contents of the message being sent.
        //
        //UARTprintf("Sending msg: 0x%02X %02X %02X %02X", pui8MsgData[0],
        //         pui8MsgData[1], pui8MsgData[2], pui8MsgData[3]);
        // Send the CAN message using object number 1 (not the same thing as
        // CAN ID, which is also 1 in this example).  This function will cause
        // the message to be transmitted right away.
        if (FLAG_ONE_TX == 1)
        {
            CANMessageSet(CAN0_BASE, 1, &sCANMessage, MSG_OBJ_TYPE_TX);

        }
        // Now wait 1 second before continuing

        SimpleDelay();

        // Check the error flag to see if errors occurred
        if (g_bErrFlag)
        {
            UARTprintf(" error - cable connected?\n");
        }
        //else
        //{
        // If no errors then print the count of message sent
        //  UARTprintf(" ID = %u\n", sCANMessage.ui32MsgID);
        //}

        // Increment the value in the message data.
        //ui32MsgData++;
        vTaskDelay(150);
    }

}

//*****************************************************************************
//
// Configure the CAN and enter a loop to receive CAN messages.
//
//*****************************************************************************
void vTaskCode_NODE_ZERO_RX(void * pvParameters)/*RECIVE TASK*/
{
    tCANMsgObject sCANMessage;
    uint8_t pui8MsgData[8];
//
// Initialize a message object to be used for receiving CAN messages with
// any CAN ID.  In order to receive any CAN ID, the ID and mask must both
// be set to 0, and the ID filter enabled.
//
    sCANMessage.ui32MsgID = 0;
    sCANMessage.ui32MsgIDMask = 0;
    sCANMessage.ui32Flags = MSG_OBJ_RX_INT_ENABLE | MSG_OBJ_USE_ID_FILTER;
    sCANMessage.ui32MsgLen = 8;

//
// Now load the message object into the CAN peripheral.  Once loaded the
// CAN will receive any message on the bus, and an interrupt will occur.
// Use message object 1 for receiving messages (this is not the same as
// the CAN ID which can be any value in this example).
//
    CANMessageSet(CAN0_BASE, 2, &sCANMessage, MSG_OBJ_TYPE_RX);

//
// Enter loop to process received messages.  This loop just checks a flag
// that is set by the interrupt handler, and if set it reads out the
// message and displays the contents.  This is not a robust method for
// processing incoming CAN data and can only handle one messages at a time.
// If many messages are being received close together, then some messages
// may be dropped.  In a real application, some other method should be used
// for queuing received messages in a way to ensure they are not lost.  You
// can also make use of CAN FIFO mode which will allow messages to be
// buffered before they are processed.
//
    while (1)
    {
        unsigned int uIdx;

        //
        // If the flag is set, that means that the RX interrupt occurred and
        // there is a message ready to be read from the CAN
        //
        if (g_bRXFlag2)
        {
            //
            // Reuse the same message object that was used earlier to configure
            // the CAN for receiving messages.  A buffer for storing the
            // received data must also be provided, so set the buffer pointer
            // within the message object.
            //
            sCANMessage.pui8MsgData = pui8MsgData;

            //
            // Read the message from the CAN.  Message object number 1 is used
            // (which is not the same thing as CAN ID).  The interrupt clearing
            // flag is not set because this interrupt was already cleared in
            // the interrupt handler.
            //
            CANMessageGet(CAN0_BASE, 2, &sCANMessage, 0);
            if (sCANMessage.ui32MsgID == 0) /* NODE 0 RX */
            {
                if (*sCANMessage.pui8MsgData == 1)/* LED ON */
                {
                    UARTprintf(" data=%d", *sCANMessage.pui8MsgData);
                    ON_LED1();
                    SimpleDelay();
                    OFF_LED1();
                    FLAG_ONE_TX = 1;
                }
                else if (*sCANMessage.pui8MsgData == 0)
                {
                    OFF_LED1();
                }
            }
            //
            // Clear the pending message flag so that the interrupt handler can
            // set it again when the next message arrives.
            //
            g_bRXFlag = 0;

            //
            // Check to see if there is an indication that some messages were
            // lost.
            //
            if (sCANMessage.ui32Flags & MSG_OBJ_DATA_LOST)
            {
                UARTprintf("CAN message loss detected\n");
            }

            //
            // Print out the contents of the message that was received.
            //
            //UARTprintf("Msg ID=0x%08X len=%u data=0x", sCANMessage.ui32MsgID,
            //           sCANMessage.ui32MsgLen);
            //for (uIdx = 0; uIdx < sCANMessage.ui32MsgLen; uIdx++)
            //{
            //   UARTprintf("%02X ", pui8MsgData[uIdx]);
            //}
            //UARTprintf("total count=%u\n", g_ui32MsgCount);
        }
        vTaskDelay(50);
    }
}
//*****************************************************************************
//
// Configure the CAN and enter a loop to receive CAN messages.
//
//*****************************************************************************
void vTaskCode_NODE_ONE_RX(void * pvParameters)/*RECIVE TASK*/
{
    tCANMsgObject sCANMessage;
    uint8_t pui8MsgData[8];
//
// Initialize a message object to be used for receiving CAN messages with
// any CAN ID.  In order to receive any CAN ID, the ID and mask must both
// be set to 0, and the ID filter enabled.
//
    sCANMessage.ui32MsgID = 0;
    sCANMessage.ui32MsgIDMask = 0;
    sCANMessage.ui32Flags = MSG_OBJ_RX_INT_ENABLE | MSG_OBJ_USE_ID_FILTER;
    sCANMessage.ui32MsgLen = 8;

//
// Now load the message object into the CAN peripheral.  Once loaded the
// CAN will receive any message on the bus, and an interrupt will occur.
// Use message object 1 for receiving messages (this is not the same as
// the CAN ID which can be any value in this example).
//
    CANMessageSet(CAN0_BASE, 2, &sCANMessage, MSG_OBJ_TYPE_RX);

//
// Enter loop to process received messages.  This loop just checks a flag
// that is set by the interrupt handler, and if set it reads out the
// message and displays the contents.  This is not a robust method for
// processing incoming CAN data and can only handle one messages at a time.
// If many messages are being received close together, then some messages
// may be dropped.  In a real application, some other method should be used
// for queuing received messages in a way to ensure they are not lost.  You
// can also make use of CAN FIFO mode which will allow messages to be
// buffered before they are processed.
//
    while (1)
    {
        unsigned int uIdx;

        //
        // If the flag is set, that means that the RX interrupt occurred and
        // there is a message ready to be read from the CAN
        //
        if (g_bRXFlag2)
        {
            //
            // Reuse the same message object that was used earlier to configure
            // the CAN for receiving messages.  A buffer for storing the
            // received data must also be provided, so set the buffer pointer
            // within the message object.
            //
            sCANMessage.pui8MsgData = pui8MsgData;

            //
            // Read the message from the CAN.  Message object number 1 is used
            // (which is not the same thing as CAN ID).  The interrupt clearing
            // flag is not set because this interrupt was already cleared in
            // the interrupt handler.
            //
            CANMessageGet(CAN0_BASE, 2, &sCANMessage, 0);
            if (sCANMessage.ui32MsgID == 1) /* NODE 1 RX */
            {
                if (*sCANMessage.pui8MsgData == 1)/* LED ON */
                {
                    ON_LED1();
                    SimpleDelay();
                    OFF_LED1();
                    FLAG_ZERO_TX = 1;

                }
                else if (*sCANMessage.pui8MsgData == 0)
                {
                    OFF_LED1();
                }
            }
            //
            // Clear the pending message flag so that the interrupt handler can
            // set it again when the next message arrives.
            //
            g_bRXFlag = 0;

            //
            // Check to see if there is an indication that some messages were
            // lost.
            //
            if (sCANMessage.ui32Flags & MSG_OBJ_DATA_LOST)
            {
                UARTprintf("CAN message loss detected\n");
            }

            //
            // Print out the contents of the message that was received.
            //
            //UARTprintf("Msg ID=0x%08X len=%u data=0x", sCANMessage.ui32MsgID,
            //         sCANMessage.ui32MsgLen);
            //for (uIdx = 0; uIdx < sCANMessage.ui32MsgLen; uIdx++)
            //{
            //  UARTprintf("%02X ", pui8MsgData[uIdx]);
            //}
            //UARTprintf("total count=%u\n", g_ui32MsgCount);

        }
        vTaskDelay(50);
    }
}


//*****************************************************************************
//
// Configure the CAN and enter a loop to transmit periodic CAN messages.
//
//*****************************************************************************
void vTaskCode_NODE_ZERO_START(void * pvParameters)
{
    tCANMsgObject sCANMessage;
    uint32_t ui32MsgData;
    uint8_t *pui8MsgData;/* pointer to check data */

    //
    // Initialize the message object that will be used for sending CAN
    // messages.  The message will be 4 bytes that will contain an incrementing
    // value.  Initially it will be set to 0.
    //
    ui32MsgData = 1; /* DATA = 1 LED ON */
    pui8MsgData = (uint8_t *) &ui32MsgData;
    sCANMessage.ui32MsgID = 1; /* NODE 1 ID */
    sCANMessage.ui32MsgIDMask = 0;
    sCANMessage.ui32Flags = MSG_OBJ_TX_INT_ENABLE;
    sCANMessage.ui32MsgLen = sizeof(pui8MsgData);
    sCANMessage.pui8MsgData = pui8MsgData;

    //
    // Enter loop to send messages.  A new message will be sent once per
    // second.  The 4 bytes of message content will be treated as an uint32_t
    // and incremented by one each time.
    //
    //
    while (1)
    {
        //
        // Print a message to the console showing the message count and the
        // contents of the message being sent.
        //
        //UARTprintf("Sending msg: 0x%02X %02X %02X %02X", pui8MsgData[0],
        //         pui8MsgData[1], pui8MsgData[2], pui8MsgData[3]);
        // Send the CAN message using object number 1 (not the same thing as
        // CAN ID, which is also 1 in this example).  This function will cause
        // the message to be transmitted right away.

            CANMessageSet(CAN0_BASE, 1, &sCANMessage, MSG_OBJ_TYPE_TX);

        // Now wait 1 second before continuing

        SimpleDelay();

        // Check the error flag to see if errors occurred
        if (g_bErrFlag)
        {
            UARTprintf(" error - cable connected?\n");
        }
        //else
        //{
        // If no errors then print the count of message sent
        //  UARTprintf(" ID = %u\n", sCANMessage.ui32MsgID);
        //}

        // Increment the value in the message data.
        //ui32MsgData++;
        vTaskSuspend(NULL); /*susspend for init tasks */
    }

}
