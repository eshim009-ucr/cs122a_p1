#include "pico/stdlib.h"
#include "hardware/adc.h"
#include "task.h"
#include "sm_adc.h"


const uint PIN_ADC0 = 26;
const uint PIN_ADC1 = 27;
// The number of state machine ticks to wait before registering another step
// Real world time depends on state machine period
const uint TICKS_COOLDOWN = 10;
// The reading default reading of the ADC when not detecting anything
// The current design biases it to half of VCC
// A 12-bit DC biased ADC will sit at 2^11 = 2048
const uint ADC_BIAS = 1 << 11;
// The minimum difference from a normal (no step) reading to indicate a step
const uint TRIGGER_THRESHOLD = 200;

enum SM_ADC_State {
	// Initial state, return to in event of undefined state
	SM_Start,
	// Initialize ADC peripheral
	SM_Init,
	// Read from the ADC to see if a step has ocurred
	SM_Read,
	// "Debounce" step input
	SM_Cooldown
};

void sm_adc_handler(void);

Task task_sm_adc = {
	.state = SM_Start,
	.period = 50,
	.handler = sm_adc_handler
};


bool step_detected = false;
// Equivalent to step_detected
// Hold a separate private copy to use for the next transistion
// Otherwise there is a race condition with the task that clears this value
static bool step_transition = false;
static uint cooldown = 0;


void sm_adc_handler(void) {
	switch (task_sm_adc.state) {
		case SM_Start:
			task_sm_adc.state = SM_Init;
			break;
		case SM_Init:
			task_sm_adc.state = SM_Read;
			break;
		case SM_Read:
			if (step_transition) {
				task_sm_adc.state = SM_Cooldown;
			} else {
				task_sm_adc.state = SM_Read;
			}
			break;
		case SM_Cooldown:
			if (cooldown == TICKS_COOLDOWN) {
				task_sm_adc.state = SM_Read;
			} else {
				task_sm_adc.state = SM_Cooldown;
			}
			break;
		default:
			task_sm_adc.state = SM_Start;
			break;
	}
	
	switch (task_sm_adc.state) {
		case SM_Start:
			break;
		
		case SM_Init:
			// With reference to SDK example
			// https://github.com/raspberrypi/pico-examples/blob/master/adc/microphone_adc/microphone_adc.c
			adc_init();
			adc_gpio_init(PIN_ADC0);
			adc_select_input(0);
			break;
		
		case SM_Read:
			uint sensor = adc_read();
			
			if (
					(sensor < ADC_BIAS - TRIGGER_THRESHOLD) ||
					(sensor > ADC_BIAS + TRIGGER_THRESHOLD)
				) {
				// Signal for other tasks
				step_detected = true;
				// Signal for internal transition
				step_transition = true;
				// Reset cooldown timer
				cooldown = 0;
			}
			
			break;
		
		case SM_Cooldown:
			step_transition = false;
			cooldown++;
			break;
		
		default:
			break;
	}
}
