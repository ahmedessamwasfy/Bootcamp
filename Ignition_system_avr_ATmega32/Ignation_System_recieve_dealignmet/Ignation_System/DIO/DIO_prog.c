#include "../includes/Std_Types.h"
#include "../includes/BitwiseOperations.h"
#include "../includes/numbers.h"
#include "../MC/atmega32.h"
#include   "dio_config.h"
#include   "DIO_prog.h"

/************************************************************************************
* Function Name:       DIO_WritePin
* Parameters (in):     uint8 PinNum      PIN Number
                       uint8 PinValue    Value (HIGH 1),(LOW 0)
* Parameters (inout):  GPIO_PORTx_OUTPUT   the GPIO_OUTPUT register
* Parameters (out):    void
* Return value:        void
* Description:         Write on GPIO Pin
************************************************************************************/
void DIO_WritePin(uint8 PinNum,uint8 PinValue)
{
	if ((PORT0_START<=PinNum)&&(PORT0_END >=PinNum))  /* Get the GPIO port */  
	{                   
 
		PinNum-=PORT0_START;                         /* Get the real PIN number */
		if(STD_HIGH==PinValue)                           /* Check on the PIN value */
		{                           
		   Set_Bit(GPIO_PORT0_OUTPUT,PinNum);        /* Set the PIN in case of HIGH */
		}
		else if(STD_LOW==PinValue)
		{
		   Clear_Bit(GPIO_PORT0_OUTPUT,PinNum);       /* Clear the PIN in case of LOW */
		}
	}
	else if ((PORT1_START<=PinNum)&&(PORT1_END >=PinNum))
	{
		PinNum-=PORT1_START;
		if(STD_HIGH==PinValue)
		{
			Set_Bit(GPIO_PORT1_OUTPUT,PinNum);
		}
		else if(STD_LOW==PinValue)
		{
			Clear_Bit(GPIO_PORT1_OUTPUT,PinNum);
		}
	}
	else if ((PORT2_START<=PinNum)&&(PORT2_END >=PinNum))
	{
		PinNum-=PORT2_START;
		if(STD_HIGH==PinValue)
		{
			Set_Bit(GPIO_PORT2_OUTPUT,PinNum);
        }
		else if(STD_LOW==PinValue)
		{
			Clear_Bit(GPIO_PORT2_OUTPUT,PinNum);
		}
	}
									  
	else if ((PORT3_START<=PinNum)&&(PORT3_END >=PinNum))
	{
			PinNum-=PORT3_START;
			if(STD_HIGH==PinValue)
			{
				Set_Bit(GPIO_PORT3_OUTPUT,PinNum);
		    }
			else if(STD_LOW==PinValue)
			{
				Clear_Bit(GPIO_PORT3_OUTPUT,PinNum);
			}
     }			
			
		   
}
/*****************************************************************************************************/
	

/************************************************************************************
* Function Name:       DIO_ReadPin
* Parameters (in):     uint8 PinNum          GPIO PIN number
                       GPIO_PORTx_INPUT      GPIO PORTX INPUT register
* Parameters (inout): void
* Parameters (out):uint8 PinValue
* Return value:(HIGH=1) (LOW=0) 
* Description:Function that return GPIO PIN Value
************************************************************************************/	
	

uint8 DIO_ReadPin(uint8 PinNum){
	uint8 PinValue;

	if ((PORT0_START<=PinNum)&&(PORT0_END >=PinNum))        /* Get the the the GPIO port */ 
	{    
		  PinNum-=PORT0_START;                              /* Get the real PIN number */
		  PinValue=Get_Bit(GPIO_PORT0_INPUT,PinNum);        /* Get the PIN Value */
		  return PinValue;
	}
	
	else if ((PORT1_START<=PinNum)&&(PORT1_END >=PinNum))
	{
		PinNum-=PORT1_START;
		PinValue=Get_Bit(GPIO_PORT1_INPUT,PinNum);
		return PinValue;
    }                             
	
	else if ((PORT2_START<=PinNum)&&(PORT2_END >=PinNum))
	{
		PinNum-=PORT2_START;
		PinValue=Get_Bit(GPIO_PORT2_INPUT,PinNum);
		return PinValue;
    }
	                                 
		else if ((PORT3_START<=PinNum)&&(PORT3_END >=PinNum))
		{
			PinNum-=PORT3_START;
			PinValue=Get_Bit(GPIO_PORT3_INPUT,PinNum);
			return PinValue;
	    }
}	
/*****************************************************************************************************/
	
