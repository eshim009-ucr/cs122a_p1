#include "pico/stdlib.h"
#include "hardware/adc.h"
#include "task.h"
#include "sm_adc.h"


const uint8_t PIN_ADC0 = 26;
const uint8_t PIN_ADC1 = 27;

enum SM_ADC_State {SM_Start, SM_Init, SM_Read};

bool sm_adc_sdk_callback(struct repeating_timer *t);


Task task_sm_adc = {
	.state = SM_Start,
	.period = 50,
	.sdk_callback = sm_adc_sdk_callback
};


inline static void init_adc();
inline static void read_adc();


bool sm_adc_sdk_callback(struct repeating_timer *t) {
	Task *task = t->user_data;
	
	switch (task->state) {
		case SM_Start:
			task->state = SM_Init;
			break;
		case SM_Init:
			task->state = SM_Read;
			break;
		case SM_Read:
			task->state = SM_Read;
			break;
		default:
			task->state = SM_Start;
			break;
	}
	
	switch (task->state) {
		case SM_Start:
			break;
		case SM_Init:
			init_adc();
			break;
		case SM_Read:
			read_adc();
			break;
		default:
			break;
	}
	
	// Continue repeating
	return true;
}


// With reference to SDK example
// https://github.com/raspberrypi/pico-examples/blob/master/adc/microphone_adc/microphone_adc.c
inline static void init_adc() {
	adc_init();
	adc_gpio_init(PIN_ADC0);
	adc_select_input(0);
}


inline static void read_adc() {
	printf("%d\n", adc_read());
}
