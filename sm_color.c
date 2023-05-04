#include "sm_color.h"
#include "sm_error.h"
#include "task.h"


const uint PIN_BTN_COLOR = 16;


enum SM_Color_State {
	// Initial state, return to in event of undefined state
	SM_Start,
	// Initialize button input
	SM_Init,
	// Display red patterns
	SM_Color_Red,
	// Display green patterns
	SM_Color_Green,
	// Display blue patterns
	SM_Color_Blue,
	// Display white patterns
	SM_Color_White
};

void sm_color_handler(void);

Task task_sm_color = {
	.state = SM_Start,
	.period = 500,
	.handler = sm_color_handler
};

const Color* current_color = &BLACK;


void sm_color_handler(void) {
	switch (task_sm_color.state) {
		case SM_Start:
			task_sm_color.state = SM_Init;
			break;
		case SM_Init:
			gpio_init(PIN_BTN_COLOR);
			gpio_set_dir(PIN_BTN_COLOR, GPIO_IN);
			gpio_pull_up(PIN_BTN_COLOR);
			break;
		case SM_Color_Red:
			if (gpio_get(PIN_BTN_COLOR) == 0) {
				task_sm_color.state = SM_Color_Green;
			}
			break;
		case SM_Color_Green:
			if (gpio_get(PIN_BTN_COLOR) == 0) {
				task_sm_color.state = SM_Color_Blue;
			}
			break;
		case SM_Color_Blue:
			if (gpio_get(PIN_BTN_COLOR) == 0) {
				task_sm_color.state = SM_Color_White;
			}
			break;
		case SM_Color_White:
			if (gpio_get(PIN_BTN_COLOR) == 0) {
				task_sm_color.state = SM_Color_Red;
			}
			break;
		default:
			show_sm_error("color", task_sm_color.state);
			task_sm_color.state = SM_Start;
			break;
	}
	
	switch (task_sm_color.state) {
		case SM_Start:
			break;
		case SM_Init:
			gpio_init(PIN_BTN_COLOR);
			gpio_set_dir(PIN_BTN_COLOR, GPIO_IN);
			gpio_pull_up(PIN_BTN_COLOR);
			break;
		case SM_Color_Red:
			current_color = &RED;
			break;
		case SM_Color_Green:
			current_color = &GREEN;
			break;
		case SM_Color_Blue:
			current_color = &BLUE;
			break;
		case SM_Color_White:
			current_color = &WHITE;
			break;
		default:
			break;
	}
}
