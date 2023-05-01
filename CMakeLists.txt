cmake_minimum_required(VERSION 3.13)

# initialize pico-sdk from submodule
# note: this must happen before project()
include(pico-sdk/pico_sdk_init.cmake)

project(my_project)

# initialize the Raspberry Pi Pico SDK
pico_sdk_init()

add_executable(main)

pico_generate_pio_header(main ${CMAKE_CURRENT_LIST_DIR}/ws2812b.pio)

target_sources(main PRIVATE
	main.c
	sm_adc.c
	sm_led.c
	task.c
	ws2812b.c
)

# Add pico_stdlib library which aggregates commonly used features
target_link_libraries(main PRIVATE
	pico_stdlib
	hardware_adc
	hardware_pio
)

# Enable USB serial output for printf
pico_enable_stdio_usb(main 1)
pico_enable_stdio_uart(main 0)

# create map/bin/hex/uf2 file in addition to ELF.
pico_add_extra_outputs(main)
