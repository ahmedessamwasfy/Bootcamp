#include <avr/io.h>
#include <avr/interrupt.h>
#include "../Includes/Types.h"
#include "../Includes/DIO.h"
#include "../includes/ADC.h"
#include "../Includes/ADC_cfg.h"
#include "../Includes/BitwiseOperations.h"

void (*ADC_ISR_Function)(void) = 0; /*GLOBAL POINTER TO FUN TO USED IN CALLBACK FUN */


/*ADC_Initialize */
/* Parameters : void , void */
/* I/p : void , void  */
/* O/p : N/A */
/* Return : Void */
/* Function that initialize ADC  */
void ADC_Initialize(void)
{
	switch (ADC_RESOLUTION_MODE)
	{
		/* Select Eight Bit Resolution Mode */
		case EightBitResolution:
		SET_BIT(ADMUX, ADLAR);
		break;

		/* Select Ten Bit Resolution Mode */
		case TenBitResolution:
		SET_BIT(ADMUX, ADLAR);
		break;

		default:
		break;
	}
	
	/*********** PRESCALER CONFIGURATION **************/
	switch (ADC_PRESCALER_DIVISION)
	{
		/* Set Division Factor to 2 */
		case Prescaler_2:
		CLEAR_BIT(ADCSRA, ADPS0);
		CLEAR_BIT(ADCSRA, ADPS1);
		CLEAR_BIT(ADCSRA, ADPS2);
		break;
		/* Set Division Factor to 4 */
		case Prescaler_4:
		CLEAR_BIT(ADCSRA, ADPS0);
		SET_BIT(ADCSRA, ADPS1);
		CLEAR_BIT(ADCSRA, ADPS2);
		break;
		/* Set Division Factor to 8 */
		case Prescaler_8:
		SET_BIT(ADCSRA, ADPS0);
		SET_BIT(ADCSRA, ADPS1);
		SET_BIT(ADCSRA, ADPS2);
		break;
		/* Set Division Factor to 16 */
		case Prescaler_16:
		CLEAR_BIT(ADCSRA, ADPS0);
		CLEAR_BIT(ADCSRA, ADPS1);
		SET_BIT(ADCSRA, ADPS2);
		break;
		/* Set Division Factor to 32 */
		case Prescaler_32:
		SET_BIT(ADCSRA, ADPS0);
		CLEAR_BIT(ADCSRA, ADPS1);
		SET_BIT(ADCSRA, ADPS2);
		break;
		/* Set Division Factor to 64 */
		case Prescaler_64:
		CLEAR_BIT(ADCSRA, ADPS0);
		SET_BIT(ADCSRA, ADPS1);
		SET_BIT(ADCSRA, ADPS2);
		break;
		/* Set Division Factor to 128 */
		case Prescaler_128:
		SET_BIT(ADCSRA, ADPS0);
		SET_BIT(ADCSRA, ADPS1);
		SET_BIT(ADCSRA, ADPS2);
		break;
		default:
		break;
	}
/*********** TRIGGIRE MODE CONFIGURATION ************/
switch (ADC_TRIGERRING_MODE)
{
	/* ADC Free Running mode */
	case Free_Running_Mode:
	CLEAR_BIT(SFIOR, ADTS0);
	CLEAR_BIT(SFIOR, ADTS1);
	CLEAR_BIT(SFIOR, ADTS2);
	break;

	/* ADC Auto Trigger From Analog Comparator*/
	case Analog_Comparator:
	SET_BIT(SFIOR, ADTS0);
	SET_BIT(SFIOR, ADTS1);
	SET_BIT(SFIOR, ADTS2);
	break;

	/* ADC Auto Trigger From External Interrupt Request 0*/
	case External_Interrupt_Request_0:
	CLEAR_BIT(SFIOR, ADTS0);
	SET_BIT(SFIOR, ADTS1);
	CLEAR_BIT(SFIOR, ADTS2);
	break;

	/* ADC Auto Trigger From Timer/Counter0 Compare Match*/
	case Timer0_Compare_Match:
	SET_BIT(SFIOR, ADTS0);
	SET_BIT(SFIOR, ADTS1);
	CLEAR_BIT(SFIOR, ADTS2);
	break;

	/* ADC Auto Trigger From Timer/Counter0 Overflow*/
	case Timer0_Overflow:
	CLEAR_BIT(SFIOR, ADTS0);
	CLEAR_BIT(SFIOR, ADTS1);
	SET_BIT(SFIOR, ADTS2);
	break;

	/* ADC Auto Trigger From Timer/Counter1 Compare Match B*/
	case Timer1_CompareMatchB:
	SET_BIT(SFIOR, ADTS0);
	CLEAR_BIT(SFIOR, ADTS1);
	SET_BIT(SFIOR, ADTS2);
	break;

	/* ADC Auto Trigger From Timer/Counter1 Overflow*/
	case Timer1_Overflow:
	CLEAR_BIT(SFIOR, ADTS0);
	SET_BIT(SFIOR, ADTS1);
	SET_BIT(SFIOR, ADTS2);
	break;

	/* ADC Auto Trigger From Timer/Counter1 Capture Event*/
	case Timer1_Capture_Event:
	SET_BIT(SFIOR, ADTS0);
	SET_BIT(SFIOR, ADTS1);
	SET_BIT(SFIOR, ADTS2);
	break;
	default:
	break;
}
	/*********** OPERATION MODE CONFIGURATION ************/
	switch (ADC_TRIGERRING_MODE)
	{
		case OneShotMode:
		CLEAR_BIT(ADCSRA, ADATE); /* ADC One Shot Enable */
		break;
		case AutoTriggerMode:
		CLEAR_BIT(ADCSRA, ADATE); /* ADC Auto Trigger Enable */
		break;
		default:
		break;
	}
	/*********** VREF CONFIGURATION **************/
	switch (ADC_REFERENCE_VOLTAGE)
	{
		/* AREF, Internal Vref turned off */
		case AREF:
		CLEAR_BIT(ADMUX, REFS0);
		CLEAR_BIT(ADMUX, REFS1);
		break;
		/* AVCC with external capacitor at AREF pin */
		case AVCC:
		SET_BIT(ADMUX, REFS0);
		SET_BIT(ADMUX, REFS1);
		break;
		/* Internal 2.56V Voltage Reference with external capacitor at AREF pin */
		case Internal_2_56V:
		SET_BIT(ADMUX, REFS0);
		SET_BIT(ADMUX, REFS1);
		break;
		default:
		break;
	}
	
}

