#include "task.h"


// The smallest time resolution for task period, in milliseconds
static const uint SCHEDULER_QUANTUM = 50;
#define NUM_TASKS 2
static Task *tasks[NUM_TASKS];
repeating_timer_t sdk_timer;


bool scheduler_tick(struct repeating_timer *t);


// Scheduling from this SDK example
// https://github.com/raspberrypi/pico-examples/blob/master/timer/hello_timer/hello_timer.c
void init_scheduler() {
	for (uint i = 0; i < NUM_TASKS; ++i) {
		tasks[i] = NULL;
	}
}


void start_scheduler() {
	add_repeating_timer_ms(
		// Negative schedules since the last start, not the last end
		-SCHEDULER_QUANTUM,
		// Conatins tick function
		scheduler_tick,
		// Send along extra data for arguments, not needed
		NULL,
		// Store timer data for later reference
		&sdk_timer
	);
}


void stop_scheduler() {
	cancel_repeating_timer(&sdk_timer);
}


bool schedule_task(Task* task) {
	for (uint i = 0; i < NUM_TASKS; ++i) {
		if (tasks[i] == NULL) {
			tasks[i] = task;
			return true;
		}
	}
	
	return false;
}


// Based on example scheduler from zyBooks
bool scheduler_tick(struct repeating_timer *t) {
	for (uint i = 0; i < NUM_TASKS; ++i) {
		if (tasks[i] != NULL) {
			if (tasks[i]->since_last >= tasks[i]->period) {
				tasks[i]->handler();
				tasks[i]->since_last = 0;
			}
			tasks[i]->since_last += SCHEDULER_QUANTUM;
		}
	}
	
	// Contintue repeating
	return true;
}
