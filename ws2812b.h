#ifndef WS2812B_H
#define WS2812B_H
#include "pico/stdlib.h"


typedef struct {
	uint8_t g;
	uint8_t r;
	uint8_t b;
} Color;

extern const Color RED;
extern const Color GREEN;
extern const Color BLUE;

uint ws2812b_init(uint pin);
void send_pixel(const Color *c);


#endif
