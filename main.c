#include <stdio.h>
#include "pico/stdlib.h"
#include "task.h"
#include "sm_adc.h"


const uint8_t LED_PIN = PICO_DEFAULT_LED_PIN;


int main() {
	stdio_init_all();
	gpio_init(LED_PIN);
	gpio_set_dir(LED_PIN, GPIO_OUT);
	
	schedule_task(&task_sm_adc);
	
	while (true) {
		gpio_put(LED_PIN, 1);
		sleep_ms(250);
		
		gpio_put(LED_PIN, 0);
		sleep_ms(250);
	}
	
	return 0;
}
