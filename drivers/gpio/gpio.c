#include "gpio.h"

#include "../iomux.h"

void Drivers_GPIO_Init(void) {
    for (uint8_t pin = 0; pin < DRIVERS_GPIO_PIN_CNT; pin++) {
        Drivers_IOMUX_GPIO_SetPullup(pin, 1);
    }
}

void Drivers_GPIO_SetMode(uint8_t const pin, DRIVERS_GPIO_MODE const mode) {
    if (mode == DRIVERS_GPIO_MODE_OUTPUT) {
        DRIVERS_GPIO_ENA_W1TS = (1 << pin); /* Set output */
    }
    else {
        DRIVERS_GPIO_ENA_W1TC = (1 << pin);
    }
}

void Drivers_GPIO_Write(uint8_t const pin, uint16_t const val) {
    if (pin >= 6 && pin <= 11) return;
    if (val) {
        DRIVERS_GPIO_OUT_W1TS = (1 << pin);
    } else {
        DRIVERS_GPIO_OUT_W1TC = (1 << pin);
    }
}