/*ADC_Enable */
/* Parameters : void , void */
/* I/p : void , void  */
/* O/p : N/A */
/* Return : Void */
/* Function ENABLE ADC  */
void ADC_Enable(void)
{
	SET_BIT(ADCSRA, ADEN);	/* Enable ADC */
}


/*ADC_Disable */
/* Parameters : void , void */
/* I/p : void , void  */
/* O/p : N/A */
/* Return : Void */
/* Function that DISBALE ADC  */
void ADC_Disable(void)
{
	CLEAR_BIT(ADCSRA, ADEN);/* DISABLE ADC */
}


/*ADC_StartConversion */
/* Parameters : uint8 */
/* I/p : void , void  */
/* O/p : N/A */
/* Return : uint16 */
/* Function that start ADC conversion  */
uint16 ADC_StartConversion(uint8 CHANNEL)
{
	uint16 VALUE;

	switch (CHANNEL)/*ADC CHANNEL FROM 0>>7*/
	{
		/* ADC Channel 0 */
		case ADC_Channel_0:
		CLEAR_BIT(ADMUX, MUX0);
		CLEAR_BIT(ADMUX, MUX1);
		CLEAR_BIT(ADMUX, MUX2);
		CLEAR_BIT(ADMUX, MUX3);
		break;
		/* ADC Channel 1 */
		case ADC_Channel_1:
		SET_BIT(ADMUX, MUX0);
		CLEAR_BIT(ADMUX, MUX1);
		CLEAR_BIT(ADMUX, MUX2);
		CLEAR_BIT(ADMUX, MUX3);
		break;

		/* ADC Channel 2 */
		case ADC_Channel_2:
		CLEAR_BIT(ADMUX, MUX0);
		SET_BIT(ADMUX, MUX1);
		CLEAR_BIT(ADMUX, MUX2);
		CLEAR_BIT(ADMUX, MUX3);
		break;

		/* ADC Channel 3 */
		case ADC_Channel_3:
		SET_BIT(ADMUX, MUX0);
		SET_BIT(ADMUX, MUX1);
		CLEAR_BIT(ADMUX, MUX2);
		CLEAR_BIT(ADMUX, MUX3);
		break;

		/* ADC Channel 4 */
		case ADC_Channel_4:
		CLEAR_BIT(ADMUX, MUX0);
		CLEAR_BIT(ADMUX, MUX1);
		SET_BIT(ADMUX, MUX2);
		CLEAR_BIT(ADMUX, MUX3);
		break;

		/* ADC Channel 5 */
		case ADC_Channel_5:
		SET_BIT(ADMUX, MUX0);
		CLEAR_BIT(ADMUX, MUX1);
		SET_BIT(ADMUX, MUX2);
		CLEAR_BIT(ADMUX, MUX3);
		break;

		/* ADC  Channel 6 */
		case ADC_Channel_6:
		CLEAR_BIT(ADMUX, MUX0);
		SET_BIT(ADMUX, MUX1);
		SET_BIT(ADMUX, MUX2);
		CLEAR_BIT(ADMUX, MUX3);
		break;

		/* ADC Channel 7 */
		case ADC_Channel_7:
		SET_BIT(ADMUX, MUX0);
		SET_BIT(ADMUX, MUX1);
		SET_BIT(ADMUX, MUX2);
		CLEAR_BIT(ADMUX, MUX3);
		break;
		default:
		break;

	}

	/* Start Conversion */
	SET_BIT(ADCSRA, ADSC);

	/* Wait until ADC conversion completes */
	while (!(GET_BIT(ADCSRA, ADIF)));

	/*********** ADJUST CONFIGURATION resoulution **************/
	switch (ADC_RESOLUTION_MODE)
	{
		case EightBitResolution:
		VALUE = ADCH; /*  Read High Register */
		break;
		case TenBitResolution:
		VALUE |= ADCL; /*  Read High & Low Register */
		VALUE |= (ADCH << 8);
		break;
		default:
		break;
	}
	return VALUE; /*Returned value after ADC converion */
}

