#include "pico/stdlib.h"


const uint PIN_STATUS_RED = 14;
const uint PIN_STATUS_BLUE = 15;


void init_error() {
	gpio_init(PIN_STATUS_RED);
	gpio_init(PIN_STATUS_BLUE);
	gpio_set_dir(PIN_STATUS_RED, GPIO_OUT);
	gpio_set_dir(PIN_STATUS_BLUE, GPIO_OUT);
}


void show_error(const char* message, int state) {
	printf(message);
	gpio_put(PIN_STATUS_RED, 1);
}


void show_sm_error(const char* name, int state) {
	printf("ERROR: Fault in %s state machine (state=%d)\n", name, state);
	gpio_put(PIN_STATUS_RED, 1);
}


void show_notice(const char* message) {
	printf(message);
	gpio_put(PIN_STATUS_BLUE, 1);
}


void clear_status() {
	gpio_put(PIN_STATUS_RED, 0);
	gpio_put(PIN_STATUS_BLUE, 0);
}
