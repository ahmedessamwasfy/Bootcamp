
#ifndef    TYPES_H
#define   TYPES_H
typedef unsigned char             uint8;
typedef signed char               sint8;
typedef unsigned char*             ptr8;
typedef unsigned short            uint16;
typedef signed short              sint16;
typedef unsigned long int         uint32;
typedef signed   long int         sint32;

typedef void(* tasktype)(void);
typedef struct task_pramters
{
	tasktype address;
	uint16    priority;
	uint16    periodicity;
	uint16    Remaining;
	
}task;

#endif









