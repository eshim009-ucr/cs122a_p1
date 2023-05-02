#include <stdio.h>
#include "pico/stdlib.h"
#include "task.h"
#include "ws2812b.h"
#include "sm_adc.h"
#include "sm_led.h"
#include "pins.h"


const uint LED_PIN = PICO_DEFAULT_LED_PIN;
const uint PIN_STATUS_RED = 14;
const uint PIN_STATUS_BLUE = 15;


int main() {
	stdio_init_all();
	gpio_init(LED_PIN);
	gpio_init(PIN_STATUS_RED);
	gpio_init(PIN_STATUS_BLUE);
	gpio_set_dir(LED_PIN, GPIO_OUT);
	gpio_set_dir(PIN_STATUS_RED, GPIO_OUT);
	gpio_set_dir(PIN_STATUS_BLUE, GPIO_OUT);
	
	init_scheduler();
	if (!schedule_task(&task_sm_adc)) {
		gpio_put(PIN_STATUS_RED, 1);
	}
	if (!schedule_task(&task_sm_led)) {
		gpio_put(PIN_STATUS_RED, 1);
	}
	start_scheduler();
	
	while (true) {
		gpio_put(LED_PIN, 1);
		sleep_ms(250);
		gpio_put(LED_PIN, 0);
		sleep_ms(250);
	}
	
	return 0;
}
