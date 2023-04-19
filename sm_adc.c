#include "pico/stdlib.h"
#include "hardware/adc.h"
#include "task.h"
#include "sm_adc.h"


const uint8_t PIN_ADC0 = 26;
const uint8_t PIN_ADC1 = 27;

static enum {SM_Start, SM_Init, SM_Read} state_sm_read_adc;

inline static void init_adc();
inline static void read_adc();


TaskState tick_sm_read_adc(TaskState state) {
	switch (state) {
		case SM_Start:
			state = SM_Init;
			break;
		case SM_Init:
			state = SM_Read;
			break;
		case SM_Read:
			state = SM_Read;
			break;
		default:
			state = SM_Start;
			break;
	}
	
	switch (state) {
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
	
	return state;
}


// With reference to SDK example
// https://github.com/raspberrypi/pico-examples/blob/master/adc/microphone_adc/microphone_adc.c
inline static void init_adc() {
	adc_init();
	adc_gpio_init(PIN_ADC0);
	adc_select_input(0);
}


inline static void read_adc() {
	adc_read();
}