uint16 ADC_GetConvertedValue(void)
{
	uint16 VALUE;

	/* Check for RESOLUTION_MODE */
	switch (ADC_RESOLUTION_MODE)
	{
		case EightBitResolution:
		VALUE = ADCH; /*  Read High Register */
		break;
		case TenBitResolution:
		VALUE |= ADCL; /*  Read High & Low Register */
		VALUE |= (ADCH << 8);
		break;
		default:
		break;
	}

	return VALUE ;

}
/*ADC_setCallBack */
/* Parameters : void , void */
/* I/p : void , void  */
/* O/p : N/A */
/* Return : Void */
/* call back function for ISR */
void ADC_setCallBack(void (*Ptr)(void))
{

	ADC_ISR_Function = Ptr;

}


/*ADC_InterruptEnable */
/* Parameters : void , void */
/* I/p : void , void  */
/* O/p : N/A */
/* Return : Void */
/* Function that enable  interrupt  */
void ADC_InterruptEnable(void)
{
	SET_BIT(ADCSRA, ADIE);/* enable interrupt */
}

/*ADC_InterruptDisable */
/* Parameters : void , void */
/* I/p : void , void  */
/* O/p : N/A */
/* Return : Void */
/* Function that disable  interrupt  */
void ADC_InterruptDisable(void)
{
	CLEAR_BIT(ADCSRA, ADIE);/* Disable Interrupt  */
}


ISR( ADC_vect)
{
	ADC_ISR_Function();
}
