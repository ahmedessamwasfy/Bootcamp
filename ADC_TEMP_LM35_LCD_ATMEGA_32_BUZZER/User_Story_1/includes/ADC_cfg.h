#ifndef __ADC_CFG_H__
#define __ADC_CFG_H__

   /* Parameter to set resolution.*/
#define ADC_RESOLUTION_MODE			EightBitResolution

 /*Parameter to set reference voltage.*/
#define ADC_REFERENCE_VOLTAGE		AVCC

 /*Parameter to set reference voltage.*/
#define ADC_PRESCALER_DIVISION		Prescaler_128

 /*Parameter to set reference voltage.*/
#define ADC_TRIGERRING_MODE			Free_Running_Mode

 /*Parameter to set operation mode. */
#define ADC_OPERATION_MODE			AutoTriggerMode


enum VoltageReferenceSelections_e{
	AREF,
	AVCC,
	Internal_2_56V,
};
	
enum ADC_Resolution_e{
	EightBitResolution,
	TenBitResolution,
};

enum ADC_Prescaler_e{
	Prescaler_2,
	Prescaler_4,
	Prescaler_8,
	Prescaler_16,
	Prescaler_32,
	Prescaler_64,
	Prescaler_128,
};

enum ADC_OperationMode_e{
	OneShotMode,
	AutoTriggerMode,
};	

enum ADC_TriggeringMode_e{
	Free_Running_Mode,    
	Analog_Comparator,
	External_Interrupt_Request_0,
	Timer0_Compare_Match,
	Timer0_Overflow,
	Timer1_CompareMatchB,
	Timer1_Overflow,
	Timer1_Capture_Event,
};

enum ADC_Channels_e{
	ADC_Channel_0,
	ADC_Channel_1,
	ADC_Channel_2,
	ADC_Channel_3,
	ADC_Channel_4,
	ADC_Channel_5,
	ADC_Channel_6,
	ADC_Channel_7,
};
#define VREF 5
#define V_TO_MV 1000
#endif