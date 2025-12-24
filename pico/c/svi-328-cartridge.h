/**
 * SVI-328 PicoROM
 * 
 * Copyright (c) 2025 Markus Rautopuro
 * 
 * Works only with Raspberry Pico 2 W.
 */

#define CCS1_PIN 22
#define CCS2_PIN 26
#define CCS3_PIN 27
#define CCS4_PIN 28

#define CCS1_GPIO_MASK (1UL << CCS1_PIN)
#define CCS2_GPIO_MASK (1UL << CCS2_PIN)
#define CCS3_GPIO_MASK (1UL << CCS3_PIN)
#define CCS4_GPIO_MASK (1UL << CCS4_PIN)

#define CCS_GPIO_MASK (CCS1_GPIO_MASK | CCS2_GPIO_MASK | CCS3_GPIO_MASK | CCS4_GPIO_MASK)
#define ADDRESS_PIN_MASK (1UL << 14) - 1        // first 14 bits
#define DATA_PIN_MASK ((1UL << 8) - 1) << 14    // second 8 bits
#define ALL_GPIO_MASK (ADDRESS_PIN_MASK | DATA_PIN_MASK | CCS_GPIO_MASK)

void __no_inline_not_in_flash_func(core1_entry)();
