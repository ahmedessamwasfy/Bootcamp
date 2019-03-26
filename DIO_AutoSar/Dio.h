#ifndef DIO_H_
#define DIO_H_

#include "Dio_Cfg.h"
#include "Std_Types.h"
#include "internal.h"
/*******************************************************************************
 *                              Module Data Types                              *
 *******************************************************************************/

/*Numeric ID of a DIO channel..*/
typedef uint8 Dio_ChannelType;

/*Numeric ID of a DIO port*/
typedef uint8 Dio_PortType; /*number of ports */

/*These are the possible levels a DIO channel can have (input or output)*/
typedef uint8 Dio_LevelType;/*STTD_HIGH or STD_LOW */

/*If the µC owns ports of different port widths (e.g. 4, 8,16...Bit) Dio_PortLevelType
 inherits the size of the largest port.*/
typedef uint8 Dio_PortLevelType;

/*Type for the definition of a channel group, which consists of several adjoining
 channels within a port*/
typedef struct
{
    uint8 mask;
    uint8 offset;
    Dio_PortType port;
} Dio_ChannelGroupType;

/******************************************************************************
 *                      API Service Id Macros                                 *
 ******************************************************************************/

/* the DIO read channel service id */
#define DIO_READ_CHANNEL_SID          (uint8)0x00

/* the DIO write channel service id */
#define DIO_WRITE_CHANNEL_SID         (uint8)0x01

/* the Dio Read Port service id */
#define DIO_READ_PORT_SID           (uint8)0x02

/* the Dio Write Port service id */
#define DIO_WRITE_PORT_SID             (uint8)0x03

/* the Dio Read Channel Group service id */
#define DIO_READ_CHANNEL_GROUP_SID     (uint8)0x04

/*  the DIO write Channel Group Service ID */
#define DIO_WRITE_CHANNEL_GROUP_SID    (uint8)0x05

/* the DIO flip Channel Service ID */
#define DIO_FLIP_CHANNEL_SID           (uint8)0x11

/* theDIO GetVersionInfo Service ID */
#define DIO_GET_VERSION_INFO_SID       (uint8)0x12

/*******************************************************************************
 *                      Function Prototypes                                    *
 *******************************************************************************/

/************************************************************************************
 * Service Name: Dio_ReadChannel
 * Service ID[hex]: 0x00
 * Sync/Async: Synchronous
 * Reentrancy: Reentrant
 * Parameters (in): ChannelId - ID of DIO channel.
 * Parameters (inout): None
 * Parameters (out): None
 * Return value: Dio_LevelType
 * Description: Function to return the value of the specified DIO channel.
 ************************************************************************************/
extern FUNC(Dio_LevelType,memclass) Dio_ReadChannel(
        VAR(Dio_ChannelType,memclass) ChannelId);

/************************************************************************************
 * Service Name: Dio_WriteChannel
 * Service ID[hex]: 0x01
 * Sync/Async: Synchronous
 * Reentrancy: Reentrant
 * Parameters (in): ChannelId - ID of DIO channel.
 *                  Level - Value to be written.
 * Parameters (inout): None
 * Parameters (out): None
 * Return value: None
 * Description: Function to set a level of a channel.
 ************************************************************************************/
extern FUNC(void,memclass) Dio_WriteChannel(
        VAR(Dio_ChannelType,memclass) ChannelId,
        VAR(Dio_LevelType,memclass) Level);

/************************************************************************************
 * Service Name: Dio_ReadPort
 * Service ID[hex]: 0x02
 * Sync/Async: Synchronous
 * Reentrancy: Reentrant
 * Parameters (in): PortId - ID of DIO Port.
 * Parameters (inout): None
 * Parameters (out): None
 * Return value: Dio_PortLevelType
 * Description: Returns the level of all channels of that port.
 ************************************************************************************/
extern FUNC(Dio_PortLevelType,memclass) Dio_ReadPort(
        VAR(Dio_PortType,memclass) PortId);

/************************************************************************************
 * Service Name: Dio_WritePort
 * Service ID[hex]: 0x03
 * Sync/Async: Synchronous
 * Reentrancy: Reentrant
 * Parameters (in): PortId - ID of DIO Port.
 *                  Level  - Value to be written
 * Parameters (inout): None
 * Parameters (out): None
 * Return value: None
 * Description: Service to set a value of the port.
 ************************************************************************************/
extern FUNC(void,memclass) Dio_WritePort(
        VAR(Dio_PortType ,memclass) PortId,
        VAR(Dio_PortLevelType,memclass) Level);

/************************************************************************************
 * Service Name: Dio_ReadChannelGroup
 * Service ID[hex]: 0x04
 * Sync/Async: Synchronous
 * Reentrancy: Reentrant
 * Parameters (in): ChannelGroupIdPtr - Pointer to ChannelGroup.
 * Parameters (inout): None
 * Parameters (out): None
 * Return value: Dio_PortLevelType
 * Description: This Service reads a subset of the adjoining bits of a port.
 ************************************************************************************/
extern FUNC(Dio_PortLevelType,memclass) Dio_ReadChannelGroup(
        P2CONST(Dio_ChannelGroupType,memclass,ptrclass)ChannelGroupIdPtr );


/************************************************************************************
 * Service Name: Dio_WriteChannelGroup
 * Service ID[hex]: 0x05
 * Sync/Async: Synchronous
 * Reentrancy: Reentrant
 * Parameters (in): ChannelGroupIdPtr - Pointer to ChannelGroup.
 *                  Level             - Value to be written
 * Parameters (inout): None
 * Parameters (out):   None
 * Return value:       None
 * Description: Service to set a subset of the adjoining bits of a port to a specified level.
 ************************************************************************************/
extern FUNC(void,DIO_MEM_CLASS) Dio_WriteChannelGroup(
        P2CONST(Dio_ChannelGroupType,AUTOMATIC,PTR_FAR) ChannelGroupIdPtr, VAR(Dio_PortLevelType,AUTOMATIC) Level );

/************************************************************************************
 * Service Name: Dio_GetVersionInfo
 * Service ID[hex]: 0x12
 * Sync/Async: Synchronous
 * Reentrancy: Reentrant
 * Parameters (in): None
 * Parameters (inout): None
 * Parameters (out): VersionInfo - Pointer to where to store the version information of this module.
 * Return value: None
 * Description: Function to get the version information of this module.
 ************************************************************************************/
//extern FUNC(void, memclass) Dio_GetVersionInfo(P2VAR(Std_VersionInfoType, memclass, ptrclass)VersionInfo);

/************************************************************************************
 * Service Name: Dio_FlipChannel
 * Service ID[hex]: 0x11
 * Sync/Async: Synchronous
 * Reentrancy: Reentrant
 * Parameters (in): ChannelId - ID of DIO channel.
 * Parameters (inout): None
 * Parameters (out): None
 * Return value: Dio_LevelType
 * Description: Function to flip the level of a channel and return the level of the channel after flip.
 ************************************************************************************/
extern FUNC(Dio_LevelType, memclass) Dio_FlipChannel(
        VAR(Dio_ChannelType, memclass) ChannelId);

/*******************************************************************************
 *                       External Variables                                    *
 *******************************************************************************/
extern Dio_ConfigChannel Channel_struct[];
extern Dio_ConfigPort Port_g[];
#define MAX_CHANNEL 42
#define MAX_CHANNEL_GROUP 4
extern Dio_ChannelGroupType channel_group[MAX_CHANNEL_GROUP];


#endif /* DIO_H_ */
