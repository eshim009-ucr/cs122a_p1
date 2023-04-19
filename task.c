#include "task.h"


// Scheduling from this SDK example
// https://github.com/raspberrypi/pico-examples/blob/master/timer/hello_timer/hello_timer.c
void schedule_task(Task* task) {
	add_repeating_timer_ms(
		// Negative schedules since the last start, not the last end
		-task->period,
		// Conatins tick function
		task->sdk_callback,
		// Send along the task struct as extra data
		// Used to update SM state
		&task,
		// Store timer data for later reference
		&task->sdk_timer
	);
}
