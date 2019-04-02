
#ifndef STD_TYPES_H_
#define STD_TYPES_H_

#include "Platform_Types.h"
#include "Compiler.h"

#define  STD_TYPES_VENDOR_ID                       (1U)

/* DET Module Id */
#define STD_TYPES_MODULE_ID                        (197U)
/* Dio Instance Id */
#define STD_TYPES_INSTANCE_ID                      (0U)

#define STD_TYPES_SW_MAJOR_VERSION                 (1U)
#define STD_TYPES_SW_MINOR_VERSION                 (0U)
#define STD_TYPES_SW_PATCH_VERSION                 (0U)
/*
 * AUTOSAR Version 4.3.1
 */
#define STD_TYPES_AR_RELEASE_MAJOR_VERSION         (4U)
#define STD_TYPES_AR_RELEASE_MINOR_VERSION         (3U)
#define STD_TYPES_AR_RELEASE_PATCH_VERSION         (1U)

typedef uint8 Std_ReturnType;

typedef struct
{
uint16 vendorID;
uint16 moduleID;
uint8 sw_major_version;
uint8 sw_minor_version;
uint8 sw_patch_version;
} Std_VersionInfoType;

#ifndef STATUSTYPEDEFINED
#define STATUSTYPEDEFINED

/* Function Return OK */
#define E_OK (0x00U)

/* OSEK compliance */
typedef unsigned char StatusType;

#endif

/* Function Return NOT OK */
#define E_NOT_OK (0x01U)

/* Physical state 5V or 3.3V */
#define STD_HIGH (0x01U)

/* Physical state 0V */
#define STD_LOW  (0x00U)

/* Logical state active */
#define STD_ACTIVE  (0x01U)

/* Logical state idle */
#define STD_IDLE    (0x00U)

#define STD_ON      (0x01U)

#define STD_OFF     (0x00U)
#define NULL ((void *)0)
#endif /* STD_TYPES_H_ */
