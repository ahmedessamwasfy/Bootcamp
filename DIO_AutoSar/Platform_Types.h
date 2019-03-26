#ifndef PLATFORM_TYPES_H_
#define PLATFORM_TYPES_H_

/************************General Type Definitions************************/
#define CPU_TYPE_8        8
#define CPU_TYPE_16      16
#define CPU_TYPE_32      32
#define CPU_TYPE_64      64
/************** Bit order definition ***********************************/
#define MSB_FIRST        0
#define LSB_FIRST        1

#define HIGH_BYTE_FIRST  0
#define LOW_BYTE_FIRST   1
/***************************Symbols **********************************/
#define CPU_TYPE CPU_TYPE_16
#define CPU_BIT_ORDER LSB_FIRST
#define CPU_BYTE_ORDER HIGH_BYTE_FIRST

/*****************************Types*********************************/
typedef unsigned char boolean;
typedef signed char sint8; /*        -128 .. +127            */
typedef unsigned char uint8; /*           0 .. 255             */
typedef signed short sint16; /*      -32768 .. +32767          */
typedef unsigned short uint16; /*           0 .. 65535           */
typedef signed long sint32; /* -2147483648 .. +2147483647     */
typedef signed long long sint64;
typedef unsigned long uint32; /*           0 .. 4294967295      */
typedef unsigned long long uint64; /*       0..18446744073709551615  */
typedef signed char sint8_least;
typedef unsigned char uint8_least;
typedef signed short sint16_least;
typedef unsigned short uint16_least;
typedef signed long sint32_least;
typedef unsigned long uint32_least;
typedef float float32;
typedef double float64;
typedef uint8 Std_ReturnType;
#define ZERO 0
/*
 * Boolean Values
 */
#ifndef FALSE
#define FALSE       (0u)
#endif
#ifndef TRUE
#define TRUE        (1u)
#endif

#endif /* PLATFORM_TYPES_H_ */
