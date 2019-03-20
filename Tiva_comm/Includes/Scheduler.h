/*
 * Scheduler.h
 *
 * Created: 2/23/2019 4:30:55 PM
 *  Author: AVE-LAP-005
 */ 


#ifndef SCHEDULER_H_
#define SCHEDULER_H_
#define MAX_SIZE 5
#define FALSE 0
#define TRUE 1
/* structure of every task*/
volatile typedef struct{
	void (*task)(void);
	uint32 Periodicity;
	uint32 Priority;
	uint32 Delay;
	uint32 id;
	}TCB;

/* Scheduler APIS */
void Scheduler_Init();
void Scheduler_Start();
void TTC_Scheduler();
uint8 Scheduler_Add_Task(TCB* Task);
void Remove_Task(uint32 Task_id);
/* Array of Structures*/
TCB System_Tasks[MAX_SIZE];


#endif /* SCHEDULER_H_ */
