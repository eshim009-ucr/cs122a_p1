#ifndef TASK_H
#define TASK_H
#include "pico/stdlib.h"


typedef uint TaskState;
// Based on zyBooks example
typedef struct _Task {
	TaskState state;
	uint period;
	// A scheduling struct provided by the Pico SDK
	struct repeating_timer sdk_timer;
	// The callback function defined by the Pico SDK
	// This function as the state machine's tick function
	repeating_timer_callback_t sdk_callback;
} Task;


// Set the given task to execute using the Pico SDK
// Uses internal struct period
void schedule_task(Task* task);


#endif
