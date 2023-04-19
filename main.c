#include <stdio.h>
#include "pico/stdlib.h"


const uint8_t LED_PIN = PICO_DEFAULT_LED_PIN;


int main() {
	stdio_init_all();
	gpio_init(LED_PIN);
	gpio_set_dir(LED_PIN, GPIO_OUT);
	
	while (true) {
		gpio_put(LED_PIN, 1);
		printf("On\n");
		sleep_ms(250);
		
		gpio_put(LED_PIN, 0);
		printf("Off\n");
		sleep_ms(250);
	}
	
	return 0;
}
