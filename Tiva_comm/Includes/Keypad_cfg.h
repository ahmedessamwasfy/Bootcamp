#include "driverlib/gpio.h"
#include "inc/hw_memmap.h"
#include "driverlib/rom.h"

#ifndef KEYPAD_CFG
#define KEYPAD_CFG

#define  KEYPAD_COL_NUM        NUM_3
#define  KEYPAD_ROW_NUM        NUM_3



#define  KEYPAD_COL1_PORT      GPIO_PORTD_BASE
#define  KEYPAD_COL2_PORT      GPIO_PORTD_BASE
#define  KEYPAD_COL3_PORT      GPIO_PORTA_BASE

#define  KEYPAD_COL1_clk       SYSCTL_PERIPH_GPIOD
#define  KEYPAD_COL2_clk       SYSCTL_PERIPH_GPIOD
#define  KEYPAD_COL3_clk       SYSCTL_PERIPH_GPIOA

#define  KEYPAD_COL1_PIN       GPIO_PIN_1
#define  KEYPAD_COL2_PIN       GPIO_PIN_6
#define  KEYPAD_COL3_PIN       GPIO_PIN_6


#define  KEYPAD_RAW1_PORT      GPIO_PORTB_BASE
#define  KEYPAD_RAW2_PORT      GPIO_PORTB_BASE
#define  KEYPAD_RAW3_PORT      GPIO_PORTB_BASE

#define  KEYPAD_RAW1_clk       SYSCTL_PERIPH_GPIOB
#define  KEYPAD_RAW2_clk       SYSCTL_PERIPH_GPIOB
#define  KEYPAD_RAW3_clk       SYSCTL_PERIPH_GPIOB

#define  KEYPAD_RAW1_PIN       GPIO_PIN_2
#define  KEYPAD_RAW2_PIN       GPIO_PIN_3
#define  KEYPAD_RAW3_PIN       GPIO_PIN_6


#endif
