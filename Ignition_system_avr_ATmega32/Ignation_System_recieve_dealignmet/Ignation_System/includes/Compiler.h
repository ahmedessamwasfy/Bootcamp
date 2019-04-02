

#ifndef COMPILER_H_
#define COMPILER_H_

#define COMPILER_VENDOR_ID                     (1U)

/* COMPILER Module Id */
#define COMPILER_MODULE_ID                     (198U)
/* COMPILER Instance Id */
#define COMPILER_INSTANCE_ID                   (0U)
/*
 * Module Version 1.0.0
 */
#define COMPILER_SW_MAJOR_VERSION                (1U)
#define COMPILER_SW_MINOR_VERSION                (0U)
#define COMPILER_SW_PATCH_VERSION                (0U)
/*
 * AUTOSAR Version 4.3.1
 */
#define COMPILER_AR_RELEASE_MAJOR_VERSION         (4U)
#define COMPILER_AR_RELEASE_MINOR_VERSION         (3U)
#define COMPILER_AR_RELEASE_PATCH_VERSION         (1U)

/* [SWS_COMPILER_00046] Memory class AUTOMATIC */
#define AUTOMATIC

/* [SWS_COMPILER_00059] Memory class TYPEDEF */
#define TYPEDEF

/*[SWS_COMPILER_00051] NULL_PTR */
#define NULL_PTR                                         ((void *)0)

/* [SWS_COMPILER_00057] INLINE*/
#define INLINE inline

/* [SWS_COMPILER_00060] LOCAL_INLINE */
#define LOCAL_INLINE

/* [SWS_COMPILER_00001] FUNC identification information. */
#define FUNC(rettype, memclass)                            rettype

/* [SWS_COMPILER_00061] FUNC_P2CONST */
#define FUNC_P2CONST(rettype, ptrclass, memclass)          const  rettype *

/* [SWS_COMPILER_00063] FUNC_P2VAR */
#define FUNC_P2VAR(rettype, ptrclass, memclass)            rettype *

/* [SWS_COMPILER_00006] P2VAR   */
#define P2VAR(ptrtype, memclass, ptrclass)                 ptrtype *

/* [SWS_COMPILER_00013] P2CONST */
#define P2CONST(ptrtype, memclass, ptrclass)               const ptrtype *

/* [SWS_COMPILER_00031] CONSTP2VAR */
#define CONSTP2VAR (ptrtype, memclass, ptrclass)           ptrtype * const

/* [SWS_COMPILER_00032] CONSTP2CONST  */
#define CONSTP2CONST(ptrtype, memclass, ptrclass)          const ptrtype * const

/* [SWS_COMPILER_00039] P2FUNC  */
#define P2FUNC(rettype, ptrclass, fctname)                 rettype (* fctname)

/* [SWS_COMPILER_00065] CONSTP2FUNC */
#define CONSTP2FUNC(rettype, ptrclass, fctname)            rettype (* const fctname)

/* [SWS_COMPILER_00023] CONST */
#define CONST(consttype, memclass)                         const type

/* [SWS_COMPILER_00026]  VAR */
#define VAR(vartype, memclass)                             vartype



#endif /* COMPILER_H_ */
