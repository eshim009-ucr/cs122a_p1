#include "pico/stdlib.h"
#include "task.h"
#include "ws2812b.h"
#include "sm_adc.h"
#include "pins.h"
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

void sm_led_handler(void);

Task task_sm_led = {
	.state = SM_Start,
	.period = 250,
	.handler = sm_led_handler
};


void sm_led_handler(void) {
	switch (task_sm_led.state) {
		case SM_Start:
			task_sm_led.state = SM_Init;
			break;
		case SM_Init:
			task_sm_led.state = SM_Wait;
			break;
		case SM_Wait:
			if (step_detected) {
				task_sm_led.state = SM_Step;
			} else {
				task_sm_led.state = SM_Wait;
			}
			break;
		case SM_Step:
			task_sm_led.state = SM_Wait;
			break;
		default:
			printf("ERROR: Fault in LED state machine\n");
			printf("\tstate=%d\n", task_sm_led.state);
			task_sm_led.state = SM_Start;
			gpio_put(PIN_STATUS_RED, 1);
			break;
	}
	
	switch (task_sm_led.state) {
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
			step_detected = false;
			break;
		default:
			break;
	}
}
