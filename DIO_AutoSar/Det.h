#ifndef DET_H_
#define DET_H_
#include "Std_Types.h"
/*******************************************************************************
 *                      Function Prototypes                                    *
 *******************************************************************************/
FUNC(Std_ReturnType,memclass) Det_ReportError(
        VAR(uint16,memclass) ModuleId, VAR(uint8,memclass) InstanceId,
        VAR(uint8,memclass) ApiId, VAR(uint8,memclass) ErrorId);

/*******************************************************************************
 *                      DET Error Codes                                        *
 *******************************************************************************/

/* [SWS_Dio_00175] Invalid channel requested.*/
#define DIO_E_PARAM_INVALID_CHANNEL_ID  (uint8)0x0A

/* [SWS_Dio_00177] Invalid port requested. */
#define DIO_E_PARAM_INVALID_PORT_ID     (uint8)0x14

/* [SWS_Dio_00178] Invalid channel group requested. */
#define DIO_E_PARAM_INVALID_GROUP       (uint8)0x1F

/* [SWS_Dio_00188] API service called with a NULL pointer. */
#define DIO_E_PARAM_POINTER             (uint8)0x20



#endif /* DET_H_ */
