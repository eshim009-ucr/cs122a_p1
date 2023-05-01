#include <stdio.h>
#include "pico/stdlib.h"
#include "task.h"
#include "ws2812b.h"
#include "sm_adc.h"
#include "sm_led.h"


const uint8_t LED_PIN = PICO_DEFAULT_LED_PIN;


int main() {
	stdio_init_all();
	gpio_init(LED_PIN);
	gpio_set_dir(LED_PIN, GPIO_OUT);
	
	init_scheduler();
	schedule_task(&task_sm_adc);
	schedule_task(&task_sm_led);
	
	while (true) {
		gpio_put(LED_PIN, 1);
		sleep_ms(250);
		gpio_put(LED_PIN, 0);
		sleep_ms(250);
	}
	
	return 0;
}
