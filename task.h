#ifndef TASK_H
#define TASK_H
#include "pico/stdlib.h"


typedef uint TaskState;
// Based on zyBooks example
typedef struct _Task {
	TaskState state;
	// The period of the task, measured in milliseconds
	uint period;
	// Time elapsed since the last task tick
	uint since_last;
	// Handler function to be called each tick
	void (*handler)(void);
} Task;


// Initialize the scheduler
void init_scheduler();
// Set the given task to execute using the Pico SDK
// Uses internal struct period
// Returns true if successful
bool schedule_task(Task* task);
void start_scheduler();
void stop_scheduler();


#endif
