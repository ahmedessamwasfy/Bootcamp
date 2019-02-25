/*
 * _7Seg.h
 *
 * Created: 2/18/2019 9:37:13 PM
 *  Author: Muhmed Hagag
 */ 


#ifndef sevseg_H_
#define sevseg_H_

#include "BitwiseOperations.h"
#include "Types.h"
#include "DIO.h"
/* Data pin for 7SEG */
#define DATA_PINA 8 
#define DATA_PINB 9
#define DATA_PINC 10
#define DATA_PIND 11

/* enable pin for 7SEG */

#define enable_pin_7seg_4 31
#define enable_pin_7seg_3 30
#define enable_pin_7seg_2 27
#define enable_pin_7seg_1 26

extern void BCDSevegments_enable(uint8 SevenSegment_Number);
extern void BCDSevegments_disable (uint8 SevenSegment_Number);
extern void BCDSevegments_displayNo (uint8 Display_Number);



#endif /* 7SEG_H_ */