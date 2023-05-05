#include "pico/stdlib.h"
#include "task.h"
#include "ws2812b.h"
#include "sm_adc.h"
#include "sm_error.h"
#include "sm_color.h"
#include "sm_pattern.h"
#include "sm_led.h"


const uint PIN_LED_STRIP = 3;
const uint STRIP_LENGTH = 25;


enum SM_LED_State {
	// Initial state, return to in event of undefined state
	SM_Start,
	// Iinitialize LED peripherals
	SM_Init,
	// Wait for a step to be detected, display nothing
	SM_Off,
	// Display a color at full brightness
	SM_On,
	// Dim the current color
	SM_Dim
};

void sm_led_handler(void);

Task task_sm_led = {
	.state = SM_Start,
	.period = 100,
	.handler = sm_led_handler
};


uint dimmer;


Color dim_color(const Color* color) {
	Color darkened;
	
	darkened.r = color->r >> dimmer;
	darkened.g = color->g >> dimmer;
	darkened.b = color->b >> dimmer;
	
	return darkened;
}


void sm_led_handler(void) {
	switch (task_sm_led.state) {
		case SM_Start:
			task_sm_led.state = SM_Init;
			break;
		case SM_Init:
			task_sm_led.state = SM_Off;
			break;
		case SM_Off:
			if (step_detected) {
				task_sm_led.state = SM_On;
			}
			break;
		case SM_On:
			switch (current_pattern) {
				case PATTERN_BINARY:
					task_sm_led.state = SM_Off;
					break;
				case PATTERN_FADE:
					task_sm_led.state = SM_Dim;
					break;
			}
			break;
		case SM_Dim:
			if (dimmer == 8) {
				task_sm_led.state = SM_Off;
			}
			break;
		default:
			show_sm_error("LED", task_sm_led.state);
			task_sm_led.state = SM_Start;
			break;
	}
	
	switch (task_sm_led.state) {
		case SM_Start:
			break;
		case SM_Init:
			ws2812b_init(PIN_LED_STRIP);
			break;
		case SM_Off:
			for (uint i = 0; i < STRIP_LENGTH; ++i) {
				send_pixel(&BLACK);
			}
			break;
		case SM_On:
			for (uint i = 0; i < STRIP_LENGTH; ++i) {
				send_pixel(current_color);
			}
			dimmer = 0;
			step_detected = false;
			break;
		case SM_Dim:
			Color tmp = dim_color(current_color);
			for (uint i = 0; i < STRIP_LENGTH; ++i) {
				send_pixel(&tmp);
			}
			dimmer++;
			break;
		default:
			break;
	}
}
