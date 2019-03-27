#include "Dio_MemMap.h"
#include "Dio.h"
#include "Det.h"
#include "internal.h"
#include "Reg.h"
#include "COMMON_MACRO.h"

/************************************************************************************
 * Service Name: Dio_WriteChannel
 * Service ID[hex]: 0x01
 * Sync/Async: Synchronous
 * Reentrancy: Reentrant
 * Parameters (in): ChannelId - ID of DIO channel.
 *                  Level - Value to be written.
 * Parameters (input): None
 * Parameters (out): None
 * Return value: None
 * Description: Function to set a level of a channel.
 * SWS_Dio_00134
 ************************************************************************************/
FUNC(void,memclass) Dio_WriteChannel(VAR(Dio_ChannelType,memclass) ChannelId,
VAR(Dio_LevelType,memclass) Level)
{
    uint8 index = 0U;/*index for loop */
    if (ChannelId > MAX_CHANNEL)/*check if channel ID is valid with my channels */
    {
        /*check if the channel id is maximum 42 report INVALID_ERROR_ID for DET fun */
        /*if there is invalid id LED2 will turn on */
        Det_ReportError(ZERO, ZERO, ZERO, DIO_E_PARAM_INVALID_CHANNEL_ID);
    }
    else
    {
        for (index = ZERO; index < (uint8) MAX_SIZE; index++)
        {
            if (Channel_struct[index].id == ChannelId)/*check if ID argument is equal to configuration*/
            {
                if ((uint8) Channel_struct[index].Direction == (uint8) OP)
                {
                    switch (Channel_struct[index].Port)
                    /*switch on port */
                    {
                    case PORTA_:
                        (PORTA->DATA) &= ~(1U << Channel_struct[index].Pin_Num);/*clear data register in PORTA */
                        if (STD_HIGH == Level)
                        {
                            /*SWS_Dio_00028*/
                            (PORTA->DATA) |= (1U
                                    << Channel_struct[index].Pin_Num);
                        }
                        break;

                    case PORTB_:
                        (PORTB->DATA) &= ~(1u << Channel_struct[index].Pin_Num);/*clear data register in PORTB */
                        if (STD_HIGH == Level)
                        {
                            /*SWS_Dio_00028*/

                            (PORTB->DATA) |= (1U
                                    << Channel_struct[index].Pin_Num);
                        }
                        break;

                    case PORTC_:
                        (PORTC->DATA) &= ~(1U << Channel_struct[index].Pin_Num);/*clear data register in PORTB */
                        if (STD_HIGH == Level)
                        {
                            /*SWS_Dio_00028*/

                            (PORTC->DATA) |= (1U
                                    << Channel_struct[index].Pin_Num);
                        }
                        break;

                    case PORTD_:
                        (PORTD->DATA) &= ~(1U << Channel_struct[index].Pin_Num);/*clear data register in PORTC */
                        if (STD_HIGH == Level)
                        {
                            /*SWS_Dio_00028*/

                            (PORTD->DATA) |= (1U
                                    << Channel_struct[index].Pin_Num);
                        }
                        break;
                    case PORTE_:
                        (PORTE->DATA) &= ~(1U << Channel_struct[index].Pin_Num);/*clear data register in PORTE */
                        if (STD_HIGH == Level)
                        {
                            /*SWS_Dio_00028*/

                            (PORTE->DATA) |= (1U
                                    << Channel_struct[index].Pin_Num);
                        }
                        break;
                    case PORTF_:
                        (PORTF->DATA) &= ~(1U << Channel_struct[index].Pin_Num);/*clear data register in PORTD */
                        if ((uint8) STD_HIGH == (uint8) Level)
                        {
                            /*SWS_Dio_00028*/

                            (PORTF->DATA) |= (1U
                                    << Channel_struct[index].Pin_Num);
                        }
                        break;
                    default:
                        break;
                    }
                }
                else
                {
                    /*SWS_Dio_00108*/
                    /*SWS_Dio_00029*/
                    /*SWS_Dio_00079*/
                }
            }

        }
    }
}
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
 * SWS_Dio_00133
 ************************************************************************************/
