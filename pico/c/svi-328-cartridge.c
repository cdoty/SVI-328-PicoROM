/**
 * SVI-328 PicoROM
 * 
 * Copyright (c) 2025 Markus Rautopuro
 * 
 * Works only with Raspberry Pico 2 W.
 */

#include <stdio.h>
#include <string.h>
#include "pico/stdlib.h"
#include "pico/multicore.h"

#include "svi-328-cartridge.h"

#include "rom.h"

/**
 * 32 kB ROM emulation
 */

void __no_inline_not_in_flash_func(core1_entry)()
{
    while (true)
	{ // Here, we are just serving the uploaded 32 kB ROM
        while (gpio_get(CCS1_PIN) & gpio_get(CCS2_PIN))
		{
            tight_loop_contents();
        }

		uint32_t pins = gpio_get_all() & ALL_GPIO_MASK;
		uint32_t addr = pins & ADDRESS_PIN_MASK | ((pins & CCS1_GPIO_MASK) ? 1UL << 14 : 0);

        gpio_set_dir_out_masked(DATA_PIN_MASK);
        gpio_put_masked(DATA_PIN_MASK, ((uint32_t)ROM[addr]) << 14);

        while (!gpio_get(CCS1_PIN) | !gpio_get(CCS2_PIN))
		{
            tight_loop_contents();
        }
        
		gpio_set_dir_in_masked(DATA_PIN_MASK);
    }
}