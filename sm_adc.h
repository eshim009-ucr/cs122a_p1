#ifndef SM_ADC_H
#define SM_ADC_H
#include "task.h"


// Task for the state machine that reads from the ADC
extern Task task_sm_adc;
// Set by the ADC state machine when a step has been detected
// Cleared by the receiving state machine upon reading it
// Essentially functions as a binary sempahore
extern bool step_detected;


#endif