/************************************************************************************
* Function Name:       DIO_SetPinDirection
* Parameters (in):     uint8 PinNum          the pin number
                       uint8 PinDirection    the pin direction (OUTPUT =1) ,(INPUT=0)
* Parameters (inout):  GPIO_PORT0_DIR
* Parameters (out):    void
* Return value:        void
* Description:         Function that Set a GPIO PIN Direction
************************************************************************************/

void DIO_SetPinDirection(uint8 PinNum,uint8 PinDirection)
{                                                              
		      
	if ((PORT0_START<=PinNum)&&(PORT0_END >=PinNum))       /* Get the the the GPIO port */
	{
		PinNum-=PORT0_START;                               /* Get the real PIN number */

		if(OUTPUT==PinDirection)                           /* Check if PIN Direction is OUTPUT */
		{                          
			Set_Bit(GPIO_PORT0_DIR,PinNum);                /* Set the GPIO_PORT0_DIR  */
		}
		else if(INPUT==PinDirection)                       /* Check if PIN Direction is INPUT */
		{ 
			Clear_Bit(GPIO_PORT0_DIR,PinNum);              /* Clear GPIO_PORT0_DIR */
		}
	}
	else if ((PORT1_START<=PinNum)&&(PORT1_END >=PinNum))
	{
		PinNum-=PORT1_START;
		if(OUTPUT==PinDirection) 
		{
			Set_Bit(GPIO_PORT1_DIR,PinNum);
		}
		else if(INPUT==PinDirection)
		{
			Clear_Bit(GPIO_PORT1_DIR,PinNum);
		}
	}
	else if ((PORT2_START<=PinNum)&&(PORT2_END >=PinNum))
	{
		PinNum-=PORT2_START;
		if(OUTPUT==PinDirection) 
		{
			Set_Bit(GPIO_PORT2_DIR,PinNum);
		}
		else if(INPUT==PinDirection)
		{
			Clear_Bit(GPIO_PORT2_DIR,PinNum);
		}
	}
	else if ((PORT3_START<=PinNum)&&(PORT3_END >=PinNum))
	{
		PinNum-=PORT3_START;
		if(OUTPUT==PinDirection) 
		{
			Set_Bit(GPIO_PORT3_DIR,PinNum);
		}
		else if(INPUT==PinDirection)
		{
			Clear_Bit(GPIO_PORT3_DIR,PinNum);
		}
	}
}

/*****************************************************************************************************/

/************************************************************************************
* Function Name:       DIO_TogglePin
* Parameters (in):     uint8 PinNum
* Parameters (inout):  GPIO_PORT0_OUTPUT
* Parameters (out):    void
* Return value:        void
* Description:         Function that toggle a GPIO PIN 
************************************************************************************/

void DIO_TogglePin(uint8 PinNum)
{
	
	if ((PORT0_START<=PinNum)&&(PORT0_END >=PinNum))            /* Get the the the GPIO port */
	{
		PinNum-=PORT0_START;                                   /* Get the real PIN number */
		Toggle_Bit(GPIO_PORT0_OUTPUT,PinNum);                  /* Toggle the GPIO PIN */
	
	}
	else if ((PORT1_START<=PinNum)&&(PORT1_END >=PinNum))
	{
		PinNum-=PORT1_START;
	    Toggle_Bit(GPIO_PORT1_OUTPUT,PinNum);
	}
	
	else if ((PORT2_START<=PinNum)&&(PORT2_END >=PinNum))
	{
		PinNum-=PORT2_START;
		Toggle_Bit(GPIO_PORT2_OUTPUT,PinNum);
	}
	
	else if ((PORT3_START<=PinNum)&&(PORT3_END >=PinNum))
	{
		PinNum-=PORT3_START;
		Toggle_Bit(GPIO_PORT3_OUTPUT,PinNum);
	}
}
/*****************************************************************************************************/
