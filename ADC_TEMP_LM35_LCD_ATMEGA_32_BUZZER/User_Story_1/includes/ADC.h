#ifndef ADC_H_
#define ADC_H_
#define VREF 5
#define V_TO_MV 1000

extern void ADC_Initialize(void);/* Function to initialize module.*/

extern uint16 ADC_StartConversion(uint8 channel_num ); /*Function to start conversion and return value after conversion (Synchronous).*/

extern void ADC_Enable(); /*Function to enable ADC.*/

extern void ADC_Disable(); /* Function to disable ADC.*/

extern uint16 ADC_GetConvertedValue();/* Function to get converted value.*/

extern void ADC_InterruptEnable(); /*Function to enable ADC conversion interrupt.*/

extern void ADC_InterruptDisable(); /* Function to disable ADC conversion interrupt.*/

extern void ADC_setCallBack(); /* Function to set a callback when the interrupt is fired.*/



#endif /* ADC_H_ */