FUNC(Dio_LevelType,memclass) Dio_ReadChannel(
VAR(Dio_ChannelType,memclass) ChannelId)
{
    uint8 index_ = ZERO;
    uint8 value = ZERO; /*return value */
    if (ChannelId > MAX_CHANNEL)/*check if channel ID is valid with my channels */
    {
        /*check if the channel id is maximum 42 report INVALID_ERROR_ID for DET fun */
        /*if there is invalid id LED2 will turn on */
        Det_ReportError(ZERO, ZERO, ZERO, DIO_E_PARAM_INVALID_CHANNEL_ID);
    }
    else
    {
        for (index_ = ZERO; (uint8) index_ < (uint8) MAX_SIZE; index_++)
        {
            if (Channel_struct[index_].id == ChannelId)/*check if ID is valid */
            {
                if ((uint8) Channel_struct[index_].Direction == (uint8) IP)
                {
                    switch (Channel_struct[index_].Port)
                    {
                    case PORTA_:
                        value = ((uint8) (PORTA->DATA)
                                & (1 << Channel_struct[index_].Pin_Num));
                        break;

                    case PORTB_:
                        value = ((uint8) PORTB->DATA)
                                & (1 << Channel_struct[index_].Pin_Num);
                        break;

                    case PORTC_:
                        value = ((uint8) PORTC->DATA)
                                & (1 << Channel_struct[index_].Pin_Num);
                        break;

                    case PORTD_:
                        value = ((uint8) PORTD->DATA)
                                & (1 << Channel_struct[index_].Pin_Num);
                        break;
                    case PORTE_:
                        value = ((uint8) (PORTE->DATA)
                                & (1 << Channel_struct[index_].Pin_Num));
                        break;
                    case PORTF_:
                        value = ((uint8) (PORTF->DATA)
                                & (1 << Channel_struct[index_].Pin_Num));
                        break;
                    default:
                        break;
                    }
                }
            }

        }
    }
    /* SWS_Dio_00031*/
    return value;/*Return Channel Value */
}
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
 * SWS_Dio_00135
 ************************************************************************************/
FUNC(void,DIO_MEM_CLASS) Dio_WritePort(
        VAR(Dio_PortType,AUTOMATIC) PortId,
        VAR(Dio_PortLevelType,AUTOMATIC) Level)
{
    uint8 index = ZERO;
    uint8 final = ZERO;/* value which returned by Dio_WritePort serves */
    for (index = ZERO; index < MAX_SIZE; index++)
    {
        if (Port_g[index].Direction_port == OP)/*check if port is output */
        {
            if (Port_g[index].port_id == PortId)/* check the valid id */
            {
                switch (PortId)
                {
                case PORTA_:
                    PORTA->DATA = Level;/* write level in port */
                    break;
                case PORTB_:
                    PORTB->DATA = Level;/* write level in port */
                    break;
                case PORTC_:
                    PORTC->DATA = Level;/* write level in port */
                    break;
                case PORTD_:
                    PORTD->DATA = Level;/* write level in port */
                    break;
                case PORTE_:
                    PORTE->DATA = Level;/* write level in port */
                    break;
                case PORTF_:
                    PORTF->DATA = Level;/* write level in port */
                    break;
                default:
                    break;
                }
            }
            final = (PORTF->DATA);/*assign the value of data register in final value and return */
        }
        else
        {
            /* DET Error */
        }
    }
    /*SWS_Dio_00031*/
    return final;
}
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
FUNC(Dio_PortLevelType,memclass) Dio_ReadPort(
VAR(Dio_PortType,memclass) PortId)
{
    uint8 Port_Value, index = ZERO;
    for (index = (uint8) 0; index < MAX_SIZE; index++)
    {
        if (Port_g[index].Direction_port == IP)
        {
            if (Port_g[index].port_id == PortId)
            {
                switch (Port_g[index].port_id)
                /* switch on PORT id */
                {
                case PORTA_:
                    Port_Value = PORTA->DATA;/*read data register */
                    break;

                case PORTB_:
                    Port_Value = PORTB->DATA;/*read data register */
                    break;
                case PORTC_:
                    Port_Value = PORTC->DATA;/*read data register */
                    break;
                case PORTD_:
                    Port_Value = PORTD->DATA;/*read data register */
                    break;
                case PORTE_:
                    Port_Value = PORTE->DATA;/*read data register */
                    break;
                case PORTF_:
                    Port_Value = PORTF->DATA;/*read data register */
                    break;
                default:
                    break;
                }
            }

        }
        else
        {
            /* DET Error */
        }
    }
    /*SWS_Dio_00031*/
    return Port_Value; /*return PORT value */

}

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
FUNC(Dio_LevelType, memclass) Dio_FlipChannel(
VAR(Dio_ChannelType, memclass) ChannelId)
{
    uint8 index = ZERO;/*index for loop */
    uint8 last_value = ZERO;
    if (ChannelId > MAX_CHANNEL)/*check if channel ID is valid with my channels */
    {
        /*check if the channel id is maximum 42 report INVALID_ERROR_ID for DET fun */
        /*if there is invalid id LED2 will turn on */
        Det_ReportError(ZERO,ZERO, ZERO, DIO_E_PARAM_INVALID_CHANNEL_ID);
    }
    else
    {
        for (index = ZERO; index < (uint8) MAX_SIZE; index++)
        {
            if (Channel_struct[index].id == ChannelId)/*check if ID argument is equal to configuration*/
            {
                /*switch on port */

                switch (Channel_struct[index].Port)
                {
                case PORTA_:
                    /*SWS_Dio_00191*/
                    (PORTA->DATA) ^= (1U << Channel_struct[index].Pin_Num);/*toggle pin in dataregister in PORTA */
                    break;
                case PORTB_:
                    /*SWS_Dio_00191*/

                    (PORTB->DATA) ^= (1U << Channel_struct[index].Pin_Num); /*toggle pin in dataregister in PORTB */
                    break;
                case PORTC_:
                    /*SWS_Dio_00191*/

                    (PORTC->DATA) ^= (1U << Channel_struct[index].Pin_Num);/*toggle pin in dataregister in PORTC */
                    break;
                case PORTD_:
                    /*SWS_Dio_00191*/

                    (PORTD->DATA) ^= (1U << Channel_struct[index].Pin_Num);/*toggle pin in dataregister in PORTD */
                    break;
                case PORTE_:
                    /*SWS_Dio_00191*/

                    (PORTE->DATA) ^= (1U << Channel_struct[index].Pin_Num);/*toggle pin in dataregister in PORTE */
                    break;
                case PORTF_:
                    /*SWS_Dio_00191*/

                    (PORTF->DATA) ^= (1U << Channel_struct[index].Pin_Num);/*toggle pin in dataregister in PORTF */
                    break;
                default:
                    break;
                }
            }
            else
            {
            }
            last_value = (PORTF->DATA);
        }
    }
    return last_value;
}

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

