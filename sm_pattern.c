#include "sm_error.h"
#include "task.h"
#include "sm_pattern.h"


const uint PIN_BTN_PATTERN = 17;


enum SM_Pattern_State {
	// Initial state, return to in event of undefined state
	SM_Start,
	// Initialize button input
	SM_Init,
	// Display a solid color briefly after detecting a step
	SM_Pattern_Binary,
	// Display a fading color after detectinga  step
	SM_Pattern_Fade
};

void sm_pattern_handler(void);

Task task_sm_pattern = {
	.state = SM_Start,
	.period = 500,
	.handler = sm_pattern_handler
};

Pattern current_pattern;


void sm_pattern_handler(void) {
	switch (task_sm_pattern.state) {
		case SM_Start:
			task_sm_pattern.state = SM_Init;
			break;
		case SM_Init:
			gpio_init(PIN_BTN_PATTERN);
			gpio_set_dir(PIN_BTN_PATTERN, GPIO_IN);
			gpio_pull_up(PIN_BTN_PATTERN);
			break;
		case SM_Pattern_Binary:
			if (gpio_get(PIN_BTN_PATTERN) == 0) {
				task_sm_pattern.state = SM_Pattern_Fade;
			}
			break;
		case SM_Pattern_Fade:
			if (gpio_get(PIN_BTN_PATTERN) == 0) {
				task_sm_pattern.state = SM_Pattern_Binary;
			}
			break;
		default:
			show_sm_error("pattern", task_sm_pattern.state);
			task_sm_pattern.state = SM_Start;
			break;
	}
	
	switch (task_sm_pattern.state) {
		case SM_Start:
			break;
		case SM_Init:
			gpio_init(PIN_BTN_PATTERN);
			gpio_set_dir(PIN_BTN_PATTERN, GPIO_IN);
			gpio_pull_up(PIN_BTN_PATTERN);
			break;
		case SM_Pattern_Binary:
			current_pattern = PATTERN_BINARY;
			break;
		case SM_Pattern_Fade:
			current_pattern = PATTERN_FADE;
			break;
		default:
			break;
	}
}
