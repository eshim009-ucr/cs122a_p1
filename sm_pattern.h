#ifndef SM_PATTERN_H
#define SM_PATTERN_H
#include "task.h"


// Task for the state machine that reads from the ADC
extern Task task_sm_pattern;
typedef enum {PATTERN_BINARY, PATTERN_FADE} Pattern;
extern Pattern current_pattern;


#endif
