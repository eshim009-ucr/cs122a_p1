#ifndef TASK_H
#define TASK_H
#include "pico/stdlib.h"


typedef int TaskState;
// Based on zyBooks example
typedef struct _Task {
	int state;
	unsigned int period;
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
