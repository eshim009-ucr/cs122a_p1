#include "pico/stdlib.h"
#include "task.h"
#include "ws2812b.h"
#include "sm_adc.h"
#include "sm_led.h"


const uint PIN_LED_STRIP = 3;


enum SM_LED_State {
	// Initial state, return to in event of undefined state
	SM_Start,
	// Iinitialize LED peripherals
	SM_Init,
	// Wait for a step to be detected
	SM_Wait,
	// Display a step
	SM_Step
};

bool sm_led_sdk_callback(struct repeating_timer *t);

Task task_sm_led = {
	.state = SM_Start,
	.period = 250,
	.sdk_callback = sm_led_sdk_callback
};


bool sm_led_sdk_callback(struct repeating_timer *t) {
	Task *task = t->user_data;
	
	switch (task->state) {
		case SM_Start:
			task->state = SM_Init;
			break;
		case SM_Init:
			task->state = SM_Wait;
			break;
		case SM_Wait:
			if (step_detected) {
				task->state = SM_Step;
			} else {
				task->state = SM_Wait;
			}
			break;
		default:
			task->state = SM_Start;
			break;
	}
	
	switch (task->state) {
		case SM_Start:
			break;
		case SM_Init:
			ws2812b_init(PIN_LED_STRIP);
			break;
		case SM_Wait:
			send_pixel(&RED);
			break;
		case SM_Step:
			send_pixel(&WHITE);
			break;
		default:
			break;
	}
	
	// Continue repeating
	return true;
}
