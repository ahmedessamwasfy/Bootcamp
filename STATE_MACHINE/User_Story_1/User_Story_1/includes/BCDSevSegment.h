
#ifndef __BCDSEVSEGMENT_H__ 
#define __BCDSEVSEGMENT_H__

#define SEVSEG_D0 Pin11
#define SEVSEG_D1 Pin12
#define SEVSEG_D2 Pin13
#define SEVSEG_D3 Pin14

#define high     1
#define low      0
#define output   1
#define input    0
extern void BCDSevegments_enable(uint8 SevenSegment_Number);
extern void BCDSevegments_disable (uint8 SevenSegment_Number);
extern void BCDSevegments_displayNo (uint8 Display_Number);

#endif