FUNC(Dio_PortLevelType,DIO_MEM_CLASS) Dio_ReadChannelGroup(
P2CONST(Dio_ChannelGroupType,AUTOMATIC,PTR_FAR) ChannelGroupIdPtr )
{
    /*local variables*/
    uint8 data_ch_group = STD_LOW;
    uint8 i = STD_LOW;
    /*loop to the size of array of structs*/
    for(i=ZERO; i<MAX_SIZE; i++)
    {
        /*check the port if it is valid*/
        if(channel_group[i].port == ChannelGroupIdPtr->port)
        {
            /*specify the given group*/
            switch(channel_group[i].port)
            {
                case PORTA_ :
                /*read group pins in Port A by masking its value with port then apply offset to read from LSB*/
                data_ch_group = (PORTA->DATA & (ChannelGroupIdPtr->mask)) >> ChannelGroupIdPtr->offset;
                break;

                case PORTB_ :
                /*read the desired group in Port B by masking its value with port then apply offset to read from LSB*/
                data_ch_group = (PORTB->DATA & (ChannelGroupIdPtr->mask)) >> ChannelGroupIdPtr->offset;
                break;

                case PORTC_ :
                /*read the desired group in Port C by masking its value with port then apply offset to read from LSB*/
                data_ch_group = (PORTC->DATA & (ChannelGroupIdPtr->mask)) >> ChannelGroupIdPtr->offset;
                break;

                case PORTD_ :
                /*read the desired group in Port D by masking its value with port then apply offset to read from LSB*/
                data_ch_group = (PORTD->DATA & (ChannelGroupIdPtr->mask)) >> ChannelGroupIdPtr->offset;
                break;

                case PORTE_ :
                /*read the desired group in Port D by masking its value with port then apply offset to read from LSB*/
                data_ch_group = (PORTE->DATA & (ChannelGroupIdPtr->mask)) >> ChannelGroupIdPtr->offset;
                break;

                case PORTF_ :
                /*read the desired group in Port D by masking its value with port then apply offset to read from LSB*/
                data_ch_group = (PORTF->DATA & (ChannelGroupIdPtr->mask)) >> ChannelGroupIdPtr->offset;
                break;
                default:
                break;
            }
            break;
        }
    }
    return data_ch_group;
}
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
FUNC(void,DIO_MEM_CLASS) Dio_WriteChannelGroup(
P2CONST(Dio_ChannelGroupType,AUTOMATIC,PTR_FAR) ChannelGroupIdPtr, VAR(Dio_PortLevelType,AUTOMATIC) Level )
            {

                switch(channel_group->port)
                {
                    case PORTA_:
                    PORTA->DATA|=(channel_group->mask & Level);/*write mask in dara register */
                    break;
                    case PORTB_:
                    PORTB->DATA|=(channel_group->mask & Level);/*write mask in dara register */
                    break;
                    case PORTC_:
                    PORTC->DATA|=(channel_group->mask & Level);/*write mask in dara register */
                    break;
                    case PORTD_:
                    PORTD->DATA|=(channel_group->mask& Level);/*write mask in dara register */
                    break;
                    case PORTE_:
                    PORTE->DATA|=(channel_group->mask & Level);/*write mask in dara register */
                    break;
                    case PORTF_:
                    PORTF->DATA|=(channel_group->mask& Level);/*write mask in dara register */
                    break;
                    default:
                    break;
                }
            }

