/**
 * SVI-328 PicoROM
 * 
 * Copyright (c) 2025 Markus Rautopuro
 * 
 * Works only with Raspberry Pico 2 W.
 */

#include <stdio.h>
#include <string.h>
#include "pico/cyw43_arch.h"
#include "pico/stdlib.h"
#include "pico/multicore.h"
#include "hardware/clocks.h"
#include "hardware/flash.h"

#include "svi-328-cartridge.h"

void pico_set_led(bool led_on)
{
	cyw43_arch_gpio_put(CYW43_WL_GPIO_LED_PIN, led_on);
}

int main()
{
	set_sys_clock_khz(250000, true); // Overclocks Pico to handle ROM emulation properly

	gpio_init_mask(ALL_GPIO_MASK);
	gpio_set_dir_in_masked(ALL_GPIO_MASK);

	multicore_launch_core1(core1_entry);

	cyw43_arch_init();
	
	pico_set_led(true);

	stdio_usb_init();

	while (true)
	{
		sleep_ms(1000);
	}
}
