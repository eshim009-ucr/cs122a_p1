#ifndef TASK_H
#define TASK_H


typedef int TaskState;
// Based on zyBooks example
typedef struct _Task {
	int state;
	unsigned int period;
	unsigned int sinceLastTick;
	TaskState (*handler)(TaskState state);
} Task;


#endif
