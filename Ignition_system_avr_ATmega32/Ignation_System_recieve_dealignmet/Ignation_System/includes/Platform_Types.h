

#ifndef PLATFORM_TYPES_H_
#define PLATFORM_TYPES_H_

#define PLATFORM_VENDOR_ID                     (1U)

/* PLATFORM Module Id */
#define PLATFORM_MODULE_ID                     (199U)
/* PLATFORM Instance Id */
#define PLATFORM_INSTANCE_ID                   (0U)
/*
 * Module Version 1.0.0
 */
#define PLATFORM_SW_MAJOR_VERSION                (1U)
#define PLATFORM_SW_MINOR_VERSION                (0U)
#define PLATFORM_SW_PATCH_VERSION                (0U)
/*
 * AUTOSAR Version 4.3.1
 */
#define PLATFORM_AR_RELEASE_MAJOR_VERSION         (4U)
#define PLATFORM_AR_RELEASE_MINOR_VERSION         (3U)
#define PLATFORM_AR_RELEASE_PATCH_VERSION         (1U)

#define CPU_TYPE_8                                (8U)
#define CPU_TYPE_16                               (16U)
#define CPU_TYPE_32                               (32U)

#define MSB_FIRST                                 (0U)   /* Big Endian*/
#define LSB_FIRST                                 (1U)   /* Little Endian*/

#define HIGH_BYTE_FIRST                           (0U)   /* Big Endian*/
#define LOW_BYTE_FIRST                            (1U)   /* Little Endian*/


#define CPU_TYPE                     CPU_TYPE_32
#define CPU_BIT_ORDER                LSB_FIRST       /*(tiva c) Little Endian */
#define CPU_BYTE_ORDER               LOW_BYTE_FIRST  /*(tiva c) Little Endian*/

/*
 * Boolean Values
 */
#ifndef TRUE
#define TRUE (1U)
#endif

#ifndef FALSE
#define FALSE (0U)
#endif

typedef unsigned char                  boolean;
typedef signed char                    sint8;
typedef unsigned char                  uint8;
typedef signed short                   sint16;
typedef unsigned short                 uint16;
typedef signed long                    sint32;
typedef signed long long               sint64;
typedef unsigned long                  uint32;
typedef unsigned long long             uint64;
typedef signed char                    sint8_least;
typedef unsigned char                  uint8_least;
typedef signed short                   sint16_least;
typedef unsigned short                 uint16_least;
typedef signed long                    sint32_least;
typedef unsigned long                  uint32_least;
typedef float                          float32;
typedef double                         float64;




#endif /* PLATFORM_TYPES_H_ */
