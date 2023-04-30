#include <stdio.h>
#include "pico/stdlib.h"
#include "task.h"
#include "ws2812b.h"
#include "sm_adc.h"


const uint8_t LED_STRIP_PIN = 3;


int main() {
	stdio_init_all();
	// gpio_init(LED_PIN);
	// gpio_set_dir(LED_PIN, GPIO_OUT);
	ws2812b_init(LED_STRIP_PIN);
	
	schedule_task(&task_sm_adc);
	
	while (true) {
		for (uint i = 0; i < 4; ++i)
			send_pixel(&RED);
		sleep_ms(250);
		
		for (uint i = 0; i < 4; ++i)
			send_pixel(&GREEN);
		sleep_ms(250);
		
		for (uint i = 0; i < 4; ++i)
			send_pixel(&BLUE);
		sleep_ms(250);
	}
	
	return 0;
}
