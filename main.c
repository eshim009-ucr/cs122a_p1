#include <stdio.h>
#include "pico/stdlib.h"
#include "task.h"
#include "ws2812b.h"
#include "sm_adc.h"
#include "sm_led.h"
#include "sm_color.h"
#include "sm_error.h"


const uint LED_PIN = PICO_DEFAULT_LED_PIN;


int main() {
	stdio_init_all();
	gpio_init(LED_PIN);
	gpio_set_dir(LED_PIN, GPIO_OUT);
	
	init_error();
	
	init_scheduler();
	if (!schedule_task(&task_sm_adc)) {
		show_error("Unable to schedule all tasks\n");
	}
	if (!schedule_task(&task_sm_led)) {
		show_error("Unable to schedule all tasks\n");
	}
	if (!schedule_task(&task_sm_color)) {
		show_error("Unable to schedule all tasks\n");
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
