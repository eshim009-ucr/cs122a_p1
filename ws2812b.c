#include "pico/stdlib.h"
#include "hardware/clocks.h"
#include "ws2812b.pio.h"
#include "ws2812b.h"


const Color RED = {
	.r = 0xFF,
	.g = 0,
	.b = 0
};
const Color GREEN = {
	.r = 0,
	.g = 0xFF,
	.b = 0
};
const Color BLUE = {
	.r = 0,
	.g = 0,
	.b = 0xFF
};


static const uint STATE_MACHINE_INDEX = 0;
static const PIO PIO_INST = pio0;
static const uint FREQ = 800000;


// From SDK Example: https://github.com/raspberrypi/pico-examples/blob/master/pio/ws2812/ws2812.pio#L31-L47
// Most arguments moved to private constants
// Offset determined internally and returned
uint ws2812b_init(uint pin) {
	uint offset = pio_add_program(PIO_INST, &ws2812b_program);
	
	pio_gpio_init(PIO_INST, pin);
	pio_sm_set_consecutive_pindirs(PIO_INST, STATE_MACHINE_INDEX, pin, 1, true);
	
	pio_sm_config c = ws2812b_program_get_default_config(offset);
	sm_config_set_sideset_pins(&c, pin);
	sm_config_set_out_shift(&c, false, true, 24);
	sm_config_set_fifo_join(&c, PIO_FIFO_JOIN_TX);
	
	int cycles_per_bit = ws2812b_T1 + ws2812b_T2 + ws2812b_T3;
	float div = clock_get_hz(clk_sys) / (FREQ * cycles_per_bit);
	sm_config_set_clkdiv(&c, div);
	
	pio_sm_init(PIO_INST, STATE_MACHINE_INDEX, offset, &c);
	pio_sm_set_enabled(PIO_INST, STATE_MACHINE_INDEX, true);
	
	return offset;
}


// Can be optimized with a union type if needed
void send_pixel(const Color* c) {
	pio_sm_put_blocking(pio0, 0,
		(c->g << 24) |
		(c->r << 16) |
		(c->b << 8)
	);
}
